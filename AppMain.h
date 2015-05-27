#pragma once

#include <OgreVector3.h>

#include "enumerations.h"

class TerrainMgr;
class Personnage;
class Item;
class Inventaire;
class WaterMgr;
class LightMgr;
class hkpWorld;
class CeguiMgr;
class InputListener;
class FMODSoundMgr;

namespace Ogre
{
	class Root;
	class RenderWindow;
	class SceneManager;
	class Camera;
	class SceneNode;
}

namespace SkyX
{
	class SkyX;
}

namespace Forests
{
	class PagedGeometry;
}

/* Application du jeu */
/* Singleton */
class AppMain
{
private:

	static AppMain *mpsUniqueInstance;

	Ogre::Root *mpRoot;
	Ogre::RenderWindow *mpWindow;
	Ogre::SceneManager *mpSceneMgr;
	Ogre::Camera *mpCam;

	CeguiMgr *mpCeguiMgr;
	TerrainMgr *mpTerrain;
	WaterMgr *mpWater;
	LightMgr *mpLum;
	InputListener *mpListener;
	FMODSoundMgr *mpSoundMgr;

	SkyX::SkyX *mpSky;
	Forests::PagedGeometry *mpTrees;

	hkpWorld *mpHkWorld;

	std::map<std::string, Personnage*> mmapPersonnages;
	std::map<std::string, Item*> mmapItem;
	std::map<std::string, Inventaire*> mmapInventaire;

	/* Constructeur interne du singleton */
	AppMain();

	/* Destructeur interne */
	~AppMain();

	/* Constructeur par copie interdit */
	AppMain(AppMain const& rOriginal);

	/* Opérateur d'affectation interdit */
	AppMain& operator=(AppMain const& rOriginal);

public:

	/* Renvoie l'adresse de l'instance unique */
	static AppMain* getInstance();

	/* Détruit l'unique instance */
	static void destroy();

	/* Lance le jeu */
	/* Retourne toujours true (système d'exception si erreur) */
	void start();

	/* Crée la scène, appelée par start() */
	/* Retourne false en cas d'erreur */
	bool createScene();

	/* Crée les éléments basiques, viewport, caméra, éclairage ambient */
	/* Retourne false en cas d'erreur */
	bool createBase();

	/* Crée le terrain */
	/* Appelée par createScene() */
	/* Retourne false en cas d'erreur */
	bool createTerrain();

	/* Crée le ciel */
	/* Appelée par createScene() */
	/* Retourne false en cas d'erreur */
	bool createSky();

	/* Crée les objets autres que les personnages */
	/* Appelée par createScene() */
	/* Retourne false en cas d'erreur */
	bool createObject();

	/* Crée les personnages */
	/* Appelée par createScene() */
	/* Retourne false en cas d'erreur */
	bool createPersonnage();

	/* Crée et enregistre le gestionnaire des lumières */
	/* Appelée par createScene() */
	/* Retourne false en cas d'erreur */
	bool createLight();

	/* Charge et initialise Ogre, appelée par start() */
	/* Retourne false en cas d'erreur */
	bool initOGRE();

	/* Lance la boucle de rendu, appelée par start() */
	void infiniteLoop();

	/* Ajoute un nouveau Personnage */
	/* Retourne false en cas d'erreur */
	bool ajoutPersonnage(Ogre::SceneNode *pNoeud, std::string const& nom, int stat[EStat::ESTATMAX], int niveau, int XP, Ogre::Vector3 const& position, Ogre::Vector3 const& rotation);

	/* Retourne un personnage en fonction de son nom */
	/* Renvoie un pointeur vers ce personnage */
	/* Lève une exception sinon */
	Personnage* getPersonnage(std::string const& nom) const;

	/* Initialise Havok */
	bool initHavok();

	/* Renvoie l'adresse du gestionnaire de son FMOD */
	FMODSoundMgr* getFMODSoundMgr() const;
};