#include "cCameraWorker.h"
#include <QDebug>
#include <QImage>
#include <QDateTime>
#include <QDir>

cCameraWorker *cCameraWorker::m_Instance = nullptr;

cCameraWorker::cCameraWorker(QObject *parent) : QObject(parent)
{
    m_Abort = false;
    m_Method = STREAMANH;
}

cCameraWorker::~cCameraWorker()
{
    abort();
}

cCameraWorker *cCameraWorker::instance()
{
    static QMutex mutex;
    if (m_Instance == nullptr) {
       mutex.lock();
       m_Instance = new cCameraWorker();
       mutex.unlock();
    }
    return m_Instance;
}

void cCameraWorker::drop()
{
    static QMutex mutex;
    mutex.lock();
    delete m_Instance;
    m_Instance = nullptr;
    mutex.unlock();
}

void cCameraWorker::abort()
{
    QMutexLocker locker(&m_Mutex);
    m_Abort = true;
}

void cCameraWorker::requestMethod(int m_method)
{
    QMutexLocker locker(&m_Mutex);
    m_Method = m_method;
}

void cCameraWorker::setKanbanCode(QString kanbanCode)
{
    QMutexLocker locker(&m_Mutex);
    m_kanbanCode = kanbanCode;
}

Mat cCameraWorker::captureImageFromCamera()
{
    QMutexLocker locker(&m_Mutex);
    Mat frames;
    if (!m_Cap.isOpened()) {
       bool retVal = m_Cap.open(0);
       qDebug() << "Camera is opened with RetVal: " << retVal;
       if (retVal) {
           m_Cap.set(CV_CAP_PROP_FRAME_WIDTH,640);
           m_Cap.set(CV_CAP_PROP_FRAME_HEIGHT,480);
           m_Cap >> frames;
       }
    } else {
        m_Cap >> frames;
        cvtColor(frames, frames, CV_BGR2RGB);
    }
    return frames.clone();
}



void cCameraWorker::mainLoop()
{
    forever {
        m_Mutex.lock();
        if (m_Abort)
        {
           emit finished();
           m_Mutex.unlock();
           return;
        }
        m_Mutex.unlock();
        switch (m_Method) {
        case STREAMANH:
            m_Frame = captureImageFromCamera();
            m_QFrame = QPixmap::fromImage(QImage((unsigned char*) m_Frame.data, m_Frame.cols, m_Frame.rows, m_Frame.step, QImage::Format_RGB888));
            emit sigCameraFrameReady(m_QFrame);
            break;
        default:
            break;
        }
        QThread::msleep(50);
    }
}
