#include "HeightFieldShape.h"
#include "GestionnaireTerrain.h"

#include <algorithm>

#include <OgreTerrainGroup.h>

HeightFieldShape::HeightFieldShape(hkpSampledHeightFieldBaseCinfo const& rInfo, GestionnaireTerrain const *pTerrains, std::pair<int, int> const& coo): hkpSampledHeightFieldShape(rInfo)
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
			mpHeightData[i][j] = pTerrains->getTerrains()->getTerrain(0,0)->getHeightAtWorldPosition(static_cast<Ogre::Real>(coo.first*TAILLE_CHUNK +i), 5000.0f, static_cast<Ogre::Real>(coo.second*TAILLE_CHUNK +j));
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

std::pair<float, float> HeightFieldShape::getMinMaxHeight() const
{
	float min = mpHeightData[0][0], max = mpHeightData[0][0];

	for (int i=0; i<TAILLE_CHUNK; ++i)
	{
		for (int j=0; j<TAILLE_CHUNK; ++j)
		{
			if (mpHeightData[i][j] < min)
			{
				min = mpHeightData[i][j];
			}

			if (mpHeightData[i][j] > max)
			{
				max = mpHeightData[i][j];
			}
		}
	}

	return std::make_pair(min, max);
}
