#include "Chunk.h"
#include "ExceptionPerso.h"

#include <OgreCamera.h>

using namespace Ogre;

Chunk::Chunk(unsigned int sizeMap, unsigned int chunkSize, GestionnaireTerrain *pGestTer, Ogre::Camera *pCam)
{
	assert(sizeMap%chunkSize == 0);

	mSizeMap = sizeMap;
	mChunkSize = chunkSize;
	mMaxChunkCoo = sizeMap / chunkSize;

	mReady = false;

	mppChunks = new hkpRigidBody* [mMaxChunkCoo*mMaxChunkCoo];

	for (unsigned int i=0; i<mMaxChunkCoo*mMaxChunkCoo; ++i)
	{
		mppChunks[i] = nullptr;
	}

	mpGestTerrain = pGestTer;
	mpCam = pCam;
}


Chunk::~Chunk()
{
	delete[] mppChunks;
	mppChunks = nullptr;
}

bool Chunk::addChunkPtr(hkpRigidBody* pShape, unsigned int x, unsigned int y)
{
	if (x >= mMaxChunkCoo || y >= mMaxChunkCoo)
	{
		return false;
	} 
	else
	{
		assert(pShape != nullptr);

		if (mppChunks[mMaxChunkCoo*x + y] != nullptr)
		{
			return false;
		}
		else
		{
			mppChunks[mMaxChunkCoo*x + y] = pShape;
			mReady = false;

			return true;
		}
	}
}

bool Chunk::removeChunkPtr(unsigned int x, unsigned int y)
{
	if (x >= mMaxChunkCoo || y >= mMaxChunkCoo)
	{
		return false;
	}

	if (mppChunks[mMaxChunkCoo*x + y] != nullptr)
	{
		mppChunks[mMaxChunkCoo*x + y] = nullptr;
		mReady = false;

		return true;
	}
	else
	{
		mReady = false;
		return false;
	}
}

void Chunk::ready()
{
	for (unsigned int i=0; i < mMaxChunkCoo*mMaxChunkCoo; ++i)
	{
		if (mppChunks[i] == nullptr)
		{
			throw ExceptionPerso("Chunk incomplet. Ne peut pas être finalisé tant qu'il n'est pas complet.", ERREUR);
		}
	}

	mReady = true;
}

TableauChunks const& Chunk::getCurrentChunks() const
{
	return mActualChunk;
}

bool Chunk::frameRenderingQueued(Ogre::FrameEvent const& rEv)
{
	if (!mReady)
	{
		throw ExceptionPerso("Chunk non finalisé, veuillez appeler ready()", FATAL);
	}

	TableauChunks tmp;

	Vector3 pos = mpCam->getDerivedPosition();

	tmp.positionJoueur = pos;

	/* Coordonnées du chunk sur lequel est le joueur */
	pos.x = Real(int(pos.x)/mChunkSize);
	pos.y = Real(int(pos.y)/mChunkSize);

	unsigned int k=0;

	for (unsigned int i= unsigned int (pos.x)-1; i <= unsigned int (pos.x)+1; ++i)
	{
		for (unsigned int j= unsigned int (pos.y)-1; j <= unsigned int(pos.y)+1; ++j)
		{
			if (i>=0 && i<mMaxChunkCoo && j>=0 && j<mMaxChunkCoo)
			{
				tmp.ppChunk[k] = mppChunks[i*mMaxChunkCoo + j];
			} 
			else
			{
				tmp.ppChunk[k] = nullptr;
			}
			
			k++;
		}
	}

	mActualChunk = tmp;

	return true;
}
