#pragma once

#include <string>
#include <Ogre.h>

#include "Affichable.h"

class EntiteVivante: public Affichable
{
protected:
    int mVie;
    std::string mNom;

public:

    /* Constructeur */
    /* pNode, adresse du noeud de scène lié à l'objet */
    /* IsVisible, true si l'objet doit être rendu */
    /* vie, la vie de l'entité */
    /* nom, le nom de l'entité */
    EntiteVivante(Ogre::SceneNode *pNode, bool IsVisible, int vie, std::string nom="DefaultName");

    /* Destructeur */
    virtual ~EntiteVivante();
};

