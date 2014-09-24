#pragma once

#include "Classentitevivante.h"

class Humanoide :public EntiteVivante
{
public:

    /* Constructeur */
    /* pNode, adresse du noeud de scène lié à l'objet */
    /* IsVisible, true si l'objet doit être rendu */
    /* vie, la vie de l'entité */
    /* nom, le nom de l'entité */
    Humanoide(Ogre::SceneNode *pNode, bool IsVisible, int vie, std::string nom="DefaultName");

    /* Destructeur */
    virtual ~Humanoide();
};

