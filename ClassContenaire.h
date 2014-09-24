#pragma once

#include "classinventaire.h"
#include "Affichable.h"

class Contenaire : public Inventaire, Affichable
{
public:

    /* Constructeur */
    /* pNode, adresse du noeud de scène lié à l'objet */
    /* IsVisible, true si l'objet doit être rendu, true par défaut */
    /* max, la taille de l'inventaire du contenaire */
    Contenaire(Ogre::SceneNode *pNode, bool IsVisible=true, int max=10);

    /* Destructeur */
    virtual ~Contenaire();
};

