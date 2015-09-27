#include "StdLibAndNewOperator.h"
#include "ClassCreature.h"

Creature::Creature(Ogre::SceneNode *pNode, EShape shapeType, bool IsVisible, int vie, std::string const& nom): EntiteVivante(pNode, shapeType, IsVisible, vie, nom)
{

}

Creature::~Creature()
{

}
