#include "StdLibAndNewOperator.h"
#include "ClassEntiteVivante.h"


EntiteVivante::EntiteVivante(Ogre::SceneNode *pNode, EShape shapeType, bool IsVisible, int vie, std::string const& nom) : Affichable(pNode, IsVisible), Collisionnable(shapeType)
{
	mVie = vie;
	mNom = nom;
}


EntiteVivante::~EntiteVivante()
{
}

/* Surcharge des opérateurs externes */

#ifdef _DEBUG
/* << */
std::ostream& operator<<(std::ostream& rOst, EntiteVivante const& obj)
{
	obj.afficheDebug(rOst);

	return rOst;
}
#endif