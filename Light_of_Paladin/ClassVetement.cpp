#include "StdLibAndNewOperator.h"
#include "ClassVetement.h"

Vetement::Vetement(Ogre::SceneNode *pNode, EShape shapeType, int prix, float poid, std::string const& nom, bool IsUnique, bool IsVisible, Sort *pEnchantement) :Enchante(pNode, shapeType, prix, poid, nom, IsUnique, IsVisible, pEnchantement)
{

}

Vetement::~Vetement()
{
}