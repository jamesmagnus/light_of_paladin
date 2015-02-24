#pragma once

#include <Physics2012/Collide/hkpCollide.h>
#include <Physics2012/Collide/Shape/HeightField/SampledHeightField/hkpSampledHeightFieldShape.h>

#include <boost/noncopyable.hpp>

#include "Structures.h"

class GestionnaireTerrain;
class hkpSampledHeightFieldBaseCinfo;
class CollideSpheresInput;
class SphereCollisionOutput;

/* Classe pour représenter un chunk de terrain dans Havok */
/* Hérite de hkSampleHeightFieldShape */
/* Sémantique d'entité, hérite boost::noncopyable */
class HeightFieldShape: public hkpSampledHeightFieldShape, private boost::noncopyable
{
private:
	float **mpHeightData;

public:

	/* Constructeur */
	/* rInfo, référence sur une structure qui décrit les paramètres de la HeightMap */
	/* pTerrain, adresse du gestionnaire de terrains */
	/* cooHeightField, paire de coordonnées (en chunk) de la zone de terrain à créer */
	HeightFieldShape(hkpSampledHeightFieldBaseCinfo const& rInfo, GestionnaireTerrain const *pTerrains, std::pair<int, int> coo);

	/* Destructeur */
	virtual ~HeightFieldShape();

	/* Récupération de la hauteur du terrain */
	HK_FORCE_INLINE hkReal getHeightAtImpl(int x, int z) const;

	/* Sens de découpage des rectangles en triangles */
	HK_FORCE_INLINE hkBool getTriangleFlipImpl() const;

	/* Détermine la collision avec une sphère */
	/* Fonction par défaut de Havok */
	virtual void collideSpheres(CollideSpheresInput const& input, SphereCollisionOutput* outputArray) const;
};

