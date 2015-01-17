#pragma once

#include "ClassConsommable.h"

class Ingredient :public Consommable
{
public:

    /* Constructeur */
    /* pNode, l'adresse du noeud de Ogre */
    /* prix, poid, nom, caractéristiques de l'item */
    /* IsUnique, true si l'item ne peut se trouver 2 fois dans un même inventaire, false par défaut */
    /* IsVisible, true si l'item doit être rendu par Ogre */
    Ingredient(Ogre::SceneNode *pNode, int prix=0, float poid=1.0, std::string nom="defaultIngredient", bool IsUnique=false, bool IsVisible=true);

    /* Destructeur */
    virtual ~Ingredient();
};

