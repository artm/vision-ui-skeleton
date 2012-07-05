#pragma once

namespace QOpenCV {
QImage wrapImage( const cv::Mat& image );
inline cv::Rect toCv( const QRect& rect )
{
    return cv::Rect( cv::Point(rect.x(), rect.y()), cv::Size(rect.width(), rect.height())  );
}

inline cv::Point toCv( const QPoint& point )
{
    return cv::Point( point.x(), point.y() );
}

inline QPoint toQt( const cv::Point& point )
{
    return QPoint( point.x, point.y );
}
inline QRect toQt( const cv::Rect& rect )
{
    return QRect( rect.x, rect.y, rect.width, rect.height );
}

inline cv::Mat select( cv::Mat& orig, const QRect& roi )
{
    return cv::Mat(orig, toCv(roi));
}

inline QPolygon toQPolygon( const std::vector< cv::Point >& contour )
{
    QPolygon poly;
    for(int i=0; i< contour.size(); i++) {
        poly.append( QOpenCV::toQt( contour[i] ) );
    }
    return poly;
}

cv::Rect grow( const cv::Rect& rect, double scale );

}
