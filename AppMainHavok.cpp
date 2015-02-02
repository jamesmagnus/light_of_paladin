/* Méthodes de AppMain relatives à Havok */

#include "AppMain.h"
#include "Structures.h"

#include <OgreLogManager.h>

#include <Common/Base/hkBase.h>
#include <Common/Base/Memory/System/Util/hkMemoryInitUtil.h>
#include <Physics2012/Dynamics/World/hkpWorldCinfo.h>
#include <Physics2012/Dynamics/World/hkpWorld.h>


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
	HkWorldInfo.setBroadPhaseWorldSize(3*TAILLE_CHUNK);	//Taille de la simulation 3 chunks sur 3 chunks
	HkWorldInfo.setupSolverInfo(hkpWorldCinfo::SOLVER_TYPE_8ITERS_MEDIUM);
	HkWorldInfo.m_simulationType = hkpWorldCinfo::SIMULATION_TYPE_CONTINUOUS;

	mpHkWorld = new hkpWorld(HkWorldInfo);

	Ogre::LogManager::getSingletonPtr()->logMessage("**** Havok successfully initialized ****");

	return true;
}


#include <Common/Base/keycode.cxx>

#include <Common/Base/Config/hkProductFeatures.cxx>

#include <Common/Base/System/Init/PlatformInit.cxx>