#include "mainwindow.h"

#include <QApplication>
#include <QThread>
#include "cCameraWorker.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Camera Viewer");

    QThread m_CameraThread;
    cCameraWorker *m_CameraWorker = cCameraWorker::instance();
    m_CameraWorker->moveToThread(&m_CameraThread);
    QObject::connect(&m_CameraThread, SIGNAL(started()), m_CameraWorker, SLOT(mainLoop()));
    QObject::connect(m_CameraWorker, SIGNAL(finished()), &m_CameraThread, SLOT(quit()), Qt::DirectConnection);


    QObject::connect(m_CameraWorker, &cCameraWorker::sigCameraFrameReady, &w, &MainWindow::on_ShowImage);

    w.show();
    m_CameraThread.start();
    return a.exec();
}
