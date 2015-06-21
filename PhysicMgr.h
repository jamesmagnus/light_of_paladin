#pragma once

#include <boost/core/noncopyable.hpp>

class btDefaultCollisionConfiguration;
class btCollisionDispatcher;
class btDiscreteDynamicsWorld;
class btBroadphaseInterface;
class btSequentialImpulseConstraintSolver;
class Collisionnable;

/* Classe pour gérer le moteur de physique du jeu (Bullet) */
/* Sémantique d'entité hérite de boost::noncopyable */
/* Classe finale non dérivable*/
class PhysicMgr final: boost::noncopyable
{
public:

	/* Constructeur */
	PhysicMgr();

	/* Destructeur */
	~PhysicMgr();

	/* Initialise Bullet */
	/* Renvoie true si OK, false sinon*/
	bool initBullet();

	/* Libère les ressources allouées pour Bullet */
	void destroyBullet();

	/* Ajoute un object dérivé de Collisionnable au monde */
	void addObjectToWorld(Collisionnable *pColl) const;

private:
	btDefaultCollisionConfiguration *mpCollisionCfg;
	btCollisionDispatcher *mpCollisionDispatch;
	btDiscreteDynamicsWorld *mpWorld;
	btBroadphaseInterface *mpBroadphase;
	btSequentialImpulseConstraintSolver *mpConstraintSolv;
};

