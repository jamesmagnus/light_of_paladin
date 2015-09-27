#pragma once

#include <boost/core/noncopyable.hpp>

#include <btBulletDynamicsCommon.h>

#include "Structures.h"

class TerrainMgr;

/* Classe pour  */
/* Hérite de  */
/* Sémantique d'entité, hérite boost::noncopyable */
class HeightFieldShape: private boost::noncopyable
{
private:
	float **mpHeightData;

public:

	/* Constructeur */
	/* rInfo, référence sur une structure qui décrit les paramètres de la HeightMap */
	/* pTerrain, adresse du gestionnaire de terrains */
	/* cooHeightField, paire de coordonnées (en chunk) de la zone de terrain à créer */
	HeightFieldShape(TerrainMgr const *pTerrains, std::pair<int, int> const& coo);

	/* Destructeur */
	virtual ~HeightFieldShape();

	/* Renvoie la hauteur minimale et maximale du terrain */
	std::pair<float, float> getMinMaxHeight() const;
};

