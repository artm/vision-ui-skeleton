#pragma once

namespace QArtm {

class Named {
public:
    Named( const QString& name, QObject * obj );
    virtual ~Named();
    Named& set( const QString& property, const QVariant& value );
    Named& operator() ( const QString& property, const QVariant& value )
    { return set(property, value); }
    template<class T> operator T* ()
    { return qobject_cast<T*>(m_object); }
    Named& connect(const char * signal, QObject * receiver, const char * method,
                   Qt::ConnectionType type = Qt::AutoConnection );
protected:
    QObject * m_object;
};

#define NAMED( name, obj ) (QWidget*)QArtm::Named( name, obj )

}
