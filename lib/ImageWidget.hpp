#pragma once

namespace VoteCounter {
class ImageWidget : public QWidget {
    Q_OBJECT
public:
    ImageWidget(QWidget * parent = 0);
    virtual ~ImageWidget();
    QImage& image() { return m_image; }
    void setImage( const QImage& image );
    QPicture& overlay() { return m_overlay; }
    void setOverlay( const QPicture& overlay ) { m_overlay = overlay; update(); }

signals:
    void rectSelected( const QRect& rect );
    void pointClicked( const QPoint& point, Qt::MouseButton button );

protected:
    virtual void paintEvent ( QPaintEvent * event );
    virtual QSize sizeHint () const;
    virtual void resizeEvent ( QResizeEvent * event );

    // mouse
    virtual void mousePressEvent( QMouseEvent * event );
    virtual void mouseReleaseEvent( QMouseEvent * event );
    virtual void mouseMoveEvent( QMouseEvent * event );

    QImage m_image;
    QPicture m_overlay;

    class Detail;
    QScopedPointer<Detail> m_detail;
};
}
