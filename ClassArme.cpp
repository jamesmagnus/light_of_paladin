#include "ClassArme.h"

#include <OgreMath.h>


using namespace std;

Arme::Arme(Ogre::SceneNode *pNode, int degat, float vitesse, float resistance, int prix, float poid, std::string const& nom, bool IsUnique, bool IsVisible): Item(pNode, prix, poid, nom, IsUnique, IsVisible)
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

/* Surcharge opérateurs externes */

/* == */
bool operator==(Arme const& item1, Arme const& item2)
{
	if (typeid(item1) == typeid(item2))
	{
		return item1.compare(item2);	//Comportement polymorphique
	} 
	else
	{
		return false;
	}
}

#ifdef _DEBUG
/* << */
std::ostream& operator<<(std::ostream& rOst, Arme const& obj)
{
	obj.afficheDebug(rOst);

	return rOst;
}
#endif
