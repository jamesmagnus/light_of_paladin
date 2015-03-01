#include "ChunkManager.h"
#include "ExceptionPerso.h"
#include "HeightFieldShape.h"
#include "Chunk.h"

#include <OgreCamera.h>
#include <Physics2012/Dynamics/World/hkpWorld.h>

using namespace Ogre;

ChunkManager::ChunkManager(Ogre::Camera *pCam, GestionnaireTerrain *pTerrainMgr, hkpWorld *pHavokWorld)
{
	assert(TAILLE_MONDE%TAILLE_CHUNK == 0);

	mMaxChunkCoo = TAILLE_MONDE / TAILLE_CHUNK;
	mpCam = pCam;
	mpGestTerrain = pTerrainMgr;
	mpHavokWorld = pHavokWorld;

	mpppChunk = new Chunk**[mMaxChunkCoo];

	for (int i=0; i<mMaxChunkCoo; ++i)
	{
		mpppChunk[i] = new Chunk*[mMaxChunkCoo];

		for (int j=0; j<mMaxChunkCoo; ++j)
		{
			mpppChunk[i][j] = new Chunk(pTerrainMgr, std::make_pair(i,j));
		}
	}

	mActualChunk.offset = std::make_pair(0, 0);
	mActualChunk.positionJoueur = Vector3::ZERO;
	
	for (int i=0; i<3; ++i)
	{
		for (int j=0; j<3; ++j)
		{
			mActualChunk.ppChunk[i][j]=nullptr;
		}
	}
}


ChunkManager::~ChunkManager()
{
	for (int i=0; i<mMaxChunkCoo; ++i)
	{
		for (int j=0; j<mMaxChunkCoo; ++j)
		{
			delete mpppChunk[i][j];
			mpppChunk[i][j] = nullptr;
		}
		delete[] mpppChunk[i];
		mpppChunk[i] = nullptr;
	}

	delete[] mpppChunk;
	mpppChunk = nullptr;

	mpGestTerrain=nullptr;
	mpCam=nullptr;
}

bool ChunkManager::activeChunk(std::pair<int, int> coo)
{
	if (coo.first >= mMaxChunkCoo || coo.second >= mMaxChunkCoo || coo.first < 0 || coo.second < 0)
	{
		return false;
	} 
	else
	{
		mpppChunk[coo.first][coo.second]->loadBody();
		return true;
	}
}

bool ChunkManager::releaseChunk(std::pair<int, int> coo)
{
	if (coo.first >= mMaxChunkCoo || coo.second >= mMaxChunkCoo || coo.first < 0 || coo.second < 0)
	{
		return false;
	}
	else
	{
		mpppChunk[coo.first][coo.second]->destroyBody();
		return true;
	}
}

TableauChunks const& ChunkManager::getCurrentChunks() const
{
	return mActualChunk;
}

bool ChunkManager::frameRenderingQueued(Ogre::FrameEvent const& rEv)
{
	boost::chrono::system_clock::time_point debut = boost::chrono::system_clock::now();

	boost::chrono::milliseconds elapsedTime = boost::chrono::duration_cast<boost::chrono::milliseconds>(debut - mTimeCount);
	boost::chrono::milliseconds ref(1000);

	if (elapsedTime >= ref)
	{
		TableauChunks tmp;

		for (int i=0; i<3; ++i)
		{
			for (int j=0; j<3; ++j)
			{
				tmp.ppChunk[i][j]=nullptr;
			}
		}

		tmp.offset = std::make_pair(0, 0);
	
		Vector3 pos = mpCam->getDerivedPosition();
	
		tmp.positionJoueur = pos;
	
		/* Coordonnées du chunk sur lequel est le joueur */
		pos.x = Real(int(pos.x)/TAILLE_CHUNK);
		pos.z = Real(int(pos.z)/TAILLE_CHUNK);

		int k=0;
	
		for (int i=0; i<mMaxChunkCoo; ++i)
		{
			for (int j=0; j<mMaxChunkCoo; ++j)
			{
				if (i >= pos.x-1 && i <= pos.x+1 && j >= pos.z-1 && j <= pos.z+1)
				{
					activeChunk(std::make_pair(i, j));
					tmp.ppChunk[k/3][k%3] = mpppChunk[i][j];
					k++;
				} 
				else
				{
					releaseChunk(std::make_pair(i, j));
				}
			}
		}
	
		mActualChunk = tmp;
		mTimeCount = boost::chrono::system_clock::now();

		//-----------------------------------------------------
		mpHavokWorld->lock();
		mpHavokWorld->markForWrite();

		mpHavokWorld->removeEntity((hkpEntity*)tmp.ppChunk[0][0]->getBodyPtr());

		mpHavokWorld->unmarkForWrite();
		mpHavokWorld->unlock();
	}

	return true;
}
