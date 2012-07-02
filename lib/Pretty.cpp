#include "Pretty.hpp"

using namespace QArtm;

QString Pretty::timestamp(bool date)
{
    return QDateTime::currentDateTime()
        .toString( QString(date ? "yyyy-MM-dd " : "") + "hh:mm:ss.zzz");
}

QString Pretty::ms(int total)
{
    if (total < 1000) {
        return QString("%1 ms").arg(total);
    }
    int s = total / 1000;
    if (s < 60) {
        int ms = total % 1000;
        return QString("%1.%2 sec").arg(s).arg(ms,3,10,QChar('0'));
    }
    int m = s / 60;
    if (m < 5) {
        return QString("%1m%2").arg(m).arg(s,2,10,QChar('0'));
    }
    int h = m / 60;
    return QString("%1h%2").arg(h).arg(m,2,10,QChar('0'));
}
