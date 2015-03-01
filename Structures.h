#pragma once

#define TAILLE_MONDE 50000
#define TAILLE_CHUNK 100
#define TAILLE_IMG_HEIGHTMAP 2049

#include <OgreVector3.h>

class Chunk;

typedef struct sTableauChunks
{
	Chunk* ppChunk[3][3];
	Ogre::Vector3 positionJoueur;
	std::pair<int, int> offset;
} TableauChunks;