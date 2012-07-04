#include "CaptureThread.hpp"
#include <QOpenCV.hpp>

using namespace QArtm;

void CaptureThread::run()
{
    qDebug() << "Starting capture thread";
    finish = false;
    capture.open(0);
    while (!finish) {
        cv::Mat f;
        if (capture.read(f)) {
            emit frame( f );
            emit frame( QOpenCV::wrapImage( f ) );
        }
    }
}

CaptureThread::~CaptureThread()
{
    stop();
}
