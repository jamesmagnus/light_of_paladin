#include "ClassChaussure.h"

Chaussure::Chaussure(Ogre::SceneNode *pNode, int prix, float poid, std::string const& nom, bool IsUnique, bool IsVisible, Sort *pEnchantement):Vetement(pNode, prix, poid, nom, IsUnique, IsVisible, pEnchantement)
{

}


Chaussure::~Chaussure(void)
{
}
