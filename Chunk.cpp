#include "Chunk.h"

#include "Structures.h"
#include "HeightFieldShape.h"
#include "ExceptionPerso.h"

#include <Physics2012/Dynamics/hkpDynamics.h>
#include <Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include <Physics2012/Collide/Shape/HeightField/SampledHeightField/hkpSampledHeightFieldShape.h>

using namespace std;

Chunk::Chunk(TerrainMgr* pTerrainMgr, pair<int, int> const& pos)
{
	mpTerrainMgr = pTerrainMgr;
	mIsBodyInMemory = false;
	mPos = pos;

	mpRigidBody  = nullptr;
	mAverageHeight = 0.0f;
}

bool Chunk::loadBody()
{
	if (!mIsBodyInMemory)
	{
		hkpSampledHeightFieldBaseCinfo shapeInfo;
	
		shapeInfo.m_maxHeight = -1;
		shapeInfo.m_minHeight = 0;
		shapeInfo.m_xRes = TAILLE_CHUNK;
		shapeInfo.m_zRes = TAILLE_CHUNK;
	
		HeightFieldShape *pTerrainShape = new HeightFieldShape(shapeInfo, mpTerrainMgr, mPos);

		if (pTerrainShape == nullptr)
		{
			string mes = "Impossible de créer le modèle de terrain. Chunk: (" + to_string(mPos.first) + ',' + to_string(mPos.second) + ") dans la grille du monde";
			throw ExceptionPerso(mes.c_str(), ERREUR);
		}
	
		hkpRigidBodyCinfo bodyInfo;
		bodyInfo.m_motionType = hkpMotion::MOTION_FIXED; //Décor
		bodyInfo.m_position= hkVector4(static_cast<hkFloat32>(mPos.first*TAILLE_CHUNK), 0.0f, static_cast<hkFloat32>(mPos.second*TAILLE_CHUNK));
		bodyInfo.m_shape = pTerrainShape;
		bodyInfo.m_friction = 0.3f;
	
		mpRigidBody = new hkpRigidBody(bodyInfo);

		if (mpRigidBody == nullptr)
		{
			string mes = "Impossible de créer le chunk. Chunk: (" + to_string(mPos.first) + ',' + to_string(mPos.second) + ") dans la grille du monde";
			throw ExceptionPerso(mes.c_str(), ERREUR);
		}

		mAverageHeight = static_cast<Ogre::Real>((pTerrainShape->getMinMaxHeight().first + pTerrainShape->getMinMaxHeight().second) /2.0f);
	
		pTerrainShape->removeReference();
	
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
		mpRigidBody->markForWrite();
		mpRigidBody->removeReference();
		mpRigidBody->unmarkForWrite();
	}
}

void Chunk::destroyBody()
{
	if (mIsBodyInMemory)
	{
		if (mpRigidBody->getReferenceCount() != 1)
		{
			string mes = "Impossible de supprimer le chunk, encore utilisé ... Chunk: (" + to_string(mPos.first) + ',' + to_string(mPos.second) + ") dans la grille du monde";
			throw ExceptionPerso(mes.c_str() ,ERREUR);
		}

		mpRigidBody->markForWrite();
		mpRigidBody->removeReference();
		mpRigidBody->unmarkForWrite();

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
	Ogre::Real x = mPos.first*TAILLE_CHUNK + 0.5f*TAILLE_CHUNK;
	Ogre::Real y = mPos.second*TAILLE_CHUNK + 0.5f*TAILLE_CHUNK;

	return Ogre::Vector2(x, y);
}
