#include "ClassVetement.h"

Vetement::Vetement(unsigned long id, Ogre::SceneNode *pNode, int prix, float poid, std::string nom, bool IsUnique, bool IsVisible):Item(id, pNode, prix, poid, nom, IsUnique, IsVisible)
{

}

Vetement::~Vetement()
{
}
