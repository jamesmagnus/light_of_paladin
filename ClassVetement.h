#pragma once

#include "ClassEnchante.h"

class Vetement :public Enchante
{
public:

    /* Constructeur */
    /* pNode, l'adresse du noeud de Ogre */
    /* prix, poid, nom, caractéristiques du vêtement */
    /* IsUnique, true si le vêtement ne peut se trouver 2 fois dans un même inventaire, false par défaut */
    /* IsVisible, true si le vêtement doit être rendu par Ogre */
    Vetement(Ogre::SceneNode *pNode, int prix=0, float poid=1.0, std::string const& nom="defaultClothe", bool IsUnique=false, bool IsVisible=true, Sort *pEnchantement=nullptr);

    /* Destructeur */
    virtual ~Vetement();

	/* Prédicat, renvoie true si le personnage peut s'équiper du vetement */
	/* Méthode virtuelle pure */
	bool canUse(Personnage const& rJoueur) const override =0; 
};

