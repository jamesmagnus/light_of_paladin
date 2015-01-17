#include <Hydrax.h>
#include <Noise/Perlin/Perlin.h>
#include <Modules/ProjectedGrid/ProjectedGrid.h>
#include <Ogre.h>
#include <SkyX.h>

#include "Eau.h"


Eau::Eau(Ogre::SceneManager* pMgn, Ogre::Camera* pCam, Ogre::Viewport* pView, SkyX::SkyX* pSky): Ogre::FrameListener()
{
	mpHydrax = new Hydrax::Hydrax(pMgn, pCam, pView);
	mNeedUpdate = true;
	mpSky = pSky;
}

Eau::~Eau()
{	
	if (mpHydrax != nullptr)
	{
		delete mpHydrax;
	}
}

void Eau::setHauteur(Ogre::Real h)
{
	mH = h;
	mNeedUpdate = true;
}

Ogre::Real Eau::getHauteur() const
{
	return mH;
}

Hydrax::Hydrax* Eau::getHydrax() const
{
	return mpHydrax;
}

bool Eau::create()
{
	mpHydrax->loadCfg("HydraxDemo.hdx");

	Hydrax::Module::ProjectedGrid *module = new Hydrax::Module::ProjectedGrid(mpHydrax, new Hydrax::Noise::Perlin(), Ogre::Plane(Ogre::Vector3::UNIT_Y, 0.0), Hydrax::MaterialManager::NM_VERTEX, Hydrax::Module::ProjectedGrid::Options());

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

bool Eau::frameStarted(Ogre::FrameEvent const& rEvt)
{
	if (mNeedUpdate)
	{
		mpHydrax->setPosition(Ogre::Vector3(0.0f, mH, 0.0f));
		mNeedUpdate = false;
	}

	assert(mpSky != nullptr);

	mpSky->setStarfieldEnabled(true);

	Ogre::Vector3 sunPos = mpHydrax->getCamera()->getDerivedPosition() + mpSky->getController()->getSunDirection()*mpSky->getMeshManager()->getSkydomeRadius(mpHydrax->getCamera())*10.0f;
	mpHydrax->setSunPosition(sunPos);

	mpHydrax->update(rEvt.timeSinceLastFrame);

	return true;
}



