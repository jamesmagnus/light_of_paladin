#include "ClassPotion.h"

Potion::Potion(unsigned long id, Ogre::SceneNode *pNode, int prix, float poid, std::string nom, bool IsUnique, bool IsVisible):Consommable(id, pNode, prix, poid, nom, IsUnique, IsVisible)
{

}

Potion::~Potion()
{

}
