﻿#pragma once

#include <iostream>
#include <boost/core/noncopyable.hpp>

namespace Ogre
{
	class SceneNode;
}

/* Classe abstraite servant de base à tous les éléments affichables du jeu */
/* Sémantique d'entité, hérite de boost::noncopyable */
class Affichable: private boost::noncopyable
{
protected:
	Ogre::SceneNode *mpNoeud;
	bool mIsVisible;

public:

	/* Constructeur */
	/* pNode, adresse du noeud de scène lié à l'objet */
	/* IsVisible, true si l'objet doit être rendu, true par défaut */
	Affichable(Ogre::SceneNode *pNode, bool IsVisible=true);

	/* Clonage, méthode virtuelle pure */
	virtual Affichable* clone() const =0;

	/* Destructeur */
	/* Le noeud de scène n'est pas détruit */
	virtual ~Affichable();

	/* Modifie l'état d'affichage */
	void setVisibility(bool visible);

	/* Renvoie true si l'objet est rendu par Ogre */
	bool getVisibility() const;

	/* Assigne un nouveau noeud Ogre */
	/* Renvoie true s'il y avait un noeud valide */
	bool setNode(Ogre::SceneNode *pNoeud);

	/* Renvoie l'adresse du noeud Ogre ou nullptr */
	Ogre::SceneNode* getNode() const;

#ifdef _DEBUG
	/* Affiche des informations sur l'objet dans la console, DEBUG */
		virtual void afficheDebug(std::ostream& rOst) const;
#endif
	
};

/* Surcharge opérateurs externes */

#ifdef _DEBUG
/* << */
std::ostream& operator<<(std::ostream& rOst, Affichable const& obj);
#endif
