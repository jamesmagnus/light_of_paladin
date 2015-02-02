#include "HeightFieldShape.h"

#include "GestionnaireTerrain.h"
#include <OgreTerrainGroup.h>

HeightFieldShape::HeightFieldShape(hkpSampledHeightFieldBaseCinfo const& rInfo, GestionnaireTerrain const *pTerrains, Ogre::Vector2 cooHeightField): hkpSampledHeightFieldShape(rInfo)
{
	mCooHeightField = cooHeightField;
	mpHeightData = pTerrains->getTerrains()->getTerrain(0, 0)->getHeightData();	//TODO ne récupérer qu'un chunk de 500 sur 500
}

HeightFieldShape::~HeightFieldShape()
{
}

HK_FORCE_INLINE hkBool HeightFieldShape::getTriangleFlipImpl() const 
{
	return false;
}

void HeightFieldShape::collideSpheres(CollideSpheresInput const& input, SphereCollisionOutput* outputArray) const 
{
	return hkSampledHeightFieldShape_collideSpheres(*this, input, outputArray);
}

HK_FORCE_INLINE hkReal HeightFieldShape::getHeightAtImpl(int x, int z) const 
{
	return mpHeightData[x*TAILLE_CHUNK+z] / ((float)TAILLE_MONDE/(float)TAILLE_CHUNK);
}
