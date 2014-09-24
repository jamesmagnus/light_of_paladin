#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

#include "ClassItem.h"
#include "ClassInventaire.h"

using namespace std;

Inventaire::Inventaire(int max)
{
    mNb = 0;
    mMax = max;
    mPoidTotal = 0.0f;
}

Inventaire::~Inventaire()
{
    mStuff.clear();
    mNb = mMax = 0;
    mPoidTotal = 0.0f;
}

int Inventaire::getNB() const
{
    return mNb;
}

int Inventaire::getMax() const
{
    return mMax;
}

bool Inventaire::setMax(int newMax)
{
    if (newMax >= mNb)
    {
        mMax = newMax;

        return true;
    } 
    else
    {
        return false;   //Impossible de modifier le max, inventaire trop plein
    }
}

unsigned long Inventaire::ajout(Item& rItem)
{
    if(mNb >= mMax)
    {
        return 0;
    }
    else
    {
        mStuff.insert(make_pair(rItem.getID(), &rItem));
        mNb++;
        mPoidTotal += rItem.getPoid();

        return rItem.getID();
    }
}

unsigned long Inventaire::ajout(Item* const pItem)
{
    if(mNb >= mMax)
    {
        return 0;
    }
    else
    {
        mStuff.insert(make_pair(pItem->getID(), pItem));
        mNb++;
        mPoidTotal += pItem->getPoid();

        return pItem->getID();
    }
}

bool Inventaire::suppr(Item* const pItem)
{
    if(existe(pItem))
    {
        mStuff.erase(mStuff.find(pItem->getID()));  //Supprime le premier élément correspondant seulement

        mNb--;

        mPoidTotal -= pItem->getPoid();

        if(mPoidTotal < 0.0f)
        {
            mPoidTotal = 0.0f;
        }

        return true;
    }
    else
    {
        return false;   //Item inexistant
    }
}

bool Inventaire::suppr(unsigned long ID)
{
    if (existe(ID))
    {
        mStuff.erase(mStuff.find(ID));  //Supprime le premier élément correspondant seulement

        mPoidTotal -= getItem(ID)->getPoid();

        if(mPoidTotal < 0.0f)
        {
            mPoidTotal = 0.0f;
        }

        mNb--;

        return true;
    }
    else
    {
        return false;   //Item inexistant
    }    
}

bool Inventaire::clear()
{
    if (mNb != 0)
    {
        mStuff.clear();
        mNb = 0;
        mPoidTotal = 0.0f;

        return false;
    } 
    else
    {
        return true;    //Inventaire déjà vide
    }
}

Item* Inventaire::getItem(unsigned long ID) const
{
    if (existe(ID))
    {
        return mStuff.find(ID)->second;
    } 
    else
    {
        return nullptr;
    }
}

bool Inventaire::existe(unsigned long ID) const
{
    return mStuff.find(ID) != mStuff.end();
}

bool Inventaire::existe(Item* pItem) const
{
    return mStuff.find(pItem->getID()) != mStuff.end();
}

float Inventaire::getPoidTotal() const
{
    return mPoidTotal;
}


/* --------------------------- */
/* Surcharge des opérateurs unaires */

void Inventaire::operator+=(Inventaire const& inv)
{
    mNb += inv.getNB();
    mMax = mNb;
    mPoidTotal += inv.getPoidTotal();

    multimap<unsigned long, Item*>::const_iterator it;

    for (it = inv.mStuff.cbegin(); it != inv.mStuff.cend(); it++)
    {
        mStuff.insert(make_pair(it->first, it->second));
    }
}


/* -------------------------- */
/* Surcharge des opérateurs binaires */

Inventaire operator+(Inventaire const& inv1, Inventaire const& inv2)
{
    Inventaire temp(0);

    temp += inv1;
    temp += inv2;

    return temp;
}
