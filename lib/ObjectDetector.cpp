#include <QOpenCV.hpp>
#include <Named.hpp>
#include <ResponsibilityMapper.hpp>
#include "ObjectDetector.hpp"

using namespace QArtm;

struct ObjectDetector::Detail {
    cv::CascadeClassifier classifier;
    ResponsibilityMapper * mapper;
};

ObjectDetector::ObjectDetector( QObject * parent )
    : QObject(parent), m_detail( new Detail )
{
    m_detail->mapper = new ResponsibilityMapper( this, true );
}

ObjectDetector::~ObjectDetector()
{}

void ObjectDetector::frame(const cv::Mat& cvFrame)
{
    double scale = property("preScale").toDouble(),
           scaleFactor = property("scaleFactor").toDouble();
    int minNeighbors = property("minNeighbors").toInt(),
        minSize = property("minSize").toDouble() * scale,
        maxSize = property("maxSize").toDouble() * scale;

    // preprocess
    cv::Mat greyFrame;
    cv::cvtColor( cvFrame, greyFrame, CV_RGB2GRAY );
    cv::resize( greyFrame, greyFrame, cv::Size(0,0), scale, scale );
    cv::normalize( greyFrame, greyFrame, 0, 255, cv::NORM_MINMAX );

    std::vector< cv::Rect > cvResults;
    if (!m_detail->classifier.empty()) {
        m_detail->classifier
            .detectMultiScale( greyFrame ,
                               cvResults,
                               scaleFactor,
                               minNeighbors,
                               0, // flags,
                               cv::Size(minSize, minSize),
                               cv::Size(maxSize, maxSize));
    }

    // emit results
    QList<QRect> results;
    foreach(cv::Rect r, cvResults) {
        r.x /= scale;
        r.y /= scale;
        r.width /= scale;
        r.height /= scale;
        results << QOpenCV::toQt(r);
    }
    const QImage image = QOpenCV::wrapImage(cvFrame);
    emit objectsDetected( results, image );
}

void ObjectDetector::loadCascade( const QString& path )
{
    m_detail->classifier.load( path.toStdString() );
}

QWidget * ObjectDetector::makeWidget()
{
    QWidget * panel = new QWidget;
    QFormLayout * form = new QFormLayout( panel );

#define _M(type) .connect(SIGNAL( valueChanged(type)), m_detail->mapper, SLOT( receive(type) ) )
    form->addRow( "Pre-scale", NAMED( "preScale", new QDoubleSpinBox )
                  _M(double)
                  ("minimum", 0.1) ("maximum", 1.0) ("value", 0.3) );
    form->addRow( "Detection Scale Factor", NAMED( "scaleFactor", new QDoubleSpinBox )
                  _M(double)
                  ("minimum", 1.01) ("maximum", 2.0) ("value", 1.1) );
    form->addRow( "Min Neighbors", NAMED( "minNeighbors", new QSpinBox )
                  _M(int)
                  ("minimum", 0) ("maximum", 10) ("value", 3) );
    form->addRow( "Min Face Size", NAMED( "minSize", new QSpinBox )
                  _M(int)
                  ("minimum", 0) ("maximum", 100) ("value", 20) );
    form->addRow( "Max Face Size", NAMED( "maxSize", new QSpinBox )
                  _M(int)
                  ("minimum", 0) ("maximum", 1024) ("value", 0) );
#undef _M



    return panel;
}
