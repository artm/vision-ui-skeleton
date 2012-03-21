#pragma once

#include <QWidget>

class ArtmGL : public QWidget {
    Q_OBJECT        // must include this if you use Qt signals/slots

public:
    ArtmGL(QWidget *parent = 0);
    virtual ~ArtmGL();

protected:
    void paintEvent ( QPaintEvent * event );

protected slots:
    void pump();

private:
    class Detail;
    QScopedPointer<Detail> detail;
};
