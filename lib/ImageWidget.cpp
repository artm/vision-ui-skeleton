#include "ImageWidget.hpp"

namespace VoteCounter {

struct ImageWidget::Detail {
    bool resizing;

    bool dragging;
    QPoint dragStart, dragPos;
    QPen ribbonPen;

    Detail()
        : resizing(false),
        dragging(false),
        ribbonPen( QBrush(QColor("white")), 1, Qt::DashLine )
    {}
};

ImageWidget::ImageWidget(QWidget * parent)
    : QWidget(parent), m_detail( new Detail )
{
}

ImageWidget::~ImageWidget()
{}

void ImageWidget::paintEvent ( QPaintEvent * event )
{
    QPainter painter(this);
    painter.setRenderHint( QPainter::SmoothPixmapTransform );

    // draw the whole thing
    QSize targetSize(m_image.size());
    targetSize.scale( size(), Qt::KeepAspectRatio );

    QPoint targetOffs(0,0);

    painter.drawImage( QRect(targetOffs, targetSize), m_image, m_image.rect());
    painter.save();
    painter.scale( (float)targetSize.width() / m_image.width(),
                   (float)targetSize.height() / m_image.height());
    painter.drawPicture( targetOffs, m_overlay );
    painter.restore();

    if (m_detail->dragging) {
        painter.setPen( m_detail->ribbonPen );
        painter.drawRect( QRect( m_detail->dragStart, m_detail->dragPos ) );
    }
}

QSize ImageWidget::sizeHint () const
{
    return m_image.size();
}

void ImageWidget::setImage( const QImage& image )
{
    m_image = image;
    update();
}

void ImageWidget::resizeEvent ( QResizeEvent * event )
{
    if (m_detail->resizing) {
        QWidget::resizeEvent(event);
    } else {
        m_detail->resizing = true;
        QSize targetSize(m_image.size());
        targetSize.scale( event->size(), Qt::KeepAspectRatio );
        resize( targetSize );
        m_detail->resizing = false;
    }
}
void ImageWidget::mousePressEvent( QMouseEvent * event )
{
    m_detail->dragging = true;
    m_detail->dragStart = m_detail->dragPos = event->pos();
}

void ImageWidget::mouseReleaseEvent( QMouseEvent * event )
{
    m_detail->dragging = false;
    update();
    QSize targetSize(m_image.size());
    targetSize.scale( size(), Qt::KeepAspectRatio );
    // convert current rectangle to original image coordinates
    float sx = (float)m_image.width() / targetSize.width();
    float sy = (float)m_image.height() / targetSize.height();

    if ( (m_detail->dragStart-m_detail->dragPos).manhattanLength() < 2 )
        emit pointClicked( QPoint( m_detail->dragStart.x() * sx,
                           m_detail->dragStart.y() * sy),
                event->button());
    else
        emit rectSelected( QRect(
                QPoint( m_detail->dragStart.x() * sx,
                        m_detail->dragStart.y() * sy),
                QPoint( m_detail->dragPos.x() * sx,
                        m_detail->dragPos.y() * sy)
                ).intersected( m_image.rect() ) );
}

void ImageWidget::mouseMoveEvent( QMouseEvent * event )
{
    m_detail->dragPos = event->pos();
    update();
}

}
