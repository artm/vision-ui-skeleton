#include "LogMessageEvent.hpp"

using namespace QArtm;

LogMessageEvent::LogMessageEvent( QtMsgType msgType, const QString& message )
    : Event(LOG_MESSAGE), m_msgType(msgType), m_message(message)
{
}

