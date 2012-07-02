#pragma once

namespace QArtm {

class Pretty {
public:
    static QString timestamp(bool date=false);
    static QString ms(int milliseconds);
};

}
