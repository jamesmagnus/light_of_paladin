#pragma once

#include "enumerations.h"

#include <LinearMath/btScalar.h>
#include <LinearMath/btVector3.h>
#include <LinearMath/btDefaultMotionState.h>


class btCollisionShape;
class btTransform;
class btRigidBody;
class btMotionState;

/* Classe de base pour les objets dont la physique doit être gérée */
/* Sémantique d'entité hérite de boost::noncopyable */
class Collisionnable
{
public:

	/* Constructeur */
	/* shapeType, enum Shape qui détermine quel forme est utilisée pour représenter l'objet */
	Collisionnable(EShape shapeType);

	/* Destructeur */
	virtual ~Collisionnable();

	/* Renvoie une référence sur la matrice de transformation Bullet */
	 inline btTransform const& getTransform() const;

	 /* Défini la masse */
	 inline void setMasse(btScalar masse);

	 /* Calcul l'inertie */
	 void calcInertie();

	 /* Génère le motionState */
	 /* Renvoie true si le motionState existait déjà, false sinon */
	 bool createMotionState();

	 /* Crée le body */
	 /* Renvoie true si le body était déjà crée, false sinon */
	 bool createBody();

	 /* Renvoie l'adresse du body */
	 inline btRigidBody const * getBodyPtr() const;


protected:
	btCollisionShape *mpCollShape;
	btTransform *mpTransform;
	btVector3 mInertie;
	btScalar mMasse;
	btMotionState *mpMotionState;
	btRigidBody *mpBody;

	EShape mType;
};

inline btTransform const& Collisionnable::getTransform() const
{
	return *mpTransform;
}

inline void Collisionnable::setMasse(btScalar masse)
{
	if (masse >= 0.0)
	{
		mMasse = masse;
	}
}

inline btRigidBody const* Collisionnable::getBodyPtr() const
{
	return mpBody;
}