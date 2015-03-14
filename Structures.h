#pragma once

#define TAILLE_MONDE 30000
#define TAILLE_CHUNK 100
#define TAILLE_IMG_HEIGHTMAP 2049

#include <OgreVector3.h>

#include <vector>

class Chunk;

typedef struct sTableauChunks
{
	std::vector<Chunk*> vectPtrChunk;
	Ogre::Vector3 positionJoueur;
} TableauChunks;