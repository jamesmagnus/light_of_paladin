#include "StdLibAndNewOperator.h"
#include "ClassPotion.h"

Potion::Potion(Ogre::SceneNode *pNode, EShape shapeType, int prix, float poid, std::string const& nom, bool IsUnique, bool IsVisible) :Consommable(pNode, shapeType, prix, poid, nom, IsUnique, IsVisible)
{

}

Potion::~Potion()
{

}
