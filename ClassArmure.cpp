#include "ClassArmure.h"

using namespace std;

Armure::Armure(Ogre::SceneNode *pNode, ETypeArmure type, int prix, float poid, string nom, bool IsUnique, bool IsVisible, int pointProtection, float etat): Item(pNode, prix, poid, nom, IsUnique, IsVisible)
{
	if (pointProtection >= 0)
	{
		mPtsProtection = pointProtection;
	}
	else
	{
		mPtsProtection = 0;
	}

	etat = Ogre::Math::Clamp(etat, 0.0f, 1.0f);
	mEtat = etat;
	mType = type;
}


Armure::~Armure()
{

}

int Armure::getPtsProtection() const
{
	return mPtsProtection;
}

void Armure::setPtsProtection(int pts)
{
	if (pts >= 0)
	{
		mPtsProtection = pts;
	}
}

float Armure::getEtat() const
{
	return mEtat;
}

void Armure::setEtat(float etat)
{
	etat = Ogre::Math::Clamp(etat, 0.0f, 1.0f);
	mEtat = etat;
}

#ifdef _DEBUG
void Armure::afficheDebug(ostream& rOst) const 
{
	string stype;

	switch (mType)
	{
	case ETypeArmure::CASQUE:
		stype = ("Casque");
		break;
	case ETypeArmure::PLASTRON:
		stype = ("Plastron");
		break;
	case ETypeArmure::GANT_G:
		stype = ("Gant gauche");
		break;
	case ETypeArmure::GANT_D:
		stype = ("Gant droit");
		break;
	case ETypeArmure::BOTTE_G:
		stype = ("Botte gauche");
		break;
	case ETypeArmure::BOTTE_D:
		stype = ("Botte droite");
		break;
	case ETypeArmure::JAMBIERE_G:
		stype = ("Jambiere gauche");
		break;
	case ETypeArmure::JAMBIERE_D:
		stype = ("Jambiere droite");
		break;
	}
	cout << "Type:Armure" << endl;
	Item::afficheDebug(rOst);
	cout << "Sous-type:" << stype << endl << "Protection:" << mPtsProtection << endl << "Etat:" << mEtat*100 << "%" << endl << "-----------------------------------------------" << endl;
}
#endif

ETypeArmure Armure::getType() const
{
	return mType;
}

void Armure::setType(ETypeArmure type)
{
	mType = type;
}

Armure* Armure::clone() const 
{
	return new Armure(mpNoeud, mType, mPrix, mPoid, mNom, mIsUnique, mIsVisible, mPtsProtection, mEtat);
}

bool Armure::canUse(Personnage *pJoueur) const 
{
	/*TODO*/
	return true;
}

bool Armure::compare(Item const& rSecondeArmure) const 
{
	/* D'après le RTTI l'Item passé en paramètre est une Armure */

	const Armure& rSecondeArmureConvertie = dynamic_cast<Armure const&>(rSecondeArmure);

	/* Leur id, leur état, leur affichage peuvent être différent mais le reste doit être identique */
	return (mIsUnique == rSecondeArmureConvertie.mIsUnique && 
		mNom == rSecondeArmureConvertie.mNom && 
		mPoid == rSecondeArmureConvertie.mPoid && 
		mPrix == rSecondeArmureConvertie.mPrix && 
		mPtsProtection == rSecondeArmureConvertie.mPtsProtection && 
		mType == rSecondeArmureConvertie.mType);
}


/* Surcharge des opérateurs externes */

#ifdef _DEBUG
/* << */
ostream& operator<<(ostream& rOst, Armure const& obj)
{
	obj.afficheDebug(rOst);

	return rOst;
}
#endif