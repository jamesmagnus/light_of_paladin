#include "Lumiere.h"
#include <SkyX.h>


GestionnaireLight::GestionnaireLight(Ogre::SceneManager* pSceneMgr, Ogre::Light* pSoleil, SkyX::SkyX* pSky, Eau* pEau, Ogre::ColourValue lumAmbiente)
{
	assert(pSoleil != nullptr && pSky != nullptr && pEau != nullptr);

	mpSoleil = pSoleil;
	mpSky = pSky;
	mpEauMgr = pEau;
	mLumAmbiente = lumAmbiente;
	mpSceneMgr = pSceneMgr;
}

GestionnaireLight::~GestionnaireLight()
{

}

bool GestionnaireLight::IsNuit() const
{
	Ogre::Vector3 time = static_cast<SkyX::BasicController*>(mpSky->getController())->getTime();

	if (time.x < time.y || time.x > time.z) // Il fait nuit avant le lever du soleil ou après son coucher
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool GestionnaireLight::frameStarted(Ogre::FrameEvent const& rEvt)
{
	if (!IsNuit())
	{
		mpSoleil->setVisible(true);
		Ogre::Vector3 directionSun = mpSky->getController()->getSunDirection();
		mpSoleil->setDirection(-directionSun);
		mLumAmbiente = Ogre::ColourValue(0.8f, 0.8f, 0.8f);
	}
	else
	{
		mpSoleil->setVisible(false);
		mLumAmbiente = Ogre::ColourValue(0.3f, 0.3f, 0.3f);
	}


	mpSceneMgr->setAmbientLight(mLumAmbiente);

	return true;
}
