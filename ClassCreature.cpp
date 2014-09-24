#include "ClassCreature.h"

Creature::Creature(Ogre::SceneNode *pNode, bool IsVisible, int vie, std::string nom):EntiteVivante(pNode, IsVisible, vie, nom)
{

}

Creature::~Creature()
{

}
