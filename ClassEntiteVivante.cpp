#include "ClassEntiteVivante.h"


EntiteVivante::EntiteVivante(Ogre::SceneNode *pNode, bool IsVisible, int vie, std::string nom): Affichable(pNode, IsVisible)
{
    mVie = vie;
    mNom = nom;
}


EntiteVivante::~EntiteVivante()
{
}
