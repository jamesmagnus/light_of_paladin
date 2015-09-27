#include "StdLibAndNewOperator.h"
#include "ClassNote.h"

Note::Note(Ogre::SceneNode *pNode, EShape shapeType, int prix, float poid, std::string const& nom, bool IsUnique, bool IsVisible) :Document(pNode, shapeType, prix, poid, nom, IsUnique, IsVisible)
{

}

Note::~Note()
{

}
