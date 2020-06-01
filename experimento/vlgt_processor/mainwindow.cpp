#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>
#include <QDir>
#include <QStringList>
#include <QStringListModel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
//    estimator(NULL),
    vlgtProcessor(NULL),
    vlgtCalibrator(NULL),
    cancelAction(false)
{
    ui->setupUi(this);
    ui->buttonGroup->setId(ui->radioButtonLEC, 0);
    ui->buttonGroup->setId(ui->radioButtonREC, 1);
    ui->buttonGroup->setId(ui->radioButtonLWC, 2);
    ui->buttonGroup->setId(ui->radioButtonRWC, 3);
    ui->buttonGroup->setId(ui->radioButtonLIC, 4);

    // conecta evento com propriedade
    connect(ui->buttonGroup, SIGNAL(buttonClicked(int)), this, SLOT(setFixRef(int)) );

    // recupera configurações
    sourceFolder = settings.value("sourceFolder", (QCoreApplication::applicationDirPath()).toStdString().c_str() ).toString() ;
    targetFolder = settings.value("targetFolder", QCoreApplication::applicationDirPath() ).toString();
    baseFileName = settings.value("baseFileName", "vlgt_results").toString();

    // instancia o processador e conecta com os componentes da tela.
    this->vlgtProcessor = new VlgtProcessor( sourceFolder, ui->sliderRavgSize->value() );
    connect(ui->sliderFaceBrightnessAlpha, SIGNAL(valueChanged(int)), this->vlgtProcessor, SLOT(setFaceBrightnessAlpha(int)));
    connect(ui->sliderFaceBrightnessBeta, SIGNAL(valueChanged(int)), this->vlgtProcessor, SLOT(setFaceBrightnessBeta(int)));
    connect(ui->sliderRavgSize, SIGNAL(valueChanged(int)), this->vlgtProcessor, SLOT(setRasQueueSize(int)));
    connect(this, SIGNAL(actionCancelChanged(bool)), vlgtProcessor, SLOT(setStop(bool)) );
    // recupera config.
    ui->sliderFaceBrightnessAlpha->setValue( settings.value("faceBrightnessAlpha").toInt() );

    QObject *pobj = dynamic_cast<QObject*>(&this->vlgtProcessor->ifind);
    connect(ui->sliderIrisBrightnessAlpha, SIGNAL(valueChanged(int)), pobj, SLOT(setIrisBrightnessAlpha(int)));
    ui->sliderIrisBrightnessAlpha->setValue( settings.value("irisBrightnessAlpha").toInt() );

    ui->sliderRavgSize->setValue( settings.value("rasQueueSize").toInt() );

    connect(&videoTimer, SIGNAL(timeout()), this, SLOT(videoRefresh()));
    videoTimer.start(100);
}

MainWindow::~MainWindow()
{
    // salva configurações
    settings.setValue("sourceFolder", sourceFolder);
    settings.setValue("targetFolder", targetFolder);
    settings.setValue("baseFileName", baseFileName);
    settings.setValue("faceBrightnessAlpha", ui->sliderFaceBrightnessAlpha->value() );
    settings.setValue("irisBrightnessAlpha", ui->sliderIrisBrightnessAlpha->value() );
    settings.setValue("rasQueueSize", ui->sliderRavgSize->value() );

    delete vlgtProcessor;
    if (vlgtCalibrator != NULL)
        delete vlgtCalibrator;
    delete ui;
}

void MainWindow::on_actionPasta_origem_triggered()
{
    sourceFolder = QFileDialog::getExistingDirectory(this,
                                                     tr("Escolha uma pasta de origem"),
                                                     sourceFolder,
                                                     QFileDialog::ShowDirsOnly |
                                                     QFileDialog::DontResolveSymlinks);
}

void MainWindow::on_actionPasta_destino_triggered()
{
    targetFolder = QFileDialog::getExistingDirectory(this,
                                                     tr("Escolha uma pasta de destino"),
                                                     sourceFolder,
                                                     QFileDialog::ShowDirsOnly |
                                                     QFileDialog::DontResolveSymlinks);
}

void MainWindow::on_actionNome_de_arquivo_triggered()
{
    bool ok;
    baseFileName = QInputDialog::getText(this,
                                         tr("Informe o nome base para arquivos de saída:"),
                                         tr("Arquivos de saída"),
                                         QLineEdit::Normal,
                                         baseFileName, &ok);
}

void MainWindow::on_actionListaArquivos_triggered()
{
    QDir mydir( sourceFolder );
    QStringList filters;
    filters << "*.avi";
    QStringList list = mydir.entryList(filters);

    ui->listWidget->clear();
    ui->listWidget->addItems(list);
}

