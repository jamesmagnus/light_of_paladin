#include "HeightFieldShape.h"

#include "GestionnaireTerrain.h"
#include <OgreTerrainGroup.h>

HeightFieldShape::HeightFieldShape(hkpSampledHeightFieldBaseCinfo const& rInfo, GestionnaireTerrain const *pTerrains, std::pair<int, int> coo): hkpSampledHeightFieldShape(rInfo)
{
	mpHeightData = new float*[TAILLE_CHUNK];

	for (int i=0; i<TAILLE_CHUNK; ++i)
	{
		mpHeightData[i] = new float[TAILLE_CHUNK];
	}

	for (int i=0; i<TAILLE_CHUNK; ++i)
	{
		for (int j=0; j<TAILLE_CHUNK; ++j)
		{
			mpHeightData[i][j] = pTerrains->getTerrains()->getTerrain(0,0)->getHeightAtWorldPosition(coo.first*TAILLE_CHUNK +i, 5000.0f, coo.second*TAILLE_CHUNK +j);
		}
	}
}

HeightFieldShape::~HeightFieldShape()
{
	for (int i=0; i<TAILLE_CHUNK; ++i)
	{
		delete[] mpHeightData[i];
		mpHeightData[i] = nullptr;
	}

	delete[] mpHeightData;
	mpHeightData = nullptr;
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
	return mpHeightData[x][z];
}
