#include "StdLibAndNewOperator.h"
#include "ClassPoison.h"

Poison::Poison(Ogre::SceneNode *pNode, EShape shapeType, int prix, float poid, std::string const& nom, bool IsUnique, bool IsVisible) :Potion(pNode, shapeType, prix, poid, nom, IsUnique, IsVisible)
{

}


Poison::~Poison()
{

}
