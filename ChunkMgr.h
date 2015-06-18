#pragma once

#include <OgreFrameListener.h>
#include <OgreVector3.h>

#include <boost/chrono/chrono.hpp>
#include <boost/core/noncopyable.hpp>

#include "Structures.h"

namespace Ogre
{
	class Camera;
}

class TerrainMgr;
class Chunk;

/* Classe finale, non dérivable pour gérer le système de chunk du terrain avec Havok */
/* Sémantique d'entité, hérite de boost::noncopyable */
/* Hérite de Ogre::FrameListener, doit être ajoutée à la liste des listeners d'Ogre */
class ChunkMgr: public Ogre::FrameListener, private boost::noncopyable
{
private:
	TableauChunks mActualChunk;
	int mMaxChunkCoo;
	TerrainMgr *mpGestTerrain;
	Ogre::Camera* mpCam;
	Chunk*** mpppChunk;
	boost::chrono::system_clock::time_point mTimeCount;
	Ogre::Vector3 mOldOffset;

public:

	/* Constructeur */
	/* pCam, pointeur sur la caméra d'Ogre (pour connaître la position du joueur) */
	/* pTerrainMgr, pointeur sur les gestionnaire de terrain */
	/* DEBUG: assert si la taille du monde n'est pas un multiple de la taille d'un chunk */
	ChunkMgr(Ogre::Camera *pCam, TerrainMgr *pTerrainMgr);

	virtual ~ChunkMgr();

	/* Active un élément du terrain */
	/* coo, une paire d'entier représentant les coordonnées du chunk dans la grille */
	/* Renvoie true si le terrain a bien été généré, l'opération peut échouer si le couple(x,y) est incorrect */
	bool activeChunk(std::pair<int, int> const& coo);

	/* Désactive le chunk */
	/* coo, une paire d'entier représentant les coordonnées du chunk dans la grille */
	/* Renvoie True si le chunk a été désactivé, False sinon */
	bool releaseChunk(std::pair<int, int> const& coo);

	/* Renvoie un tableau de 9 chunks  avec celui où se trouve le joueur au centre */
	/* Si le joueur est au bord de la map certains pointeurs seront nullptr */
	TableauChunks const& getCurrentChunks() const;

	/* Mise à jour des chunks en fonction de la position du joueur */
	virtual bool frameRenderingQueued(Ogre::FrameEvent const& rEv) override;

	/* Calcul la moyenne des moyennes de hauteur de chaque chunks */
	Ogre::Real averageLocalHeight() const;
};