#include "artmgl.h"
#include <CaptureThread.hpp>

using namespace QArtm;

struct ArtmGL::Detail {
    CaptureThread * capture_thread;
    cv::Mat input_frame, paint_frame;
    QImage input_image;
};

static bool greyTableInit = false;
static QVector<QRgb> greyTable;
QImage CvMat2QImage(const cv::Mat& cvmat);

ArtmGL::ArtmGL(QWidget *parent)
    : QWidget(parent),
    detail( new Detail() )
{
    detail->capture_thread = new CaptureThread(this);
    detail->capture_thread->start();
}

ArtmGL::~ArtmGL()
{

    detail->capture_thread->stop();
    detail->capture_thread->wait(3000);
}

void ArtmGL::pump()
{
    /*
    detail->capture >> detail->input_frame;
    detail->input_image = CvMat2QImage( detail->input_frame );
    update();
    */
}

void ArtmGL::paintEvent ( QPaintEvent * event )
{
    QPainter painter(this);
    painter.drawImage(rect(), detail->input_image, detail->input_image.rect());
}

QImage CvMat2QImage(const cv::Mat& cvmat)
{
    int height = cvmat.rows;
    int width = cvmat.cols;

    if (cvmat.depth() == CV_8U && cvmat.channels() == 3) {
        QImage img((const uchar*)cvmat.data, width, height, cvmat.step.p[0], QImage::Format_RGB888);
        return img.rgbSwapped();
    } else if (cvmat.depth() == CV_8U && cvmat.channels() == 1) {
        if (!greyTableInit) {
            for (int i = 0; i < 256; i++){
                greyTable.push_back(qRgb(i, i, i));
            }
        }
        QImage img((const uchar*)cvmat.data, width, height, cvmat.step.p[0],
                QImage::Format_Indexed8);
        img.setColorTable(greyTable);
        return img;
    } else {
        qWarning() << "Image cannot be converted.";
        return QImage();
    }
}

