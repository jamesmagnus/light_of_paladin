#include "StdLibAndNewOperator.h"
#include "ClassBonne.h"

Bonne::Bonne(Ogre::SceneNode *pNode, EShape shapeType, int prix, float poid, std::string const& nom, bool IsUnique, bool IsVisible) :Potion(pNode, shapeType, prix, poid, nom, IsUnique, IsVisible)
{

}

Bonne::~Bonne()
{

}
