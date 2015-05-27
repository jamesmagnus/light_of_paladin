﻿#pragma once

#include "ClassPotion.h"

class Poison :public Potion
{
public:

    /* Constructeur */
    /* pNode, l'adresse du noeud de Ogre */
    /* prix, poid, nom, caractéristiques de l'item */
    /* IsUnique, true si l'item ne peut se trouver 2 fois dans un même inventaire, false par défaut */
    /* IsVisible, true si l'item doit être rendu par Ogre */
    Poison(Ogre::SceneNode *pNode, int prix=0, float poid=1.0, std::string const& nom="defaultPoisonPotion", bool IsUnique=false, bool IsVisible=true);

    /* Destructeur */
    virtual ~Poison();
};

