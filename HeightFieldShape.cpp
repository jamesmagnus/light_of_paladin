#include "HeightFieldShape.h"
#include "GestionnaireTerrain.h"

HeightFieldShape::HeightFieldShape(hkpSampledHeightFieldBaseCinfo const& rInfo, GestionnaireTerrain const *mTerrains): hkpSampledHeightFieldShape(rInfo)
{
	mpHeightData = mTerrains->getTerrains()->getTerrain(0, 0)->getHeightData();
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
	return mpHeightData[x*TAILLE_IMG_HEIGHTMAP+z] / ((float)TAILLE_MONDE/(float)TAILLE_IMG_HEIGHTMAP);
}
