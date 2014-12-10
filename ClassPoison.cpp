#include "ClassPoison.h"

Poison::Poison(Ogre::SceneNode *pNode, int prix, float poid, std::string nom, bool IsUnique, bool IsVisible):Potion(pNode, prix, poid, nom, IsUnique, IsVisible)
{

}


Poison::~Poison()
{

}
