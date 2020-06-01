#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QTimer>
#include <QProcess>
#include "vlgtprocessor.h"
#include "vlgtvideocalibrator.h"
#include "porestimator.h"
#include "runningaveragestream.h"
#include "Estimator.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QSettings settings;
    QString sourceFolder;
    QString targetFolder;
    QString baseFileName;    
    
private slots:
    void on_actionPasta_origem_triggered();
    void on_actionPasta_destino_triggered();
    void on_actionNome_de_arquivo_triggered();
    void on_actionListaArquivos_triggered();
    void on_actionLocateEyeFeatures_triggered();
    void on_actionEstimatePOR_triggered();
    void videoRefresh();
    void setFixRef(int ref);
    void on_sliderFaceBrightnessAlpha_valueChanged(int value);
    void on_sliderIrisBrightnessAlpha_valueChanged(int value);

    void on_actionCancelar_triggered();

    void on_sliderIrisBrightnessAlpha_actionTriggered(int action);
    void updateOutput();

signals:
    void actionCancelChanged(bool newValue);

private:
    void calibrate();

    bool cancelAction;
    Ui::MainWindow *ui;
    VlgtProcessor *vlgtProcessor;
    VlgtVideoCalibrator *vlgtCalibrator;
    cv::Mat estimatorOutputImage;
    cv::Mat estimatorOutputVideo;
    QTimer videoTimer;
    FixedReference fixRef;
};

#endif // MAINWINDOW_H
