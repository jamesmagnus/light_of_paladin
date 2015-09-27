﻿#pragma once

#include "ClassPotion.h"

class Bonne :public Potion
{
public:

    /* Constructeur */
    /* pNode, l'adresse du noeud de Ogre */
	/* shapeType, enum Shape qui détermine quel forme est utilisée pour représenter l'objet */
    /* prix, poid, nom, caractéristiques de l'item */
    /* IsUnique, true si l'item ne peut se trouver 2 fois dans un même inventaire, false par défaut */
    /* IsVisible, true si l'item doit être rendu par Ogre */
    Bonne(Ogre::SceneNode *pNode, EShape shapeType, int prix=0, float poid=1.0, std::string const& nom="defaultGoodPotion", bool IsUnique=false, bool IsVisible=true);

    /* Destructeur */
    virtual ~Bonne();
};
