#pragma once

#include "ClassInventaire.h"
#include "Affichable.h"


/* Classe finale, non héritable */
/* Permet de créer des objets affichable avec un inventaire tel des coffres, ... */
/* Sémantique d'entité */
class Contenaire: public Inventaire, Affichable
{
private:
	std::string mProprietaire, mNom;

	/* Surcharge de la fonction héritée de Inventaire pour empécher qu'elle soit appelée par erreur */
	void afficheDebugInv(std::ostream& rOst) const;

public:

	/* Constructeur */
	/* pNode, adresse du noeud de scène lié à l'objet */
	/* IsVisible, true si l'objet doit être rendu, true par défaut */
	/* max, la taille de l'inventaire du contenaire */
	Contenaire(Ogre::SceneNode *pNode, bool IsVisible=true, int max=10);

	/* Constructeur */
	/* pNode, adresse du noeud de scène lié à l'objet */
	/* IsVisible, true si l'objet doit être rendu, true par défaut */
	/* inv, l'inventaire à partir duquel construire le contenaire, vide cet inventaire */
	Contenaire(Ogre::SceneNode *pNode, Inventaire& inv, bool IsVisible=true);

	/* Destructeur */
	virtual ~Contenaire();

	/* clone un contenaire, devant être libéré */
	/* Renvoie un pointeur */
	/* clone les objets de l'inventaire du contenaire original */
	virtual Contenaire* clone() const override;

#ifdef _DEBUG
	/* Affiche des informations sur l'objet dans la console, DEBUG */
	virtual void afficheDebug(std::ostream& rOst) const override;
#endif
	/* Défini le propriètaire du contenaire */
	/* nom, le nom du propriètaire, par défaut "all", signifiant aucun propriètaire */
	void setProprietaire(std::string const& nom);

	/* Renvoie le nom du propriètaire */
	/* "all" pour aucun propriètaire */
	std::string getProprietaire() const;

	/* Défini le nom du contenaire */
	/* nom, le nom du contenaire, par défaut "Coffre" */
	void setNom(std::string const& nom);

	/* Renvoie le nom du contenaire */
	std::string getNom() const;
};

/* Surcharge des opérateurs externes */

#ifdef _DEBUG
/* << */
std::ostream& operator<<(std::ostream& rOst, Contenaire const& obj);
#endif