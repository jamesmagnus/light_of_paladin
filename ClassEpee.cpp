#include "ClassEpee.h"

using namespace Ogre;

Epee::Epee(SceneNode *pNode, int degat, float vitesse, float resistance, int prix, float poid, std::string nom, bool IsUnique, bool IsVisible): Arme(pNode, degat, vitesse, resistance, prix, poid, nom, IsUnique, IsVisible)
{
}

Epee::~Epee()
{
}

#ifdef _DEBUG
void Epee::afficheDebug(std::ostream& rOst) const 
{
	rOst << "Type:Epee" << std::endl;
	Arme::afficheDebug(rOst);
}

#endif
Epee* Epee::clone() const 
{
	return new Epee(mpNoeud, mDegat, mVitesse, mResistance, mPrix, mPoid, mNom, mIsUnique, mIsVisible);
}

bool Epee::canUse(Personnage *pJoueur) const 
{
	//TODO
	return true;
}

bool Epee::compare(Item const& rSecondeEpee) const 
{
	/* D'après le RTTI l'Item passé en paramètre est une Epée */

	const Epee& rSecondeEpeeConvertie = dynamic_cast<Epee const&>(rSecondeEpee);

	/* Leur id, leur état, leur affichage peuvent être différent mais le reste doit être identique */
	return (mIsUnique == rSecondeEpeeConvertie.mIsUnique && 
		mNom == rSecondeEpeeConvertie.mNom && 
		mPoid == rSecondeEpeeConvertie.mPoid && 
		mPrix == rSecondeEpeeConvertie.mPrix && 
		mResistance == rSecondeEpeeConvertie.mResistance && 
		mDegat == rSecondeEpeeConvertie.mDegat && 
		mVitesse == rSecondeEpeeConvertie.mVitesse);
}

/* Surcharge des opérateurs externes */

#ifdef _DEBUG
/* << */
std::ostream& operator<<(std::ostream& rOst, Epee const& obj)
{
	obj.afficheDebug(rOst);

	return rOst;
}
#endif