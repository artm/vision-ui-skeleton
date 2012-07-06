#pragma once

namespace QArtm {

class PolygonSelector : public QWidget {
    Q_OBJECT
public:
    PolygonSelector( QWidget * parent );
    virtual ~PolygonSelector();
    QPolygonF polygon() const { return m_polygon; }
    QPolygonF originalPolygon() const { return m_original; }
    void setPolygon( const QPolygonF& poly );


protected:
    virtual bool eventFilter(QObject *obj, QEvent *event);
    virtual void paintEvent ( QPaintEvent * event );
    virtual void mouseMoveEvent ( QMouseEvent * event );
    virtual void mousePressEvent ( QMouseEvent * event );
    virtual void mouseReleaseEvent ( QMouseEvent * event );

    QPolygonF m_polygon, m_original;
    int m_dragCorner;
};

}