void MainWindow::on_actionLocateEyeFeatures_triggered()
{
    cancelAction = false;
    QMessageBox msg;
    msg.setText( QString::fromUtf8("Deseja sobrescrever as informações já existentes?") );
    msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msg.setDefaultButton(QMessageBox::No);
    int ret = msg.exec();

    if (ret == QMessageBox::Yes) {
        QStringList arqs;
        for (int i=0; i < ui->listWidget->count(); i++)
            if (ui->listWidget->item(i)->isSelected()) {
                arqs.append( ui->listWidget->item(i)->text() );
            }

        if (arqs.count() > 0) {
            // inicia o processamento da lista de arquivos.
            vlgtProcessor->processQueue(arqs);
        }
    }

    cancelAction = false;
}

void MainWindow::on_actionEstimatePOR_triggered()
{
    ui->textOut->clear();
    // primeiramente, faz a calibragem.
    calibrate();

    // para todos arquivos da lista
    for (int i=0; i<ui->listWidget->count() && !cancelAction; i++)
        // processo aqueles que estiverem selecionados
        if (ui->listWidget->item(i)->isSelected() ) {
            QString fn = sourceFolder;
            fn.append("/").append(ui->listWidget->item(i)->text() );

            // busca a resolução do arquivo
            Size sz = VlgtDataUtils::loadOriginalScreenResolution( fn );

            Estimator estimator(fn, (FixedReference)ui->buttonGroup->checkedId(),
                                    sz,
                                    ui->sliderRavgSize->value() );
            while (estimator.hasFrames() && !cancelAction)
            {
                estimator.drawPOR();
                estimatorOutputImage = estimator.outputImage.clone();
                estimatorOutputVideo = estimator.outputVideo.clone();
//                waitKey(30);
                QApplication::processEvents();
                videoRefresh();
            }

            double secHitsPerc = estimator.sectorHits*100/estimator.frameCount;
            ui->textOut->append( QString("File: ")
                                 .append( fn ) );
            ui->textOut->append( QString("Total frames: ")
                                 .append( QString::number(estimator.frameCount) ) );
            ui->textOut->append( QString("Sector Hits: ")
                                 .append( QString::number(estimator.sectorHits) )
                                 .append( " (" )
                                 .append( QString::number(secHitsPerc) )
                                 .append( "%)" ) );
            double avgerrpx = estimator.accumError/estimator.frameCount;
            double avgerrpxx = estimator.accumErrorX/estimator.frameCount;
            double avgerrpxy = estimator.accumErrorY/estimator.frameCount;
            double avgerrpxperc = avgerrpx*100/estimator.maxDist();

            double avgerrdeg = estimator.accumErrorDeg/estimator.frameCount;
            double avgerrdegx = estimator.accumErrorDegX/estimator.frameCount;
            double avgerrdegy = estimator.accumErrorDegY/estimator.frameCount;

            double avgtime = estimator.accumTime/estimator.frameCount;

            ui->textOut->append( QString::fromUtf8("Erro médio (pixels): ")
                                 .append( QString::number(avgerrpx) )
                                 .append( " (" )
                                 .append( QString::number( avgerrpxperc ) )
                                 .append( "%)" ) );
            ui->textOut->append( QString("Eixo X:")
                                 .append( QString::number(avgerrpxx) ));
            ui->textOut->append( QString("Eixo Y:")
                                 .append( QString::number(avgerrpxy) ));

            ui->textOut->append( QString::fromUtf8("Erro médio (graus): ")
                                 .append( QString::number(avgerrdeg) ));
            ui->textOut->append( QString("Eixo X:")
                                 .append( QString::number(avgerrdegx) ));
            ui->textOut->append( QString("Eixo Y:")
                                 .append( QString::number(avgerrdegy) ));
            ui->textOut->append( QString::fromUtf8("Tempo médio por frame:")
                                 .append( QString::number(avgtime) ));

            QMessageBox msgBox;
            msgBox.setText("A estimativa do olhar foi calculada.");
            msgBox.setInformativeText("Deseja salvar os resultados no arquivo existente?");
            msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
            msgBox.setDefaultButton(QMessageBox::Save);
            int ret = msgBox.exec();
            if (ret == QMessageBox::Save)
            {
                QFile file("summary.txt");
                if (!file.open(QIODevice::WriteOnly| QIODevice::Append | QIODevice::Text))
                    qDebug("Erro abrindo arquivo de saída.");
                else
                {
                    QTextStream ts(&file);

                    ts << fn << ";";                                            // pasta/nome do arquivo
                    ts << ui->sliderIrisBrightnessAlpha->value() << ";";        // valor segmentação íris
                    ts << ui->buttonGroup->checkedId() << ";";                  // referência fixa
                    ts << ui->sliderRavgSize->value() << ";";                   // tamanho da fila para suavização
                    ts << estimator.frameCount << ";";                          // nº frames vídeo
                    ts << sz.width << ";";                                      // largura tela
                    ts << sz.height << ";";                                     // altura tela
                    ts << estimator.maxDist() << ";";                           // distancia máx dentro da tela
                    ts << estimator.sectorHits << ";";                          // sector hits
                    ts << avgerrpx << ";";                                      // erro médio pixels
                    ts << avgerrpxx << ";";                                     // erro médio pixels eixo X
                    ts << avgerrpxy << ";";                                     // erro médio pixels eixo Y
                    ts << avgerrdeg << ";";                                     // erro médio graus
                    ts << avgerrdegx << ";";                                    // erro médio graus eixo X
                    ts << avgerrdegy << ";";                                    // erro médio graus eixo Y
                    ts << ";";                                                  // movto. cabeça
                    ts << ";";                                                  // iluminação
                    ts << QString::number(avgtime);                                       // tempo
                    ts << endl;

                    file.close();
                }
            }

        }

    // limpa imagens
    estimatorOutputImage = Mat();
    estimatorOutputVideo = Mat();
    cancelAction = false;
}

