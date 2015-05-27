﻿#pragma once

#include "ClassCreature.h"

class Ordinaire :public Creature
{
public:

    /* Constructeur */
    /* pNode, adresse du noeud de scène lié à l'objet */
    /* IsVisible, true si l'objet doit être rendu */
    /* vie, la vie de l'entité */
    /* nom, le nom de l'entité */
    Ordinaire(Ogre::SceneNode *pNode, bool IsVisible, int vie, std::string const& nom="DefaultName");

    /* Destructeur */
    virtual ~Ordinaire();
};

