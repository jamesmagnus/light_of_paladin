#pragma once

#include "ClassEnchante.h"

/* Classe abstraite pour gérer créer les différents documents du jeu */
/* Sémantique d'entité */
class Document: public Enchante
{
private:
	std::string mContenu;
	std::string mTitre;

public:

	/* Constructeur */
	/* pNode, l'adresse du noeud de Ogre */
	/* shapeType, enum Shape qui détermine quel forme est utilisée pour représenter l'objet */
	/* prix, poid, nom, caractéristiques de l'item */
	/* IsUnique, true si l'item ne peut se trouver 2 fois dans un même inventaire, false par défaut */
	/* IsVisible, true si l'item doit être rendu par Ogre */
	/* pEnchantement, pointeur vers un sort qui constitue l'enchantement du document ou nullptr si pas d'enchantement */
	Document(Ogre::SceneNode *pNode, EShape shapeType, int prix=0, float poid=1.0, std::string const& nom="defaultDocument", bool IsUnique=false, bool IsVisible=true, Sort *pEnchantement=nullptr);

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
