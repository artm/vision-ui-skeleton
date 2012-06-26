#pragma once

namespace QArtm {

class ResponsibilityMapper : public QObject {
    Q_OBJECT
public:
    ResponsibilityMapper(QObject * parent = 0, bool setParentProperties = false);
    virtual ~ResponsibilityMapper();

    template<typename T>
    void receiveImpl( T val )
    {
        QString name = sender()->objectName();

        if (name.isEmpty()) {
            qWarning() << "Irresponsible sender" << sender()
                << "(set objectName to accept responsibility)";
            return;
        }

        if (m_setParentProperties && parent())
            parent()->setProperty( qPrintable(name), val );

        emit received( name, val );
    }

public slots:
    void receive( int val ) { receiveImpl(val); }
    void receive( double val ) { receiveImpl(val); }
    void receive( const QString& val ) { receiveImpl(val); }
    void receive( bool val ) { receiveImpl(val); }
    void receive( const QRect& val ) { receiveImpl(val); }
signals:
    void received( const QString&, int );
    void received( const QString&, double );
    void received( const QString&, const QString& );
    void received( const QString&, bool );
    void received( const QString&, const QRect& );
protected:
    bool m_setParentProperties;
};

}
