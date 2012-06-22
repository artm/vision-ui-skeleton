#pragma once

namespace QArtm {

class Throttle : public QTime {
public:
    Throttle( int ms );
    bool mayI();
protected:
    int m_throttleTime;
};

}
