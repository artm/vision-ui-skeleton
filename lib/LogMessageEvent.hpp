#pragma once

#include "QArtmEvent.hpp"

namespace QArtm {

class LogMessageEvent : public Event {
public:
    explicit LogMessageEvent( QtMsgType msgType, const QString& message );

    QtMsgType msgType() const { return m_msgType; }
    const QString& message() const { return m_message; }

protected:
    QtMsgType m_msgType;
    QString m_message;
};

}
