#-------------------------------------------------
#
# Project created by QtCreator 2012-04-14T16:35:33
#
#-------------------------------------------------

QT       += core gui

TARGET = vlgtCollector
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    window.cpp \
    capture.cpp

HEADERS  += widget.h \
    window.h \
    capture.h

FORMS    += widget.ui

unix {
    INCLUDEPATH +=  /usr/src/OpenCV-2.3.0/include/

    LIBS += -L/usr/local/LIBS \
        -lopencv_core \
        -lopencv_imgproc \
        -lopencv_highgui \
        -lopencv_ml \
        -lopencv_video \
        -lopencv_features2d \
        -lopencv_calib3d \
        -lopencv_objdetect \
        -lopencv_contrib \
        -lopencv_legacy \
        -lopencv_flann

}

windows {
    INCLUDEPATH += C:\src\opencv231\build\include

    LIBS += C:\opencv\lib\Debug\opencv_calib3d231d.lib \
            C:\opencv\lib\Debug\opencv_contrib231d.lib \
            C:\opencv\lib\Debug\opencv_core231d.lib \
            C:\opencv\lib\Debug\opencv_features2d231d.lib \
            C:\opencv\lib\Debug\opencv_flann231d.lib \
            C:\opencv\lib\Debug\opencv_gpu231d.lib \
            C:\opencv\lib\Debug\opencv_haartraining_engined.lib \
            C:\opencv\lib\Debug\opencv_highgui231d.lib \
            C:\opencv\lib\Debug\opencv_imgproc231d.lib \
            C:\opencv\lib\Debug\opencv_legacy231d.lib \
            C:\opencv\lib\Debug\opencv_ml231d.lib \
            C:\opencv\lib\Debug\opencv_objdetect231d.lib \
            C:\opencv\lib\Debug\opencv_ts231d.lib \
            C:\opencv\lib\Debug\opencv_video231d.lib

}
