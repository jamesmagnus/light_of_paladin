#include "StdLibAndNewOperator.h"
#include "ClassChaussure.h"

Chaussure::Chaussure(Ogre::SceneNode *pNode, EShape shapeType, int prix, float poid, std::string const& nom, bool IsUnique, bool IsVisible, Sort *pEnchantement) :Vetement(pNode, shapeType, prix, poid, nom, IsUnique, IsVisible, pEnchantement)
{

}


Chaussure::~Chaussure(void)
{
}
