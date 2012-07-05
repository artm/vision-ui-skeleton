#pragma once

namespace QArtm {

class ObjectDetector : public QObject {
    Q_OBJECT
public:
    ObjectDetector( QObject * parent = 0 );
    virtual ~ObjectDetector();
    QWidget * makeWidget();

public slots:
    void frame(const cv::Mat& cvFrame);
    void loadCascade( const QString& path );

signals:
    void objectsDetected(const QList<QRect>& objects, const QImage& image);

protected:
    class Detail;
    QScopedPointer<Detail> m_detail;
};

}
