#pragma once

#include "ClassEntiteVivante.h"

/* Classe abstraite pour gérer les humanoïdes, sémantique d'entité */
class Humanoide :public EntiteVivante
{
private:
	int mana;

public:

	/* Constructeur */
	/* pNode, adresse du noeud de scène lié à l'objet */
	/* shapeType, enum Shape qui détermine quel forme est utilisée pour représenter l'objet */
	/* IsVisible, true si l'objet doit être rendu */
	/* vie, la vie de l'entité */
	/* nom, le nom de l'entité */
	Humanoide(Ogre::SceneNode *pNode, EShape shapeType, bool IsVisible, int vie, std::string const& nom="DefaultHuma");

	/* Destructeur */
	virtual ~Humanoide();

	/* Clonage, méthode virtuelle pure */
	virtual Humanoide* clone() const override=0;

#ifdef _DEBUG
	/* Affiche des informations sur l'objet dans la console, DEBUG */
	virtual void afficheDebug(std::ostream& rOst) const override=0;
#endif
};


/* Surcharge des opérateurs externes */

#ifdef _DEBUG
/* << */
std::ostream& operator<<(std::ostream& rOst, Humanoide const& obj);
#endif