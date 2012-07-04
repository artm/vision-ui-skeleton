#pragma once

namespace QArtm {

class CaptureThread : public QThread
{
    Q_OBJECT
    cv::VideoCapture capture;
    bool finish;
public:
    CaptureThread(QObject * parent)
        : QThread(parent)
    { }
    virtual ~CaptureThread();

    void stop() { finish = true; }
signals:
    void frame( const cv::Mat& frame );
    void frame( const QImage& frame );

protected:
    void run();
};

}
