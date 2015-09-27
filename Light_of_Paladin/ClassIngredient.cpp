#include "StdLibAndNewOperator.h"
#include "ClassIngredient.h"

Ingredient::Ingredient(Ogre::SceneNode *pNode, EShape shapeType, int prix, float poid, std::string const& nom, bool IsUnique, bool IsVisible) :Consommable(pNode, shapeType, prix, poid, nom, IsUnique, IsVisible)
{

}

Ingredient::~Ingredient()
{

}
