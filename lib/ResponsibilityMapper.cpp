#include "ResponsibilityMapper.hpp"

using namespace QArtm;

ResponsibilityMapper::ResponsibilityMapper( QObject * parent, bool setParentProperties )
    : QObject(parent), m_setParentProperties(setParentProperties)
{
}

ResponsibilityMapper::~ResponsibilityMapper(){ }

