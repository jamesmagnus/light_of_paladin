#pragma once

#include "ChunkMgr.h"

#include <boost/core/noncopyable.hpp>

class IDMgr;

namespace Ogre
{
	class TerrainGroup;
	class TerrainGlobalOptions;
	class Camera;
	class Viewport;
	class SceneManager;
	class TerrainLayerBlendMap;
	class Root;
}

/* Classe pour gérer le terrain: gestionnaire de chunks, création et chargement des meshs... */
/* Classe non dérivable */
/* Sémantique d'entité, hérite de boost::noncopyable */
class TerrainMgr: private boost::noncopyable
{
public:

    /* Constructeur */
    TerrainMgr(unsigned int tailleHeightMap, unsigned int tailleTerrain, Ogre::SceneManager *pSceneMgr, Ogre::Light *pSoleil, Ogre::Camera *pCam, Ogre::Viewport *pViewPort, Ogre::Root *pRoot);

    /* Destructeur */
    ~TerrainMgr();

    /* Renvoie l'adresse de l'objet TerrainGlobalOptions */
    Ogre::TerrainGlobalOptions* getOptions() const;

    /* Renvoie l'adresse de l'objet TerrainGroup */
    Ogre::TerrainGroup* getTerrains() const;

    /* Ajoute un terrain */
    /* x et y, sont les coordonnées du terrain dans le groupe */
    /* Retourne un ID correspondant au terrain */
    /* Lève une exception s'il n'y a plus de slot de terrain */
    unsigned long addTerrain(int x, int y, std::string const& nom);

	/* Renvoie l'adresse du gestionnaire de chunks (frameListener) */
	ChunkMgr* getPtrChunk();

private:

    unsigned int mTailleTerrain, mTailleHeightMap;

    Ogre::SceneManager *mpSceneMgr;
    Ogre::TerrainGroup *mpTerrainGroup;
    Ogre::TerrainGlobalOptions *mpOptions;
    Ogre::Light *mpSoleil;
	Ogre::Root *mpRoot;

	ChunkMgr *mpChunksMgn;

    IDMgr *mpIDGestion;

    std::map<unsigned long, std::pair<int, int>> mID_XY;
};
