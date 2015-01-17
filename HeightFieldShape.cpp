#include "HeightFieldShape.h"
#include "GestionnaireTerrain.h"

HeightFieldShape::HeightFieldShape(hkpSampledHeightFieldBaseCinfo const& rInfo, GestionnaireTerrain const *mTerrains): hkpSampledHeightFieldShape(rInfo)
{
	mpHeightData = mTerrains->getTerrains()->getTerrain(0, 1)->getHeightData();
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
	return mpHeightData[x*257+z]/(5000.0f/257.0f);
}
