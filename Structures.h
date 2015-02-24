#pragma once

#define TAILLE_MONDE 50000
#define TAILLE_CHUNK 500
#define TAILLE_IMG_HEIGHTMAP 2049

#include <OgreVector3.h>

class hkpRigidBody;

typedef struct sTableauChunks
{
	hkpRigidBody* ppChunk[9];
	Ogre::Vector3 positionJoueur;
} TableauChunks;