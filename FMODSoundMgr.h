#pragma once

#include <fmod.hpp>

#include <OgreFrameListener.h>

#include <boost/noncopyable.hpp>

#include <map>

/* Classe utilisée pour gérer FMOD et tout le système sonore du jeu */
/* Classe finale, non dérivable */
/* Sémantique d'entité, hérite de boost::noncopyable */
/* Hérite de Ogre::FrameListener, doit être ajoutée à la liste des listers de Ogre */
class FMODSoundMgr: public Ogre::FrameListener, private boost::noncopyable
{
private:
	FMOD::System *pSys;
	std::map<std::string, FMOD::Sound*> mSoundPtrMap;

public:

	/* Constructeur */
	/* Lève une exception en cas de problème */
	FMODSoundMgr();

	/* Destructeur */
	virtual ~FMODSoundMgr();

	/* Appelé par Ogre à chaque début de frame */
	virtual bool frameStarted(Ogre::FrameEvent const& evt) override;

	/* Charge un son */
	/* renvoie true si le son est chargé, false sinon */
	/* fichier, le nom du fichier à charger */
	/* nom, le nom associé au son */
	bool loadSound(std::string const& fichier, std::string const& nom);

	/* Lance la lecture du son */
	/* nom, le nom du son à lancer */
	/* Lève une exception si le son n'existe pas */
	void playLoadedSound(std::string const& nom, bool const paused=false) const;

	/* Décharge un son */
	/* nom, le nom du son à décharger */
	/* Lève une exception si le son est introuvable */
	void unloadSound(std::string const& nom);
};

