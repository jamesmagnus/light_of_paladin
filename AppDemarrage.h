#pragma once

#include <OGRE/Ogre.h>
#include <Ogre/Terrain/OgreTerrain.h>
#include <map>

#include "Structures.h"

class GestionnaireTerrain;
class Personnage;
class Item;
class Inventaire;

class AppDemarrage
{
protected:
    Ogre::Root *mpRoot;
    Ogre::RenderWindow *mpWindow;
    Ogre::SceneManager *mpSceneMgr;
    Ogre::Camera *mpCam;
    GestionnaireTerrain *mpTerrain;
    Ogre::TerrainGlobalOptions *mpGlobals;

    std::map<std::string, Personnage*> mmapPersonnages;
    std::map<std::string, Item*> mmapItem;
    std::map<std::string, Inventaire*> mmapInventaire;

public:

    /* Constructeur */
    AppDemarrage();

    /* Destructeur */
    virtual ~AppDemarrage();

    /* Lance le jeu */
    /* Retourne toujours true (système d'exception si erreur) */
    void start();

    /* Crée la scène, appelée par start() */
    /* Retourne false en cas d'erreur */
    bool createScene();

    /* Crée les éléments basiques de la scène, viewport, caméra, éclairage ambient */
    /* Appelée par createScene() */
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

    /* Charge et initialise Ogre, appelée par start() */
    /* Retourne false en cas d'erreur */
    bool initOGRE();

    /* Lance la boucle de rendu, appelée par start() */
    void infiniteLoop();

    /* Ajoute un nouveau Personnage */
    /* Retourne false en cas d'erreur */
    bool ajoutPersonnage(Ogre::SceneNode *pNoeud, std::string nom, int stat[EStat::ESTATMAX], int niveau, int XP, Ogre::Vector3 position, Ogre::Vector3 rotation);

    /* Retourne un personnage en fonction de son nom */
    /* Renvoie un pointeur vers ce personnage */
    /* Lève une exception sinon */
    Personnage* getPersonnage(std::string nom) const;
};