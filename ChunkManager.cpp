#include "ChunkManager.h"
#include "ExceptionPerso.h"
#include "HeightFieldShape.h"
#include "Chunk.h"

#include <OgreCamera.h>

using namespace Ogre;

ChunkManager::ChunkManager(Ogre::Camera *pCam, GestionnaireTerrain *pTerrainMgr)
{
	assert(TAILLE_MONDE%TAILLE_CHUNK == 0);

	mMaxChunkCoo = TAILLE_MONDE / TAILLE_CHUNK;

	mpppChunks = new Chunk **[mMaxChunkCoo];

	for (int i=0; i<mMaxChunkCoo; ++i)
	{
		mpppChunks[i] = new Chunk*[mMaxChunkCoo];

		for (int j=0; j<mMaxChunkCoo; ++j)
		{
			mpppChunks[i][j] = nullptr;
		}
	}

	mpCam = pCam;
	mpGestTerrain = pTerrainMgr;
	mOffset = std::make_pair(0,0);
}


ChunkManager::~ChunkManager()
{
	for (unsigned int i=0; i<5; ++i)
	{
		for (unsigned int j=0; j<5; ++j)
		{
			if (mpppChunks[i][j] != nullptr)
			{
				/*mpppChunks[i][j]->markForWrite();
				mpppChunks[i][j]->removeReference();
				mpppChunks[i][j]->unmarkForWrite();

				mpppChunks[i][j] = nullptr;*/
			}
		}
	}

	mpGestTerrain=nullptr;
	mpCam=nullptr;
}

bool ChunkManager::createChunk(std::pair<int, int> coo)
{
	if (coo.first >= mMaxChunkCoo || coo.second >= mMaxChunkCoo)
	{
		return false;
	} 
	else
	{
		

		return true;
	}
}

bool ChunkManager::destroyChunk(std::pair<int, int> coo)
{
	if (coo.first >= mMaxChunkCoo || coo.second >= mMaxChunkCoo)
	{
		return false;
	}

	if (mpppChunks[coo.first%5][coo.second%5] != nullptr)
	{
		/*mpppChunks[coo.first%5][coo.second%5]->markForWrite();
		mpppChunks[coo.first%5][coo.second%5]->removeReference();
		mpppChunks[coo.first%5][coo.second%5]->unmarkForWrite();
		mpppChunks[coo.first%5][coo.second%5] = nullptr;*/
		return true;
	}
	else
	{
		return false;
	}
}

TableauChunks const& ChunkManager::getCurrentChunks() const
{
	return mActualChunk;
}

bool ChunkManager::frameRenderingQueued(Ogre::FrameEvent const& rEv)
{
	static double t=0;
	t += rEv.timeSinceLastFrame;
	if (t > 5)
{
	t=0;
	TableauChunks tmp;
	
		Vector3 pos = mpCam->getDerivedPosition();
	
		tmp.positionJoueur = pos;
	
		/* Coordonnées du chunk sur lequel est le joueur */
		pos.x = Real(int(pos.x)/TAILLE_CHUNK);
		pos.z = Real(int(pos.z)/TAILLE_CHUNK);
	
		unsigned int k=0;
	
		for (int i= int(pos.x)-1; i <= int(pos.x)+1; ++i)
		{
			for (int j= int(pos.z)-1; j <= int(pos.z)+1; ++j)
			{
				if (i>=0 && i<mMaxChunkCoo && j>=0 && j<mMaxChunkCoo)
				{
					std::cout << "chunk:" << i << " " << j << std::endl;
					/*createChunk(i, j);
					tmp.ppChunk[k] = mppChunks[i%5][j%5];
					destroyChunk(i, j);*/
				} 
				else
				{
					tmp.ppChunk[k] = nullptr;
				}
				
				k++;
			}
		}
		std::cout<< std::endl;
	
		mActualChunk = tmp;
}

	return true;
}
