#pragma once

namespace QArtm {

class ScopedTimer {
public:
    ScopedTimer(const QString& workTitle);
    ~ScopedTimer();
protected:
    QString m_workTitle;
    QTime m_time;
};

}
