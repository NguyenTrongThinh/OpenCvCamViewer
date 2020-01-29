#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_CameraViewer = new cCameraViewer();
    m_CameraViewer->clear();
    m_CameraViewer->setPixmap(QPixmap(":/images/resource/loading.png"));
    ui->vlCamera->addWidget(m_CameraViewer);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ShowImage(QPixmap pixmap)
{
    if (m_CameraViewer != nullptr) {
        if (m_CameraViewer != nullptr) {
            m_CameraViewer->setPixmap(pixmap);
            m_CameraViewer->setScaledContents( true );
            m_CameraViewer->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
        }
    }

}

