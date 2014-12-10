#include "ClassVetement.h"

Vetement::Vetement(Ogre::SceneNode *pNode, int prix, float poid, std::string nom, bool IsUnique, bool IsVisible):Item(pNode, prix, poid, nom, IsUnique, IsVisible)
{

}

Vetement::~Vetement()
{
}
