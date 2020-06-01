#-------------------------------------------------
#
# Project created by QtCreator 2012-06-07T16:01:38
#
#-------------------------------------------------

QT       += core gui

TARGET = vlgt_processor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    vlgtprocessor.cpp \
    vlgtvideocalibrator.cpp \
    ../../ScreenData.cpp \
    ../../EyeData.cpp \
    ../../CalibrationPair.cpp \
    ../../CalibrationSequence.cpp \
    ../../LeastSquaresSolver.cpp \
    ../../porestimator.cpp \
    ../../vlgtdatautils.cpp \
    ../../PointRunningAverageStream.cpp \
    ../../Face.cpp \
    ../../IrisFinder.cpp \
    runningaveragestream.cpp \
    irisfinderwrapper.cpp \
    Estimator.cpp

HEADERS  += mainwindow.h \
    vlgtprocessor.h \
    vlgtvideocalibrator.h \
    ../../EyeData.h \
    ../../ScreenData.h \
    ../../ScreenPoint.h \
    ../../CalibrationPair.h \
    ../../CalibrationSequence.h \
    ../../LeastSquaresSolver.h \
    ../../porestimator.h \
    ../../vlgtdatautils.h \
    ../../screendatasmoother.h \
    ../../PointRunningAverageStream.h \
    ../../Face.h \
    ../../IrisFinder.h \
    runningaveragestream.h \
    irisfinderwrapper.h \
    Estimator.h

FORMS    += mainwindow.ui

unix {
    INCLUDEPATH +=  /usr/src/OpenCV-2.3.0/include/
    INCLUDEPATH +=  /home/andrey/NetBeansProjects/vlgt/

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

    LIBS += /home/andrey/NetBeansProjects/vlgt/build/Debug/GNU-Linux-x86/VideoFile.o \
            /home/andrey/NetBeansProjects/vlgt/build/Debug/GNU-Linux-x86/FaceDetector.o \
#            /home/andrey/NetBeansProjects/vlgt/build/Debug/GNU-Linux-x86/Face.o \
            /home/andrey/NetBeansProjects/vlgt/build/Debug/GNU-Linux-x86/GenericDetector.o \
            /home/andrey/NetBeansProjects/vlgt/build/Debug/GNU-Linux-x86/Eye.o \
            /home/andrey/NetBeansProjects/vlgt/build/Debug/GNU-Linux-x86/Mouth.o \
            /home/andrey/NetBeansProjects/vlgt/build/Debug/GNU-Linux-x86/ImageUtils.o \
            /home/andrey/NetBeansProjects/vlgt/build/Debug/GNU-Linux-x86/EyeDetector.o \
            /home/andrey/NetBeansProjects/vlgt/build/Debug/GNU-Linux-x86/FeatureFinder.o \
            /home/andrey/NetBeansProjects/vlgt/build/Debug/GNU-Linux-x86/BlobDetector.o \
            /home/andrey/NetBeansProjects/vlgt/build/Debug/GNU-Linux-x86/_ext/1508022067/EyeProcessor.o


}
