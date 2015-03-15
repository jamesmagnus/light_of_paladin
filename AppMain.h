#pragma once

#include <OgreVector3.h>

#include "enumerations.h"

class GestionnaireTerrain;
class Personnage;
class Item;
class Inventaire;
class Eau;
class GestionnaireLight;
class hkpWorld;
class CeguiMgr;

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

class AppMain
{
private:
	Ogre::Root *mpRoot;
	Ogre::RenderWindow *mpWindow;
	Ogre::SceneManager *mpSceneMgr;
	Ogre::Camera *mpCam;

	CeguiMgr *mpCeguiMgr;

	GestionnaireTerrain *mpTerrain;
	Eau *mpWater;
	GestionnaireLight* mpLum;

	SkyX::SkyX *mpSky;
	Forests::PagedGeometry *mpTrees;

	hkpWorld *mpHkWorld;

	std::map<std::string, Personnage*> mmapPersonnages;
	std::map<std::string, Item*> mmapItem;
	std::map<std::string, Inventaire*> mmapInventaire;

public:

	/* Constructeur */
	AppMain();

	/* Destructeur */
	~AppMain();

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
};