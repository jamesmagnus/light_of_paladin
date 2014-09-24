#include "ClassContenaire.h"


Contenaire::Contenaire(Ogre::SceneNode *pNode, bool IsVisible, int max):Affichable(pNode, IsVisible), Inventaire(max)
{

}


Contenaire::~Contenaire()
{

}
