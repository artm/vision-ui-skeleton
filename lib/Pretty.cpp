#include "Pretty.hpp"

using namespace QArtm;

QString Pretty::timestamp(bool date)
{
    return QDateTime::currentDateTime()
        .toString( QString(date ? "yyyy-MM-dd " : "") + "hh:mm:ss.zzz");
}
