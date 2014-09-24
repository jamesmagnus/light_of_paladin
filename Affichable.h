#pragma once

#include <Ogre.h>

class Affichable
{
protected:
    Ogre::SceneNode *mpNoeud;
    bool mIsVisible;

public:

    /* Constructeur */
    /* pNode, adresse du noeud de scène lié à l'objet */
    /* IsVisible, true si l'objet doit être rendu, true par défaut */
    Affichable(Ogre::SceneNode *pNode, bool IsVisible=true);

    /* Destructeur */
    /* Le noeud de scène n'est pas détruit */
    virtual ~Affichable();

    /* Modifie l'état d'affichage */
    void setVisibility(bool visible);

    /* Renvoie true si l'objet est rendu par Ogre */
    bool getVisibility() const;

    /* Assigne un nouveau noeud Ogre */
    /* Renvoie true s'il y avait un noeud valide */
    bool setNode(Ogre::SceneNode *pNoeud);

    /* Renvoie l'adresse du noeud Ogre ou nullptr */
    Ogre::SceneNode* getNode() const;
};

