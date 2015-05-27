#include "ClassLivre.h"

Livre::Livre(Ogre::SceneNode *pNode, int prix, float poid, std::string const& nom, bool IsUnique, bool IsVisible):Document(pNode, prix, poid, nom, IsUnique, IsVisible)
{

}

Livre::~Livre()
{

}
