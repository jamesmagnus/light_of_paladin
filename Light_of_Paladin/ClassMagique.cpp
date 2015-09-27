#include "StdLibAndNewOperator.h"
#include "ClassMagique.h"

Magique::Magique(Ogre::SceneNode *pNode, EShape shapeType, bool IsVisible, int vie, std::string const& nom) :Creature(pNode, shapeType, IsVisible, vie, nom)
{

}

Magique::~Magique()
{

}
