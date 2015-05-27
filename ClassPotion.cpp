#include "ClassPotion.h"

Potion::Potion(Ogre::SceneNode *pNode, int prix, float poid, std::string const& nom, bool IsUnique, bool IsVisible):Consommable(pNode, prix, poid, nom, IsUnique, IsVisible)
{

}

Potion::~Potion()
{

}
