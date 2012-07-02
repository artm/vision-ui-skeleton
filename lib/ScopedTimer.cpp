#include "ScopedTimer.hpp"
#include "Pretty.hpp"

using namespace QArtm;

ScopedTimer::ScopedTimer(const QString& workTitle)
    : m_workTitle(workTitle)
{
    m_time.start();
}

ScopedTimer::~ScopedTimer()
{
    qDebug() << qPrintable( QString("Task '%1' finished in %2")
                            .arg(m_workTitle).arg(Pretty::ms( m_time.elapsed() )) );
}
