#include "ClassLivre.h"

Livre::Livre(unsigned long id, Ogre::SceneNode *pNode, int prix, float poid, std::string nom, bool IsUnique, bool IsVisible):Document(id, pNode, prix, poid, nom, IsUnique, IsVisible)
{

}

Livre::~Livre()
{

}
