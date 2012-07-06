#include "PolygonSelector.hpp"

using namespace QArtm;


PolygonSelector::PolygonSelector( QWidget * parent )
    : QWidget(parent), m_dragCorner(-1)
{
    Q_ASSERT(parent);
    resize( parent->size() );
    parent->installEventFilter(this);
}

PolygonSelector::~PolygonSelector()
{
}

bool PolygonSelector::eventFilter(QObject *obj, QEvent *ev )
{
    if (obj == parent() && ev->type() == QEvent::Resize) {
        QResizeEvent * rev = dynamic_cast<QResizeEvent*>(ev);
        resize( rev->size().width(), rev->size().height() );
    }
    return QWidget::eventFilter(obj, ev);
}

void PolygonSelector::setPolygon( const QPolygonF& poly )
{
    m_polygon = m_original = poly;
    update();
}

void PolygonSelector::paintEvent ( QPaintEvent * event )
{
    QPolygonF scaledPoly;
    foreach(QPointF p, m_polygon) {
        scaledPoly << QPoint( qBound(0, (int)(p.x() * width()), width()-1),
                              qBound(0, (int)(p.y() * height()), height()-1) );
    }

    QPainter painter(this);
    painter.drawPolygon( scaledPoly );
    int i = 0;
    QRectF digitRect;
    foreach( QPointF p, scaledPoly ) {
        QString t = QString("%1").arg(++i);
        digitRect = painter.boundingRect( QRectF( p, QSizeF(1,1) ), t );

        digitRect.moveLeft( std::max( 0, (int)digitRect.x() ) );
        digitRect.moveRight( std::min( width()-1, (int)digitRect.right() ) );
        digitRect.moveTop( std::max( 0, (int)digitRect.y() ) );
        digitRect.moveBottom( std::min( height()-1, (int)digitRect.bottom() ) );

        painter.drawText( digitRect, t );
    }
}

void PolygonSelector::mouseMoveEvent ( QMouseEvent * event )
{
    if (m_dragCorner >= 0) {
        QPointF p = event->posF();
        p.setX(p.x() / width());
        p.setY(p.y() / height());
        m_polygon[m_dragCorner] = p;
        update();
    }
}

void PolygonSelector::mousePressEvent ( QMouseEvent * event )
{
    QPointF p = event->posF();
    p.setX(p.x() / width());
    p.setY(p.y() / height());

    m_dragCorner = -1;
    if (m_polygon.containsPoint(p, Qt::OddEvenFill)) {
        // find closest corner...
        float mind = -1.0;
        for(int i = 0; i<m_polygon.size(); ++i) {
            QPointF corner = m_polygon[i];
            float d = (corner - p).manhattanLength();
            if (mind<0 || mind > d) {
                mind = d;
                m_dragCorner = i;
            }
        }
    }
}

void PolygonSelector::mouseReleaseEvent ( QMouseEvent * event )
{
    m_dragCorner = -1;
}

