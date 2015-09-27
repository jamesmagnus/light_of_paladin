#pragma once

#include "ClassEntiteVivante.h"

class Creature :public EntiteVivante
{
public:

    /* Constructeur */
    /* pNode, adresse du noeud de scène lié à l'objet */
	/* shapeType, enum Shape qui détermine quel forme est utilisée pour représenter l'objet */
    /* IsVisible, true si l'objet doit être rendu */
    /* vie, la vie de l'entité */
    /* nom, le nom de l'entité */
    Creature(Ogre::SceneNode *pNode, EShape shapeType, bool IsVisible, int vie, std::string const& nom="DefaultName");

    /* Destructeur */
    virtual ~Creature();
};