void MainWindow::videoRefresh()
{
    QImage img;
    Mat img1, img2;

    // saída do vídeo
    if ( !vlgtProcessor->outputImage.empty() ) {
        Size sz(vlgtProcessor->outputImage.cols*0.57, vlgtProcessor->outputImage.rows*0.57);
        cv::resize( vlgtProcessor->outputImage, img1, sz );
        cvtColor(img1, img2, CV_RGB2BGR);
        img = QImage((const unsigned char*)(img2.data), img2.cols, img2.rows, img2.step, QImage::Format_RGB888);
        ui->labelVideoOutput->setPixmap( QPixmap::fromImage(img) );
    }

    // saída do olho
    if ( !vlgtProcessor->outputEye.empty() ) {
        double e = (double)vlgtProcessor->outputEye.cols;
        double l = (double)ui->labelEyeOutput->width();
        double r = e/l;
        r *= 1.2;
        if (r != 0) {
            Size sz(vlgtProcessor->outputEye.cols/r, vlgtProcessor->outputEye.rows/r);
            cv::resize( vlgtProcessor->outputEye, img1, sz );
            cvtColor(img1, img2, CV_RGB2BGR);
            img = QImage((const unsigned char*)(img2.data), img2.cols, img2.rows, img2.step, QImage::Format_RGB888);
            ui->labelEyeOutput->setPixmap( QPixmap::fromImage(img) );
        }
    }

    // saída da estimativa
    if (!estimatorOutputImage.empty()) {
        Size tam( ui->labelPlotOutput->width(), ui->labelPlotOutput->height() );
        cv::resize(estimatorOutputImage, img1, tam );
        cvtColor(img1, img2, CV_BGR2RGB);
        img= QImage((const unsigned char*)(img2.data), img2.cols, img2.rows, img2.step, QImage::Format_RGB888);
        ui->labelPlotOutput->setPixmap( QPixmap::fromImage(img) );
    }
    if (!estimatorOutputVideo.empty()) {
        Size sz( estimatorOutputVideo.cols*0.57, estimatorOutputVideo.rows*0.57 );
        cv::resize( estimatorOutputVideo, img1, sz );
        cvtColor( img1, img2, CV_RGB2BGR );
        img = QImage((const unsigned char*)(img2.data), img2.cols, img2.rows, img2.step, QImage::Format_RGB888);
        ui->labelVideoOutput->setPixmap( QPixmap::fromImage(img) );
    }

    repaint();
}

void MainWindow::on_sliderFaceBrightnessAlpha_valueChanged(int value)
{
    ui->label->setText( QString("Alpha ").append( QString::number( (double)value/10 ) )) ;
}

void MainWindow::on_sliderIrisBrightnessAlpha_valueChanged(int value)
{
    ui->label_3->setText( QString("Alpha ").append( QString::number( (double)value/10 ) )) ;
}

void MainWindow::calibrate()
{
    QStringList arqs;
    for (int i=0; i < ui->listWidget->count(); i++)
        if (ui->listWidget->item(i)->isSelected() ) {
            arqs.append( ui->listWidget->item(i)->text() );
        }

    if (arqs.count() > 0) {
        // inicia a calibragem
        vlgtCalibrator = new VlgtVideoCalibrator( sourceFolder, ui->sliderPolyDeg->value() );
        vlgtCalibrator->calibrateQueue(arqs, (FixedReference)ui->buttonGroup->checkedId());
    }

}

void MainWindow::setFixRef(int ref)
{
    fixRef = (FixedReference)ref;
    qDebug("Referencial Fixo: %d",fixRef);
}

void MainWindow::on_actionCancelar_triggered()
{
    cancelAction = true;
    emit actionCancelChanged(cancelAction);
}

void MainWindow::on_sliderIrisBrightnessAlpha_actionTriggered(int action)
{

}

void MainWindow::updateOutput()
{

}
