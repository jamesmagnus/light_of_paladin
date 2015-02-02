#pragma once

#include <OgreFrameListener.h>

namespace Hydrax
{
	class Hydrax;
}

namespace SkyX
{
	class SkyX;
}

/* Classe non dérivable pour gérer l'eau, dérive de Ogre::FrameListener */
/* Sémantique d'entité */
/* Doit être ajouter à la liste des frameListener de Ogre */
class Eau: public Ogre::FrameListener
{
private:

	Hydrax::Hydrax* mpHydrax;
	SkyX::SkyX* mpSky;
	Ogre::Real mH;
	bool mNeedUpdate;

	/* Constructeur de copie interdit */
	Eau(Eau const& rOriginal);

	/* Opérateur d'assignement interdit */
	Eau& operator=(Eau const& rOriginal);

public:

	/* Constructeur */
	/* pMgn, pointeur vers le SceneManager */
	/* pCam, pointeur sur la caméra */
	/* pView, pointeur sur le viewPort */
	/* pSky, pointeur vers l'objet SkyX qui représente le ciel */
	Eau(Ogre::SceneManager* pMgn, Ogre::Camera* pCam, Ogre::Viewport* pView, SkyX::SkyX* pSky);

	/* Destructeur */
	~Eau();

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