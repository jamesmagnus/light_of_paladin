#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

#include "ClassItem.h"

using namespace std;

Item::Item(unsigned long id, Ogre::SceneNode *pNode, int prix, float poid, string nom, bool IsUnique, bool IsVisible): Affichable(pNode, IsVisible)
{
    mID = id;

    if (prix >= 0)
    {
        mPrix = prix;
    } 
    else
    {
        mPrix = 0;
    }

    if (poid >= 0.0f)
    {
        mPoid = poid;
    } 
    else
    {
        mPoid = 1.0f;
    }

    mNom = nom;
    mIsUnique = IsUnique;
}

Item::~Item()
{
    mID = 0;
    mPrix = 0;
    mPoid = 0.0f;
}

unsigned long Item::getID() const 
{
    return mID;
}

int Item::getPrix() const
{
    return mPrix;
}

float Item::getPoid() const 
{
    return mPoid;
}

string Item::getNom() const
{
    return mNom;
}

void Item::setPrix(int prix)
{
    if (prix >= 0)
    {
        mPrix = prix;
    }
}

void Item::setPoid(float poid)
{
    if (poid >= 0.0f)
    {
        mPoid = poid;
    }
}

void Item::setNom(std::string nom)
{
    if (nom.length() > 0)
    {
        mNom = nom;
    }
}

void Item::setIsUnique(bool IsUnique)
{
    mIsUnique = IsUnique;
}
