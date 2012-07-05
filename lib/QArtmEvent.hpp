#pragma once

namespace QArtm {

class Event : public QEvent {
public:
    enum Type {
        __SENTINEL__ = QEvent::User,
        LOG_MESSAGE,
        // Applications can extend events
        APP_BASE
    };

    explicit Event(Type type);

    // event should be new'd and the application will take over its ownership
    void broadcast();
};

}
