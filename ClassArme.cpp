#include "StdLibAndNewOperator.h"
#include "ClassArme.h"

#include <OgreMath.h>


using namespace std;

Arme::Arme(Ogre::SceneNode *pNode, EShape shapeType, int degat, float vitesse, float resistance, int prix, float poid, std::string const& nom, bool IsUnique, bool IsVisible, Sort *pEnchantement) : Enchante(pNode, shapeType, prix, poid, nom, IsUnique, IsVisible, pEnchantement)
{
    if (degat >= 0)
    {
        mDegat = degat;
    }
    else
    {
        mDegat = 0;
    }

    if (vitesse > 0.0f)
    {
        mVitesse = vitesse;
    }
    else
    {
        mVitesse = 1.0f;
    }
    
    resistance = Ogre::Math::Clamp(resistance, 0.0f, 1.0f);
    mResistance = resistance;
}

Arme::~Arme()
{

}

int Arme::getDegat() const
{
    return mDegat;
}

float Arme::getVitesse() const
{
    return mVitesse;
}

float Arme::getResistance() const
{
    return mResistance;
}

void Arme::decreaseResistance()
{
    mResistance -= 0.01f;

    if(mResistance < 0)
    {
        mResistance = 0;
    }
}

void Arme::setDegat(int degat)
{
    if (degat >= 0)
    {
        mDegat = degat;
    }
}

void Arme::setVitesse(float vitesse)
{
    if (vitesse > 0.0f)
    {
        mVitesse = vitesse;
    }
}

void Arme::setResistance(float resistance)
{
    resistance = Ogre::Math::Clamp(resistance, 0.0f, 1.0f);

    mResistance = resistance;
}

#ifdef _DEBUG
void Arme::afficheDebug(std::ostream& rOst) const 
{
	Item::afficheDebug(rOst);
	rOst << "Degats:" << mDegat << endl << "Vitesse:" << mVitesse << endl << "Resistance:" << mResistance*100 << "%" << endl << "-----------------------------------------------" << endl;
}
#endif

bool Arme::compare(Item const& rSecondeArme) const 
{
	/* D'après le RTTI on sait que l'item est une arme */

	Arme const& rSecArme = dynamic_cast<Arme const&>(rSecondeArme);

	return (Enchante::compare(rSecondeArme) &&
		mDegat == rSecArme.mDegat &&
		mResistance == rSecArme.mResistance &&
		mVitesse == rSecArme.mVitesse);
}
