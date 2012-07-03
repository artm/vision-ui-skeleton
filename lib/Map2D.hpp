#pragma once

namespace QArtm {

template<class K1, class K2, class V>
class Map2D : public QMap< QPair<K1,K2>, V > {
public:
    typedef QPair<K1,K2> Key;

    V& at( const K1& k1, const K2& k2 ) {
        return this->operator[]( Key(k1,k2) );
    }
    const V at( const K1& k1, const K2& k2 ) const {
        return this->operator[]( Key(k1,k2) );
    }
    bool contains( const K1& k1, const K2& k2 ) const {
        Key k(k1,k2);
        return QMap< Key, V>::contains( k );
    }
};

}
