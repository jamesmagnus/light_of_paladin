﻿#pragma once

#include "Affichable.h"

class Personnage;

/* Classe abstraite qui sert de base à tous les objets du jeu */
/* Sémantique d'entité */
class Item: public Affichable
{
protected:

	unsigned long mID;
	int mPrix;
	float mPoid;
	std::string mNom;
	bool mIsUnique;

public:

	/* Constructeur */
	/* pNode, l'adresse du noeud de Ogre */
	/* prix, poid, nom, caractéristiques de l'item */
	/* IsUnique, true si l'item ne peut se trouver 2 fois dans un même inventaire, false par défaut */
	/* IsVisible, true si l'item doit être rendu par Ogre */
	Item(Ogre::SceneNode *pNode, int prix=0, float poid=1.0, std::string const& nom="defaultItem", bool IsUnique=false, bool IsVisible=true);

	/* Destructeur */
	virtual ~Item();

	/* Renvoie true si le joueur peut utiliser l'item */
	/* Méthode virtuelle pure */
	virtual bool canUse(Personnage const& rJoueur) const = 0;

	/* Renvoie le prix de l'item */
	int getPrix() const;

	/* Change le prix de l'item */
	void setPrix(int prix);

	/* Renvoie le poid de l'item */
	float getPoid() const;

	/* Change le poid de l'item */
	void setPoid(float poid);

	/* Renvoie l'ID unique de l'item */
	unsigned long getID() const;

	/* Renvoie le nom de l'item */
	std::string const& getNom() const;

	/* Change le nom de l'item */
	void setNom(std::string const& nom);

	/* Renvoie true si l'item ne peut être 2 fois dans un même inventaire */
	bool getIsUnique() const;

	/* Défini si un item peut être plusieurs fois dans un même inventaire */
	void setIsUnique(bool IsUnique);

	/* Clonage, méthode virtuelle pure */
	virtual Item* clone() const =0;

	/* Méthode virtuelle de comparaison entre deux objets */
	virtual bool compare(Item const& secondItem) const;

#ifdef _DEBUG
	/* Affiche des informations sur l'objet dans la console, DEBUG */
	virtual void afficheDebug(std::ostream& rOst) const override;
#endif
};

/* Surcharge des opérateurs externes */

/* == */
bool operator==(Item const& obj1, Item const& obj2);