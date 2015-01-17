#pragma once

#include <Physics2012/Collide/hkpCollide.h>
#include <Physics2012/Collide/Shape/hkpShape.h>
#include <Physics2012/Collide/Shape/HeightField/SampledHeightField/hkpSampledHeightFieldShape.h>
#include <Physics2012/Collide/Shape/HeightField/SampledHeightField/hkpSampledHeightFieldBaseCinfo.h>

class GestionnaireTerrain;

class HeightFieldShape: public hkpSampledHeightFieldShape
{
private:
	float const *mpHeightData;
public:

	/* Destructeur */
	HeightFieldShape(hkpSampledHeightFieldBaseCinfo const& rInfo, GestionnaireTerrain const *pTerrains);

	/* Destructeur */
	virtual ~HeightFieldShape();

	/* Récupération de la hauteur du terrain */
	HK_FORCE_INLINE hkReal getHeightAtImpl(int x, int z) const;

	/* Sens de découpage des rectangles en triangles */
	HK_FORCE_INLINE hkBool getTriangleFlipImpl() const;

	/* Détermine la collision avec une sphère */
	virtual void collideSpheres(CollideSpheresInput const& input, SphereCollisionOutput* outputArray) const;
};

