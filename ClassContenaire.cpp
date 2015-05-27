#include "ClassContenaire.h"
#include "ClassItem.h"

#include <string>
#include <assert.h>

using namespace std;

Contenaire::Contenaire(Ogre::SceneNode *pNode, bool IsVisible, int max):Affichable(pNode, IsVisible), Inventaire(max)
{
	mNom = "Coffre";
}

Contenaire::Contenaire(Ogre::SceneNode *pNode, Inventaire& inv, bool IsVisible):Affichable(pNode, IsVisible), Inventaire(inv)
{
	inv.clear();
	mNom = "Coffre";
}

Contenaire::~Contenaire()
{

}

Contenaire* Contenaire::clone() const
{
	Inventaire invTemp(mMax);

	for (auto it : mStuff)
	{
		invTemp.ajout(it.second->clone());
	}

	assert(invTemp.getNB() == getNB());

	return new Contenaire(mpNoeud, invTemp, mIsVisible);
}

#ifdef _DEBUG
void Contenaire::afficheDebug(ostream& rOst) const 
{
	rOst << "Type: Contenaire" << endl << "Occupation:" << mNb << " sur" << mMax << endl << "Poid:" << mPoidTotal << "Nom:" << mNom << "Propriétaire:" << mProprietaire << endl << endl;
}
#endif

void Contenaire::setProprietaire(string const& nom)
{
	if(nom == "")
	{
		mProprietaire = "all";
	}
	else
	{
		mProprietaire = nom;
	}
}

string Contenaire::getProprietaire() const
{
	return mProprietaire;
}

void Contenaire::setNom(string const& nom)
{
	if (nom == "")
	{
		mNom = "Coffre";
	} 
	else
	{
		mNom = nom;
	}
}

string Contenaire::getNom() const
{
	return mNom;
}

/* Surcharge des opérateurs externes */

#ifdef _DEBUG
/* << */
ostream& operator<<(ostream& rOst, Contenaire const& obj)
{
	obj.afficheDebug(rOst);
	return rOst;
}
#endif