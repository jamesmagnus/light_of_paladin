#include "ClassDocument.h"

Document::Document(unsigned long id, Ogre::SceneNode *pNode, int prix, float poid, std::string nom, bool IsUnique, bool IsVisible):Item(id, pNode, prix, poid, nom, IsUnique, IsVisible)
{

}

Document::~Document()
{

}
