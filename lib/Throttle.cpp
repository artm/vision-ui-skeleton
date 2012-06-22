#include "Throttle.hpp"

using namespace QArtm;

Throttle::Throttle( int ms )
    : m_throttleTime(ms)
{
    start();
}

bool Throttle::mayI()
{
    if (elapsed() >= m_throttleTime) {
        restart();
        return true;
    }
    return false;
}

