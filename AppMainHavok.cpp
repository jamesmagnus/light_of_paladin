/* Méthodes de AppMain relatives à Havok */

#include <Ogre.h>

#include <Common/Base/hkBase.h>
#include <Common/Base/System/hkBaseSystem.h>
#include <Common/Base/Memory/System/Util/hkMemoryInitUtil.h>
#include <Common/Base/Memory/Allocator/Malloc/hkMallocAllocator.h>
#include <Common/Base/Memory/Allocator/LargeBlock/hkLargeBlockAllocator.h>
#include <Common/Base/Memory/System/FreeList/hkFreeListMemorySystem.h>
#include <Common/Base/Fwd/hkcstdio.h>
#include <Common/Base/Monitor/hkMonitorStream.h>
#include <Common/Base/Monitor/MonitorStreamAnalyzer/hkMonitorStreamAnalyzer.h>
#include <Common/Base/System/Stopwatch/hkStopwatch.h>
#include <Common/Base/Math/hkMath.h>


#include "AppMain.h"
#include "HeightFieldShape.h"

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