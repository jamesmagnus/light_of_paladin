/* Méthodes de AppMain relatives à Havok */

#include "AppMain.h"
#include "Structures.h"
#include "enumerations.h"
#include "HeightFieldShape.h"
#include "TerrainMgr.h"

#include <OgreLogManager.h>
#include <OgreVector2.h>

#include <Common/Base/hkBase.h>
#include <Common/Base/Memory/System/Util/hkMemoryInitUtil.h>
#include <Common/Base/Thread/Pool/hkThreadPool.h>
#include <Common/Base/Thread/Thread/hkThread.h>
#include <Common/Base/Memory/Allocator/Pooled/hkPooledAllocator.h>
#include <Physics2012/Dynamics/World/hkpWorldCinfo.h>
#include <Physics2012/Dynamics/World/hkpWorld.h>
#include <Physics2012/Dynamics/Entity/hkpRigidBody.h>


/* Fonction de gestion des erreurs pour Havok */
static void HK_CALL errorReportHavok(const char* msg, void* obj)
{
	std::cout << msg;
}

bool AppMain::initHavok()
{
	Ogre::LogManager::getSingletonPtr()->logMessage("**** Init Havok ****");

	hkMemoryRouter* pMemoryRouter = hkMemoryInitUtil::initDefault(hkMallocAllocator::m_defaultMallocAllocator, hkMemorySystem::FrameInfo(1024*5*1024)); // Alloue 5 mB de mémoire pour le solveur

	hkBaseSystem::init(pMemoryRouter, errorReportHavok);	//Initialisation de Havok et de ses sous-systèmes

	hkpWorldCinfo HkWorldInfo;

	HkWorldInfo.m_gravity.set(0, -9.81f, 0);
	HkWorldInfo.setBroadPhaseWorldSize(3*TAILLE_CHUNK +20);	//Taille de la simulation 3 chunks sur 3 chunks
	HkWorldInfo.setupSolverInfo(hkpWorldCinfo::SOLVER_TYPE_8ITERS_MEDIUM);
	HkWorldInfo.m_simulationType = hkpWorldCinfo::SIMULATION_TYPE_CONTINUOUS;

	/* HkWorldInfo.m_broadPhaseBorderBehaviour = hkpWorldCinfo::BroadPhaseBorderBehaviour::BROADPHASE_BORDER_DO_NOTHING; */ //Uncomment to disable border check

	mpHkWorld = new hkpWorld(HkWorldInfo);

	Ogre::LogManager::getSingletonPtr()->logMessage("**** Havok successfully initialized ****");

	return true;
}

#include <Common/Base/keycode.cxx>

#define HK_CLASSES_FILE <Common/Serialize/Classlist/hkKeyCodeClasses.h>

#include <Common/Base/Config/hkProductFeatures.cxx>

#include <Common/Base/System/Init/PlatformInit.cxx>
