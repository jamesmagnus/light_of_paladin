#include "StdLibAndNewOperator.h"
#include "LightMgr.h"

#include <SkyX.h>


LightMgr::LightMgr(Ogre::SceneManager* pSceneMgr, Ogre::Light* pSoleil, SkyX::SkyX* pSky, WaterMgr* pEau, Ogre::ColourValue const& lumAmbiente)
{
	assert(pSoleil != nullptr && pSky != nullptr && pEau != nullptr);

	mpSoleil = pSoleil;
	mpSky = pSky;
	mpEauMgr = pEau;
	mLumAmbiente = lumAmbiente;
	mpSceneMgr = pSceneMgr;
}

LightMgr::~LightMgr()
{

}

bool LightMgr::IsNuit() const
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

bool LightMgr::frameRenderingQueued(Ogre::FrameEvent const& rEvt)
{
	static boost::chrono::milliseconds const ref(1000);

	boost::chrono::system_clock::time_point tempsDebut = boost::chrono::system_clock::now();
	boost::chrono::milliseconds elapsedTime = boost::chrono::duration_cast<boost::chrono::milliseconds>(tempsDebut - mTimeCount);

	if (elapsedTime >= ref)
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

		mTimeCount = boost::chrono::system_clock::now();
	}

	return true;
}
