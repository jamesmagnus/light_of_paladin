#include <cstdio>
#include <cstdlib>

#include "ClassItem.h"
#include "ClassArme.h"


using namespace std;

Arme::Arme(unsigned long id, Ogre::SceneNode *pNode, int degat, float vitesse, float resistance, int prix, float poid, std::string nom, bool IsUnique, bool IsVisible): Item(id, pNode, prix, poid, nom, IsUnique, IsVisible)
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

Arme::Arme(Arme const& original):Item(original)
{
    mDegat = original.mDegat;
    mVitesse = original.mVitesse;
    mResistance = original.mResistance;
}

Arme& Arme::operator=(Arme const& original)
{
    if (this != &original)
    {
        mID = original.mID;
        mDegat = original.mDegat;
        mNom = original.mNom;
        mPoid = original.mPoid;
        mPrix = original.mPrix;
        mResistance = original.mResistance;
        mVitesse = original.mVitesse;
    }

    return *this;
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

bool Arme::canUse(Personnage *pJoueur) const
{
    // Truc a faire
    return true;
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
