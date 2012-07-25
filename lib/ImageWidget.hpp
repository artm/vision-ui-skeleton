#pragma once

namespace QArtm {
class ImageWidget : public QWidget {
    Q_OBJECT
public:
    ImageWidget(QWidget * parent = 0);
    virtual ~ImageWidget();
    QImage& image() { return m_image; }
    QPicture& overlay() { return m_overlay; }

public slots:
    void setImage( const QImage& image );
    void setOverlay( const QPicture& overlay ) { m_overlay = overlay; update(); }
    void clearOverlay( ) { m_overlay = QPicture(); }

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
