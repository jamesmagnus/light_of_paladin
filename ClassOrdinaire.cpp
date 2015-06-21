#include "StdLibAndNewOperator.h"
#include "ClassOrdinaire.h"

Ordinaire::Ordinaire(Ogre::SceneNode *pNode, EShape shapeType, bool IsVisible, int vie, std::string const& nom) :Creature(pNode, shapeType, IsVisible, vie, nom)
{

}

Ordinaire::~Ordinaire()
{

}
