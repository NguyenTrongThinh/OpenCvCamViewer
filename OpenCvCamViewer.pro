QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cCameraViewer.cpp \
    cCameraWorker.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    cCameraViewer.h \
    cCameraWorker.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

LIBS += -lopencv_core        \
        -lopencv_highgui     \
        -lopencv_imgcodecs   \
        -lopencv_imgproc     \
        -lopencv_features2d  \
        -lopencv_calib3d    \
        -lopencv_videoio

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix:!android: desktop.path = /usr/share/applications
desktop.files = data/camera-demo.desktop
!isEmpty(desktop.path): INSTALLS += desktop

DISTFILES += \
    data/camera-demo.desktop

RESOURCES += \
    images.qrc
