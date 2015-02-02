#pragma once

#include <OgreFrameListener.h>

#include "Structures.h"

namespace Ogre
{
	class Camera;
}

class hkpRigidBody;
class GestionnaireTerrain;

class Chunk: public Ogre::FrameListener
{
private:
	TableauChunks mActualChunk;
	unsigned int mSizeMap, mChunkSize, mMaxChunkCoo;
	hkpRigidBody **mppChunks;
	bool mReady;
	GestionnaireTerrain *mpGestTerrain;
	Ogre::Camera* mpCam;

public:

	/* Constructeur */
	/* sizeMap, taille du monde */
	/* chunkSize, taille d'un chunk en mètres */
	Chunk(unsigned int sizeMap, unsigned int chunkSize, GestionnaireTerrain* pGestTer, Ogre::Camera *pCam);

	virtual ~Chunk();

	/* Ajoute l'adresse d'un élément du terrain */
	/* pShape, un élément du terrain de la taille passée en paramètre au constructeur */
	/* x, la position en x du chunk dans la grille */
	/* y, la position en y du chunk dans la grille */
	/* Note: Acquiert une référence sur l'objet */
	bool addChunkPtr(hkpRigidBody* pBody, unsigned int x, unsigned int y);

	/* Valide la construction de la grille de chunks, tous les chunks doivent avoir été ajoutés, sinon lève une exception */
	void ready();

	/* Supprime le chunk enregistré en x et y dans la grille */
	/* Libère la référence */
	/* L'objet peut s'auto-détruire */
	bool removeChunkPtr(unsigned int x, unsigned int y);

	/* Renvoie un tableau de 9 chunks  avec celui où se trouve le joueur au centre */
	/* Si le joueur est au bord de la map certains pointeurs seront nullptr */
	TableauChunks const& getCurrentChunks() const;

	/* Mise à jour des chunks */
	/* Lève une exception si les chunks ne sont pas 'ready' */
	virtual bool frameRenderingQueued(Ogre::FrameEvent const& rEv) override; 
};