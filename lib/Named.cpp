#include "Named.hpp"

using namespace QArtm;

Named::Named( const QString& name, QObject * obj )
    : m_object( obj )
{
    obj->setObjectName(name);
}

Named::~Named()
{

}

Named& Named::set( const QString& property, const QVariant& value )
{
    m_object->setProperty( qPrintable(property), value );
    return *this;
}

Named& Named::connect(const char * signal, QObject * receiver, const char * method, Qt::ConnectionType type)
{
    QObject::connect( m_object, signal, receiver, method, type );
    return *this;
}
