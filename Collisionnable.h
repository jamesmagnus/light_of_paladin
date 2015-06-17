#pragma once

/* Classe de base pour les objets dont la physique doit être gérée */
/* Sémantique d'entité hérite de boost::noncopyable */
class Collisionnable
{
public:
	Collisionnable();
	virtual ~Collisionnable();
};

