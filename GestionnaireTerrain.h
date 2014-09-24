#pragma once

#include <OgreTerrainGroup.h>

class GestionnaireID;

class GestionnaireTerrain
{
public:

    /* Constructeur */
    GestionnaireTerrain(unsigned int tailleHeightMap, unsigned int tailleTerrain, Ogre::SceneManager *pSceneMgr, Ogre::Light *pSoleil, Ogre::Camera *pCam, Ogre::Viewport *pViewPort);

    /* Destructeur */
    virtual ~GestionnaireTerrain();

    /* Renvoie l'adresse de l'objet TerrainGlobalOptions */
    Ogre::TerrainGlobalOptions* getOptions() const;

    /* Renvoie l'adresse de l'objet TerrainGroup */
    Ogre::TerrainGroup* getTerrains() const;

    /* Ajoute un terrain */
    /* x et y, sont les coordonnées du terrain dans le groupe */
    /* Retourne un ID correspondant au terrain */
    /* Lève une exception s'il n'y a plus de slot de terrain */
    unsigned long addTerrain(int x, int y, std::string nom);

    /* Renvoie la blend map du terrain */
    /* id, identifiant du terrain */
    /* Lève une exception en cas d'erreur */
    Ogre::TerrainLayerBlendMap* getBlendMap(unsigned long id) const;

    /* Récupère les coordonnées x et y du terrain d'après son identifiant */
    /* id, l'identifiant du terrain fourni par addTerrain() */
    /* Retourne une std::pair<int x, int y> */
    /* Lève une exception si l'id ne correspond pas à un terrain */
    std::pair<int, int> getXYFromID(unsigned long id) const;

protected:

    unsigned int mTailleTerrain, mTailleHeightMap;

    Ogre::SceneManager *mpSceneMgr;
    Ogre::TerrainGroup *mpTerrainGroup;
    Ogre::TerrainGlobalOptions *mpOptions;
    Ogre::Light *mpSoleil;

    GestionnaireID *mpIDGestion;

    std::map<unsigned long, std::pair<int, int>> mID_XY;
};
