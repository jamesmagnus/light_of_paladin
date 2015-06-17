#include "StdLibAndNewOperator.h"
#include "PhysicMgr.h"

#include <btBulletDynamicsCommon.h>
#include <OgreLogManager.h>


PhysicMgr::PhysicMgr()
{
	mpCollisionDispatch = nullptr;
	mpCollisionCfg = nullptr;
	mpBroadphase = nullptr;
	mpConstraintSolv = nullptr;
	mpWorld = nullptr;
}


PhysicMgr::~PhysicMgr()
{
	destroyBullet();
}

bool PhysicMgr::initBullet()
{
	Ogre::LogManager::getSingletonPtr()->logMessage("**** Init Bullet ****");

	try
	{
		mpCollisionCfg = new btDefaultCollisionConfiguration();
		mpCollisionDispatch = new btCollisionDispatcher(mpCollisionCfg);
		mpBroadphase = new btDbvtBroadphase();
		mpConstraintSolv = new btSequentialImpulseConstraintSolver();
		mpWorld = new btDiscreteDynamicsWorld(mpCollisionDispatch, mpBroadphase, mpConstraintSolv, mpCollisionCfg);
	}
	catch (std::bad_alloc const& e)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("**** Bullet failed to allocate memory ****");
		return false;
	}

	Ogre::LogManager::getSingletonPtr()->logMessage("**** Bullet successfully initialized ****");

	mpWorld->setGravity(btVector3(0.0, -9.81, 0.0));

	Ogre::LogManager::getSingletonPtr()->logMessage("[Bullet] Setting gravity to -9.81");

	return true;
}

void PhysicMgr::destroyBullet()
{
	delete mpWorld;
	delete mpBroadphase;
	delete mpConstraintSolv;
	delete mpCollisionDispatch;
	delete mpCollisionCfg;
}
