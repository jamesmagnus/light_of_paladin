#pragma once

#include "Affichable.h"

namespace Ogre
{
	class SceneNode;
}

class Inventaire;

/* Classe de base abstraite pour les entités vivantes du jeu */
/* Sémantique d'entité */
class EntiteVivante: public Affichable
{
protected:
	int mVie;
	std::string mNom;
	Inventaire *mpInventaire;

public:

	/* Constructeur */
	/* pNode, adresse du noeud de scène lié à l'objet */
	/* IsVisible, true si l'objet doit être rendu */
	/* vie, la vie de l'entité */
	/* nom, le nom de l'entité */
	EntiteVivante(Ogre::SceneNode *pNode, bool IsVisible, int vie, std::string nom="DefaultName");

	/* Destructeur */
	virtual ~EntiteVivante();

	/* Clonage, méthode virtuelle pure */
	virtual EntiteVivante* clone() const override=0;

#ifdef _DEBUG
	/* Affiche des informations sur l'objet dans la console, DEBUG  */
	virtual void afficheDebug(std::ostream& rOst) const override=0;
#endif
};


/* Surcharge des opérateurs externes */

#ifdef _DEBUG
/* << */
std::ostream& operator<<(std::ostream& rOst, EntiteVivante const& obj);
#endif