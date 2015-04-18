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
class InputListener;

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
	GestionnaireLight *mpLum;
	InputListener *mpListener;

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
	/* Retourne toujours true (syst�me d'exception si erreur) */
	void start();

	/* Cr�e la sc�ne, appel�e par start() */
	/* Retourne false en cas d'erreur */
	bool createScene();

	/* Cr�e les �l�ments basiques, viewport, cam�ra, �clairage ambient */
	/* Retourne false en cas d'erreur */
	bool createBase();

	/* Cr�e le terrain */
	/* Appel�e par createScene() */
	/* Retourne false en cas d'erreur */
	bool createTerrain();

	/* Cr�e le ciel */
	/* Appel�e par createScene() */
	/* Retourne false en cas d'erreur */
	bool createSky();

	/* Cr�e les objets autres que les personnages */
	/* Appel�e par createScene() */
	/* Retourne false en cas d'erreur */
	bool createObject();

	/* Cr�e les personnages */
	/* Appel�e par createScene() */
	/* Retourne false en cas d'erreur */
	bool createPersonnage();

	/* Cr�e et enregistre le gestionnaire des lumi�res */
	/* Appel�e par createScene() */
	/* Retourne false en cas d'erreur */
	bool createLight();

	/* Charge et initialise Ogre, appel�e par start() */
	/* Retourne false en cas d'erreur */
	bool initOGRE();

	/* Lance la boucle de rendu, appel�e par start() */
	void infiniteLoop();

	/* Ajoute un nouveau Personnage */
	/* Retourne false en cas d'erreur */
	bool ajoutPersonnage(Ogre::SceneNode *pNoeud, std::string const& nom, int stat[EStat::ESTATMAX], int niveau, int XP, Ogre::Vector3 const& position, Ogre::Vector3 const& rotation);

	/* Retourne un personnage en fonction de son nom */
	/* Renvoie un pointeur vers ce personnage */
	/* L�ve une exception sinon */
	Personnage* getPersonnage(std::string const& nom) const;

	/* Initialise Havok */
	bool initHavok();
};