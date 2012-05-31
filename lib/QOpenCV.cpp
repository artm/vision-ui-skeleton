#include "QOpenCV.hpp"

namespace QOpenCV {

static bool s_greyTableInit = false;
static QVector<QRgb> s_greyTable;
QImage wrapImage( cv::Mat& cvmat)
{
    int height = cvmat.rows;
    int width = cvmat.cols;

    if (cvmat.depth() == CV_8U && cvmat.channels() == 3) {
        QImage img((const uchar*)cvmat.data, width, height, cvmat.step.p[0], QImage::Format_RGB888);
        return img.rgbSwapped();
    } else if (cvmat.depth() == CV_8U && cvmat.channels() == 1) {
        if (!s_greyTableInit) {
            for (int i = 0; i < 256; i++){
                s_greyTable.push_back(qRgb(i, i, i));
            }
        }
        QImage img((const uchar*)cvmat.data, width, height, cvmat.step.p[0], QImage::Format_Indexed8);
        img.setColorTable(s_greyTable);
        return img;
    } else {
        qWarning() << "Image cannot be converted.";
        return QImage();
    }
}

}
