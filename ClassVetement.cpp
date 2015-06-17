#include "StdLibAndNewOperator.h"
#include "ClassVetement.h"

Vetement::Vetement(Ogre::SceneNode *pNode, int prix, float poid, std::string const& nom, bool IsUnique, bool IsVisible, Sort *pEnchantement):Enchante(pNode, prix, poid, nom, IsUnique, IsVisible, pEnchantement)
{

}

Vetement::~Vetement()
{
}