#pragma once

#include "Classentitevivante.h"

/* Classe abstraite pour gérer les humanoïdes, sémantique d'entité */
class Humanoide :public EntiteVivante
{
private:
	int mana;

private:

	/* Constructeur de copie interdit */
	Humanoide(Humanoide const& rOriginal);

	/* Opérateur d'assignement interdit */
	Humanoide& operator=(Humanoide const& rOriginal);

public:

	/* Constructeur */
	/* pNode, adresse du noeud de scène lié à l'objet */
	/* IsVisible, true si l'objet doit être rendu */
	/* vie, la vie de l'entité */
	/* nom, le nom de l'entité */
	Humanoide(Ogre::SceneNode *pNode, bool IsVisible, int vie, std::string nom="DefaultHuma");

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