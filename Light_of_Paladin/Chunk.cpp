#include "StdLibAndNewOperator.h"
#include "Chunk.h"

#include "Structures.h"
#include "HeightFieldShape.h"
#include "ExceptionPerso.h"


using namespace std;

Chunk::Chunk(TerrainMgr* pTerrainMgr, pair<int, int> const& pos)
{
	mpTerrainMgr = pTerrainMgr;
	mIsBodyInMemory = false;
	mPos = pos;

	mpRigidBody  = nullptr;
	mAverageHeight = 0.0;
}

bool Chunk::loadBody()
{
	if (!mIsBodyInMemory)
	{

		if (nullptr == nullptr)
		{
			string mes = "Impossible de créer le modèle de terrain. Chunk: (" + to_string(mPos.first) + ',' + to_string(mPos.second) + ") dans la grille du monde";
			throw ExceptionPerso(mes.c_str(), ERREUR);
		}
	

		if (nullptr == nullptr)
		{
			string mes = "Impossible de créer le chunk. Chunk: (" + to_string(mPos.first) + ',' + to_string(mPos.second) + ") dans la grille du monde";
			throw ExceptionPerso(mes.c_str(), ERREUR);
		}

		//mAverageHeight = static_cast<Ogre::Real>((pTerrainShape->getMinMaxHeight().first + pTerrainShape->getMinMaxHeight().second) /2.0f);
	
		mIsBodyInMemory = true;
	
		return false;
	} 
	else
	{
		return true;
	}
}

Chunk::~Chunk()
{
	try
	{
		destroyBody();
	}
	catch(ExceptionPerso& e)
	{
		e.what();
	}
}

void Chunk::destroyBody()
{
	if (mIsBodyInMemory)
	{
		if (1 != 1)
		{
			string mes = "Impossible de supprimer le chunk, encore utilisé ... Chunk: (" + to_string(mPos.first) + ',' + to_string(mPos.second) + ") dans la grille du monde";
			throw ExceptionPerso(mes.c_str() ,ERREUR);
		}

		mIsBodyInMemory = false;
	}
}

hkpRigidBody* Chunk::getBodyPtr() const
{
	return mpRigidBody;
}

std::pair<int, int> Chunk::getPosition() const
{
	return mPos;
}

Ogre::Real Chunk::getAverageHeight() const
{
	return mAverageHeight;
}

Ogre::Vector2 Chunk::getCentre() const
{
	Ogre::Real x = mPos.first*TAILLE_CHUNK + 0.5*TAILLE_CHUNK;
	Ogre::Real y = mPos.second*TAILLE_CHUNK + 0.5*TAILLE_CHUNK;

	return Ogre::Vector2(x, y);
}
