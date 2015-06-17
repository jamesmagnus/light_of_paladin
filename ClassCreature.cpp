#include "StdLibAndNewOperator.h"
#include "ClassCreature.h"

Creature::Creature(Ogre::SceneNode *pNode, bool IsVisible, int vie, std::string const& nom):EntiteVivante(pNode, IsVisible, vie, nom)
{

}

Creature::~Creature()
{

}
