#include "ClassHumanoide.h"

Humanoide::Humanoide(Ogre::SceneNode *pNode, bool IsVisible, int vie, std::string nom):EntiteVivante(pNode, IsVisible, vie, nom)
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