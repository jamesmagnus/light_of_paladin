#pragma once

#include "ClassItem.h"

/* Classe abstraite pour gérer créer les différents documents du jeu */
/* Sémantique d'entité */
class Document: public Item
{
private:
	std::string mContenu;
	std::string mTitre;

public:

	/* Constructeur */
	/* pNode, l'adresse du noeud de Ogre */
	/* prix, poid, nom, caractéristiques de l'item */
	/* IsUnique, true si l'item ne peut se trouver 2 fois dans un même inventaire, false par défaut */
	/* IsVisible, true si l'item doit être rendu par Ogre */
	Document(Ogre::SceneNode *pNode, int prix=0, float poid=1.0, std::string const& nom="defaultDocument", bool IsUnique=false, bool IsVisible=true);

	/* Modifie le titre du document */
	/* titre, une std::string */
	void setTitre(std::string const& titre);

	/* Renvoie le titre du document, std::string */
	std::string const& getTitre() const;

	/* Modifie le contenu du document */
	/* contenu, une std::string */
	void setContenu(std::string const& contenu);

	/* Renvoie le contenu du document, std::string */
	std::string const& getContenu() const;

#ifdef _DEBUG
	/* Affiche des informations sur l'objet dans la console, DEBUG , méthode virtuelle pure*/
	virtual void afficheDebug(std::ostream& rOst) const override=0;
#endif

	/* Destructeur */
	virtual ~Document();
};


/* Surcharge des opérateurs externes */

#ifdef _DEBUG
/* << */
std::ostream& operator<<(std::ostream& rOst, Document const& obj);
#endif