#pragma once

#include <OgreFrameListener.h>

#include <boost/noncopyable.hpp>

namespace Hydrax
{
	class Hydrax;
}

namespace SkyX
{
	class SkyX;
}

/* Classe non dérivable pour gérer l'eau, hérite de Ogre::FrameListener */
/* Sémantique d'entité, hérite de boost::noncopyable */
/* Doit être ajouter à la liste des frameListener de Ogre */
class WaterMgr: public Ogre::FrameListener, private boost::noncopyable
{
private:

	Hydrax::Hydrax* mpHydrax;
	SkyX::SkyX* mpSky;
	Ogre::Real mH;
	bool mNeedUpdate;

public:

	/* Constructeur */
	/* pMgn, pointeur vers le SceneManager */
	/* pCam, pointeur sur la caméra */
	/* pView, pointeur sur le viewPort */
	/* pSky, pointeur vers l'objet SkyX qui représente le ciel */
	WaterMgr(Ogre::SceneManager* pMgn, Ogre::Camera* pCam, Ogre::Viewport* pView, SkyX::SkyX* pSky);

	/* Destructeur */
	virtual ~WaterMgr();

	/* Définie la hauteur de l'eau */
	/* h, la hauteur en coordonnées du monde (mètres) */
	void setHauteur(Ogre::Real h);

	/* Renvoie la hauteur actuelle de l'eau */
	Ogre::Real getHauteur() const;

	/* Initialise Hydrax avec les valeurs fournies et démarre le rendu */
	/* Renvoie true si cette méthode avait déjà était appelée */
	bool create();

	/* Renvoie l'adresse du gestionnaire hydrax */
	Hydrax::Hydrax* getHydrax() const;

	bool frameStarted(Ogre::FrameEvent const& rEvt) override;
};