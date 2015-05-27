#pragma once

#include <OgreFrameListener.h>
#include <OgreColourValue.h>

#include <boost/noncopyable.hpp>

namespace Ogre
{
	class Light;
	class SceneManager;
}

class WaterMgr;

namespace SkyX
{
	class SkyX;
}

/* Classe non dérivable pour gérer les différentes lumières de la scènes et les mettre à jour, hérite de Ogre::FrameListener */
/* Sémantique d'entité, hérite de boost::noncopyable */
class LightMgr: public Ogre::FrameListener, private boost::noncopyable
{
private:

	Ogre::Light* mpSoleil;
	Ogre::ColourValue mLumAmbiente;
	Ogre::SceneManager* mpSceneMgr;

	SkyX::SkyX* mpSky;
	WaterMgr* mpEauMgr;

public:

	/* Constructeur */
	/* pSoleil, pointeur vers une Ogre::Light de type directional qui servira de soleil */
	/* pSky, pointeur vers l'objet SkyX qui s'occupe du ciel */
	/* pEau, pointeur vers les gestionnaire d'eau */
	/* lumAmbiente, Ogre::Vector3 qui contient la valeur de la lumière ambiente */
	LightMgr(Ogre::SceneManager* pSceneMgr, Ogre::Light* pSoleil, SkyX::SkyX* pSky, WaterMgr* pEau, Ogre::ColourValue const& lumAmbiente=Ogre::ColourValue(0.0f, 0.0f, 0.0f));

	/* Destructeur */
	virtual ~LightMgr();

	/* Prédicat, renvoie true s'il fait nuit, false sinon */
	bool IsNuit() const;

	bool frameStarted(Ogre::FrameEvent const& rEvt) override;
};