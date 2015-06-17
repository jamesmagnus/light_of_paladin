#include "StdLibAndNewOperator.h"
#include "WaterMgr.h"

#include <Hydrax.h>
#include <Noise/Perlin/Perlin.h>
#include <Noise/FFT/FFT.h>
#include <Modules/ProjectedGrid/ProjectedGrid.h>
#include <Modules/SimpleGrid/SimpleGrid.h>
#include <Modules/RadialGrid/RadialGrid.h>
#include <SkyX.h>

#include <OgrePrerequisites.h>


WaterMgr::WaterMgr(Ogre::SceneManager* pMgn, Ogre::Camera* pCam, Ogre::Viewport* pView, SkyX::SkyX* pSky): Ogre::FrameListener()
{
	mpHydrax = LOP_NEW Hydrax::Hydrax(pMgn, pCam, pView);
	mNeedUpdate = true;
	mpSky = pSky;
}

WaterMgr::~WaterMgr()
{	
	if (mpHydrax != nullptr)
	{
		delete mpHydrax;
		mpHydrax = nullptr;
	}
}

void WaterMgr::setHauteur(Ogre::Real h)
{
	mH = h;
	mNeedUpdate = true;
}

Ogre::Real WaterMgr::getHauteur() const
{
	return mH;
}

Hydrax::Hydrax* WaterMgr::getHydrax() const
{
	return mpHydrax;
}

bool WaterMgr::create()
{
	mpHydrax->loadCfg("HydraxDemo.hdx");

	const int complexity_num = 264;
	const int mesh_size = 2100;
	struct Hydrax::Size mesh_struct;
	mesh_struct.setSize(mesh_size);
	struct Hydrax::Module::SimpleGrid::Options options_struct;
	options_struct.Complexity = complexity_num;
	options_struct.MeshSize = mesh_struct;

	Hydrax::Module::RadialGrid *module = LOP_NEW Hydrax::Module::RadialGrid(mpHydrax, LOP_NEW Hydrax::Noise::FFT(), Hydrax::MaterialManager::NM_RTT, Hydrax::Module::RadialGrid::Options());

	mpHydrax->setModule(module);

	mpHydrax->setPosition(Ogre::Vector3(0.0f, mH, 0.0f));

	mpHydrax->update(0.0);

	if (mpHydrax->isCreated())
	{
		return true;
	} 
	else
	{
		mpHydrax->create();
		return false;
	}
}

bool WaterMgr::frameStarted(Ogre::FrameEvent const& rEvt)
{
	if (mNeedUpdate)
	{
		mpHydrax->setPosition(Ogre::Vector3(0.0f, mH, 0.0f));
		mNeedUpdate = false;
	}

	assert(mpSky != nullptr);

	//mpSky->setStarfieldEnabled(true);

	Ogre::Vector3 sunPos = mpHydrax->getCamera()->getDerivedPosition() + mpSky->getController()->getSunDirection()*mpSky->getMeshManager()->getSkydomeRadius(mpHydrax->getCamera())*10.0f;
	mpHydrax->setSunPosition(sunPos);

	mpHydrax->update(rEvt.timeSinceLastFrame);

	return true;
}



