#pragma once

#include <utility>
#include <boost/noncopyable.hpp>

class GestionnaireTerrain;
class hkpRigidBody;

class Chunk: private boost::noncopyable
 {
 public:

 	/* Constructeur */
 	/* pTerrainMgr, adresse du gestionnaire de terrain */
 	/* pos, position en x et y du chunk à créer, < MAX_CHUNK_COO */
 	Chunk(GestionnaireTerrain* pTerrainMgr, std::pair<int, int> pos);

 	/* Destructeur */
 	~Chunk();

 	 /* Charge le hkpRigidBody en mémoire s'il ne l'est pas déjà */
	/* Renvoie true s'il était chargé, false sinon */
 	 /* Lève une exception en cas de problème */
 	 bool loadBody();

 	 /* Libère la mémoire utilisée par le hkpRigidBody */
 	 /* Sur requête du gestionnaire de terrain uniquement ! */
 	 /* Lève une exception en cas de problème */
 	 void destroyBody();

 private:

 	bool mIsBodyInMemory;
 	hkpRigidBody* mpRigidBody;
	GestionnaireTerrain* mpTerrainMgr;
	std::pair<int, int> mPos;
 };