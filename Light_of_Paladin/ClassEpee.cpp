﻿#include "StdLibAndNewOperator.h"
#include "ClassEpee.h"

#include <string>

using namespace Ogre;

Epee::Epee(SceneNode *pNode, EShape shapeType, int degat, float vitesse, float resistance, int prix, float poid, std::string const& nom, bool IsUnique, bool IsVisible) : Arme(pNode, shapeType, degat, vitesse, resistance, prix, poid, nom, IsUnique, IsVisible)
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
	return LOP_NEW Epee(mpNoeud, mType, mDegat, mVitesse, mResistance, mPrix, mPoid, mNom, mIsUnique, mIsVisible);	//TODO
}

bool Epee::canUse(Personnage const& rJoueur) const 
{
	//TODO
	return true;
}

bool Epee::compare(Item const& rSecondeEpee) const 
{
	/* D'après le RTTI l'Item passé en paramètre est une Epée */

	Epee const& rSecondeEpeeConvertie = dynamic_cast<Epee const&>(rSecondeEpee);

	/* Leur id, leur état, leur affichage peuvent être différent mais le reste doit être identique */
	return (Arme::compare(rSecondeEpee));
}
