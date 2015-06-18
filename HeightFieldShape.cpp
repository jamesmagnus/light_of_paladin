#include "StdLibAndNewOperator.h"
#include "HeightFieldShape.h"
#include "TerrainMgr.h"

#include <algorithm>

#include <OgreTerrainGroup.h>

HeightFieldShape::HeightFieldShape(TerrainMgr const *pTerrains, std::pair<int, int> const& coo)
{
	mpHeightData = LOP_NEW float*[TAILLE_CHUNK];

	for (int i=0; i<TAILLE_CHUNK; ++i)
	{
		mpHeightData[i] = LOP_NEW float[TAILLE_CHUNK];
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
