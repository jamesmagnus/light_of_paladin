#pragma once

#include "ClassVetement.h"

class Chaussure :public Vetement
{
public:

	/* Constructeur */
	/* pNode, l'adresse du noeud de Ogre */
	/* prix, poid, nom, caractéristiques de la chaussure */
	/* IsUnique, true si la chaussure ne peut se trouver 2 fois dans un même inventaire, false par défaut */
	/* IsVisible, true si la chaussure doit être rendu par Ogre */
	/* pEnchantement, pointeur vers un sort qui constitue l'enchantement des chaussures ou nullptr si pas d'enchantement */
	Chaussure(Ogre::SceneNode *pNode, int prix=0, float poid=1.0, std::string const& nom="defaultShoes", bool IsUnique=false, bool IsVisible=true, Sort *pEnchantement=nullptr);

	/* Destructeur */
	virtual ~Chaussure();
};

