#include <QKeyEvent>
#include <QtGui>
#include "widget.h"
#include "ui_widget.h"
#include "window.h"

#ifdef Q_OS_WIN
#include <windows.h> // for Sleep
#endif

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    size(QSize(60, 60)),
    elapsed(0),
    origin(QPoint(0,0)),
    m_frameCount(0),
    curr_move(LRT),
    ui(new Ui::Widget),
    isRecording(false),
    isAnimating(false)
{
    ui->setupUi(this);

    // antes de mais nada, o termo de consentimento.
    termAccepted = mostraTermo();

    if (termAccepted) {
        // pergunto o nome e o email, para gravar no arquivo
        bool ok;
        do {
            QString text = QInputDialog::getText(this, tr("Identificação"),
                                              tr("Informe seu nome:"), QLineEdit::Normal,
                                              QDir::home().dirName(), &ok);
            userName = text;
        } while (!ok || userName.isEmpty());

        ok = false;
        do {
            QString text = QInputDialog::getText(this, tr("Contato"),
                                              tr("Endereço de e-mail:"), QLineEdit::Normal,
                                              QDir::home().dirName(), &ok);
            userEmail = text;
        } while (!ok || userEmail.isEmpty());

    }

    // inicializo o arquivo para gravar os dados
    QString nomearq = parent->accessibleDescription();
    nomearq.append(".txt");

    outfile = new QFile(nomearq);
    ts = new QTextStream(outfile);

    if (!(*outfile).open(QIODevice::WriteOnly | QIODevice::Text))
        qDebug("Não foi possí­vel abrir o arquivo de saída.");

    // instancio o objeto para captura de video
    video = new Capture(parent);

    *ts << "VLGT Collector starting at time " << QDateTime::currentDateTime().toString() << endl;
    *ts << "User name: " << userName << endl;
    *ts << "E-mail: " << userEmail << endl;
    *ts << "Screen resolution is \t" << QApplication::desktop()->width() << "x" <<
                                        QApplication::desktop()->height() << endl;
    *ts << "FrameCount\tObjX\tObjY" << endl;

    // calculo o intervalo de tempo que deve transcorrer entre frames (aprox. 33ms)
    timeslice = 5000 / 151.51;

    // medidor de tempo
    startTicks = cv::getTickCount();

    // timer que controla a animação
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(animate()));

    timer->start(20);

    // por via das dúvidas,
    t.start();
}

Widget::~Widget()
{
    *ts << "VLGT Collector finishing at time " << QDateTime::currentDateTime().toString() << endl;
}

void Widget::animate()
{
    (*video).captureFrame(this);
    if (isRecording) {
        (*video).writeFrame();
        *ts << m_frameCount << "\t\t"
            << origin.x()+(size.width()/2) << "\t"
            << origin.y()+(size.height()/2) << endl;
    }
//    qDebug("Time since last repaint -> %d", t.elapsed() );

    // tempo decorrido desde o último paint
    qreal deltat = t.elapsed();

    if (isAnimating)
        move(deltat);

}

void Widget::paintEvent(QPaintEvent *event)
{
    if (!isAnimating) {
        // posiciona componentes na tela.
        int nx = 70;
        int ny = (this->height() - this->ui->label->height() )/2;
        this->ui->label->move(nx, ny);
        nx = this->ui->plainTextEdit->x();
        this->ui->plainTextEdit->move(nx, ny);
        ny = this->ui->plainTextEdit->y() + this->ui->plainTextEdit->height() + 5;
        this->ui->pushButton->move(nx, ny);
    }

    // para calcular a taxa de FPS
    if (m_frameCount == 0) {
        m_time.start();
    } else {
        if (isRecording && isAnimating) {
            fps = m_time.elapsed() / float(m_frameCount);
    //        qDebug("FPS is %f %d\n", fps, m_frameCount);
        }
    }

    if (isRecording)
        m_frameCount++;

    QPainter painter;
    QBrush background = QBrush(QColor(64, 32, 64));

    painter.begin(this);
    painter.fillRect(event->rect(), background);

    QPen circlePen = QPen(Qt::black);
    QBrush circleBrush = QBrush(Qt::white);
    painter.setPen(circlePen);
    painter.setBrush(circleBrush);

    painter.drawEllipse(QRect(origin, size));

    painter.end();

    t.restart();
}


void Widget::on_pushButton_clicked()
{
    if (termAccepted) {
        // inicia o processo
        isRecording = true;
        isAnimating = true;
        ui->plainTextEdit->setVisible(false);
        ui->pushButton->setVisible(false);
    } else {
        QMessageBox msg;
        msg.setWindowTitle("AVISO");
        msg.setText("Para fazer uso do aplicativo, é necessário aceitar o termo de consentimento.");
        msg.exec();
        QApplication::exit();
    }
}

