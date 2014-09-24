#include "ClassArmure.h"

using namespace std;

Armure::Armure(unsigned long id, Ogre::SceneNode *pNode, int prix, float poid, std::string nom, bool IsUnique, bool IsVisible, int pointProtection, float etat): Item(id, pNode, prix, poid, nom, IsUnique, IsVisible)
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
