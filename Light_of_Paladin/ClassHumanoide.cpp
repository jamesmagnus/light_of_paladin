#include "StdLibAndNewOperator.h"
#include "ClassHumanoide.h"

Humanoide::Humanoide(Ogre::SceneNode *pNode, EShape shapeType, bool IsVisible, int vie, std::string const& nom) :EntiteVivante(pNode, shapeType, IsVisible, vie, nom)
{
}

Humanoide::~Humanoide()
{
}

/* Surcharge des opérateurs externes */

#ifdef _DEBUG
/* << */
std::ostream& operator<<(std::ostream& rOst, Humanoide const& obj)
{
	obj.afficheDebug(rOst);

	return rOst;
}
#endif