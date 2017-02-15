
#include "VideoObject.h"

namespace Video
{

VideoObject::VideoObject() :
    m_firstFrame(0),
    m_listeCoordonnees(),
    m_listeVecteurVitesse()
{
}

VideoObject::VideoObject(int firstFrame) :
    m_firstFrame(firstFrame),
    m_listeCoordonnees(),
    m_listeVecteurVitesse()

{
}

VideoObject::~VideoObject()
{
}

} // namespace Video
