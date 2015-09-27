#include "StdLibAndNewOperator.h"
#include "ClassCle.h"

Cle::Cle(Ogre::SceneNode *pNode, EShape shapeType, int prix, float poid, std::string const& nom, bool IsUnique, bool IsVisible) :Item(pNode, shapeType, prix, poid, nom, IsUnique, IsVisible)
{

}

Cle::~Cle()
{

}