void Widget::move(qreal deltat)
{
    if ( deltat > timeslice )
    {
        // calculo tamanho do deslocamento
        stepX = floor(this->width()/3000.0 * deltat);
        stepY = floor(this->height()/3000.0 * deltat);

        int maxPosX = this->width() - size.width();
        int maxPosY = this->height() - size.height();

        // delay no inicio do movimento
        if (delayms > 0) {
            // http://stackoverflow.com/questions/3752742/how-do-i-create-a-pause-wait-function-using-qt
#ifdef Q_OS_WIN
            Sleep(uint(delayms));
#else
            struct timespec ts = { delayms / 1000, (delayms % 1000) * 1000 * 1000 };
            nanosleep(&ts, NULL);
#endif
            delayms = 0;
        }

        switch (curr_move) {

        case LRT:
            origin.setX( (origin.x() + stepX < maxPosX ? origin.x() + stepX : maxPosX) );
            if (origin.x() >= maxPosX ) {
                curr_move = TBR;
                delayms = 500;
            }
            break;

        case TBR:
            origin.setY( (origin.y() + stepY < maxPosY ? origin.y() + stepY : maxPosY) );
            if (origin.y() >= maxPosY ) {
                curr_move = RLB;
                delayms = 500;
            }
            break;

        case RLB:
            origin.setX( (origin.x() - stepX > 0 ? origin.x() - stepX : 0) );
            if (origin.x() <= 0 ) {
                curr_move = BTL;
                delayms = 500;
            }
            break;

        case BTL:
            origin.setY( (origin.y() - stepY > 0 ? origin.y() - stepY : 0) );
            if (origin.y() <= 0 ) {
                curr_move = RLTB;
                delayms = 500;
            }
            break;

        case RLTB:
            origin.setX( (origin.x() + stepX < maxPosX ? origin.x() + stepX : maxPosX) );
            origin.setY( (origin.y() + stepY < maxPosY ? origin.y() + stepY : maxPosY) );
            if (origin.x() >= maxPosX && origin.y() >= maxPosY) {
                curr_move = RLB2;
                delayms = 500;
            }
            break;

        case RLB2:
            origin.setX( (origin.x() - stepX > 0 ? origin.x() - stepX : 0) );
            if (origin.x() <= 0 ) {
                curr_move = LRBT;
                delayms = 500;
            }
            break;

        case LRBT:
            origin.setX( (origin.x() + stepX < maxPosX ? origin.x() + stepX : maxPosX) );
            origin.setY( (origin.y() - stepY > 0 ? origin.y() - stepY : 0) );
            if (origin.x() >= maxPosX && origin.y() <= 0 ) {
                curr_move = RLT;
                delayms = 500;
            }
            break;

        case RLT:
            origin.setX( (origin.x() - stepX > 0 ? origin.x() - stepX : 0) );
            if (origin.x() <= 0 )
                curr_move = STOP;
            break;

        case STOP:
            QApplication::exit();
            break;
        }
//    qDebug("%f", origin.x());
        repaint();
    }
}

bool Widget::mostraTermo() {
    QString termo("Ao fornecer meu Nome e E-Mail e clicar no botão Yes, declaro, \n");
    termo.append("por meio deste termo, que concordei em participar na pesquisa de campo \n");
    termo.append("referente ao projeto intitulado Ferramenta para Gaze Tracking Baseada em \n");
    termo.append("Imagens de Baixa Resolução, desenvolvido por Andrey Kuehlkamp.\n\n");
    termo.append("Fui informado(a), ainda, de que a pesquisa é orientada pelo Prof. \n");
    termo.append("Dr. rer. nat Eros Comunello, e que poderei contatar o pesquisador a qualquer \n");
    termo.append("momento que julgar necessário através do email kuehlkamp@gmail.com. \n\n");
    termo.append("Afirmo que aceitei participar por minha própria vontade, sem receber qualquer \n");
    termo.append("incentivo financeiro ou ter qualquer ônus e com a finalidade exclusiva de \n");
    termo.append("colaborar para o sucesso da pesquisa. \n\n");
    termo.append("Fui informado(a) dos objetivos estritamente acadêmicos do projeto, que, em \n");
    termo.append("linhas gerais é desenvolver um software capaz de estimar o foco do olhar do \n");
    termo.append("usuário na tela, usando imagens obtidas pela webcam. \n\n");
    termo.append("Minha colaboração se fará por meio da gravação de um vídeo, que permitirá a \n");
    termo.append("aferição da aplicação de gaze tracking. O acesso e a análise dos dados \n");
    termo.append("coletados se farão apenas pelo pesquisador e/ou seu orientador. \n\n");
    termo.append("Fui ainda informado(a) de que posso me retirar dessa pesquisa a qualquer \n");
    termo.append("momento, sem prejuízo para meu acompanhamento ou sofrer quaisquer sanções \n");
    termo.append("ou constrangimentos.");

    QMessageBox msgBox;
    msgBox.setWindowTitle("TERMO DE CONSENTIMENTO LIVRE E ESCLARECIDO");
    //msgBox.setText("TERMO DE CONSENTIMENTO LIVRE E ESCLARECIDO");
    msgBox.setInformativeText(termo);
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    int ret = msgBox.exec();

    if (ret == QMessageBox::Yes)
        qDebug("Respondeu Sim");
    else if (ret == QMessageBox::No)
        qDebug("Respondeu Não");
    else
        qDebug("Respondeu %d", ret);

    return ret == QMessageBox::Yes;
}

