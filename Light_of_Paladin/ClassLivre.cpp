#include "StdLibAndNewOperator.h"
#include "ClassLivre.h"

Livre::Livre(Ogre::SceneNode *pNode, EShape shapeType, int prix, float poid, std::string const& nom, bool IsUnique, bool IsVisible) :Document(pNode, shapeType, prix, poid, nom, IsUnique, IsVisible)
{

}

Livre::~Livre()
{

}
