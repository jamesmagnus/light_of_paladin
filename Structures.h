#pragma once

#define TAILLE_MONDE 30000
#define TAILLE_CHUNK 100
#define TAILLE_IMG_HEIGHTMAP 2049
#define VITESSE_TRANS_CAM 500.0f
#define VITESSE_ROTATION_CAM 0.25f

#include <OgreVector3.h>
#include <vector>

class Chunk;

typedef struct sTableauChunks
{
	std::vector<Chunk*> vectPtrChunk;
	Ogre::Vector3 positionJoueur;
} TableauChunks;

#include "enumerations.h"

typedef struct sVector3Move
{
	EMove x;
	EMove y;
	EMove z;
} Vector3Move;