#include "QArtmEvent.hpp"

using namespace QArtm;

Event::Event(Type type) : QEvent((QEvent::Type) type)
{
}

// event should be new'd and the application will take over its ownership
void Event::broadcast()
{
    qApp->postEvent(qApp, this);
}

