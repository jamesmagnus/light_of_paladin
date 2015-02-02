#include <assert.h>

#include "ClassInventaire.h"
#include "ClassItem.h"

using namespace std;

Inventaire::Inventaire(int max)
{
	mNb = 0;
	mMax = max;
	mPoidTotal = 0.0f;
}

Inventaire::Inventaire(Inventaire const& rOriginal)
{
	mMax = rOriginal.mMax;
	mNb = 0;
	mPoidTotal = 0.0f;

	auto it = rOriginal.mStuff.cbegin();

	for (; it != rOriginal.mStuff.cend(); ++it)
	{
		ajout(it->second->clone());
	}

	assert(mNb <= mMax && mNb == mStuff.size());
}


Inventaire& Inventaire::operator=(Inventaire const& rOriginal)
{
	if(this != &rOriginal)
	{
		mNb = 0;
		mMax = rOriginal.mMax;
		mPoidTotal = 0.0f;
		
		auto it = rOriginal.mStuff.cbegin();

		for (; it != rOriginal.mStuff.cend(); ++it)
		{
			ajout(it->second->clone());
		}

		assert(mNb <= mMax && mNb == mStuff.size());
	}

	return *this;
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

#ifdef _DEBUG
void Inventaire::afficheDebugInv(ostream& rOst) const
{
	rOst << "Type: Inventaire" << endl << "Occupation: " << mNb << " sur " << mMax << endl << "Poid total du contenu: " << mPoidTotal << endl << "-----------------------------------------------" << endl;
}
#endif

/* --------------------------- */
/* Surcharge des opérateurs internes */

Inventaire& Inventaire::operator+=(Inventaire const& inv)
{
	mNb += inv.getNB();

	if(mMax < mNb)
	{
		mMax = mNb;
	}

	mPoidTotal += inv.getPoidTotal();

	multimap<unsigned long, Item*>::const_iterator it;

	for (it = inv.mStuff.cbegin(); it != inv.mStuff.cend(); ++it)
	{
		mStuff.insert(make_pair(it->first, it->second));
	}

	return *this;
}


/* -------------------------- */
/* Surcharge des opérateurs externes */

Inventaire operator+(Inventaire const& inv1, Inventaire const& inv2)
{
	Inventaire temp(inv1);

	temp += inv2;

	return temp;
}

bool operator==(Inventaire const& inv1, Inventaire const& inv2)
{
	if(inv1.mNb != inv2.mNb)
	{
		return false;
	}

	auto it2 = inv2.mStuff.cbegin();
	auto it1 = inv1.mStuff.cbegin();
	bool identique=false;

	for(; it1 != inv1.mStuff.cend(); ++it1)
	{
		identique=false;

		for (; it2 != inv2.mStuff.cend(); ++it2)
		{
			if( *(it1->second) == *(it2->second) )
			{
				identique=true;
				break;
			}
		}

		if (!identique)
		{
			return false;
		}

		it2 = inv2.mStuff.cbegin();
	}

	it2 = inv2.mStuff.cbegin();
	it1 = inv1.mStuff.cbegin();
	identique=false;

	for(; it2 != inv2.mStuff.cend(); ++it2)
	{
		identique=false;

		for (; it1 != inv1.mStuff.cend(); ++it1)
		{
			if( *(it1->second) == *(it2->second) )
			{
				identique=true;
				break;
			}
		}

		if (!identique)
		{
			return false;
		}

		it1 = inv1.mStuff.cbegin();
	}

	return true;
}

bool operator<(Inventaire const& inv1, Inventaire const& inv2)
{
	return inv1.getNB() < inv2.getNB();
}

#ifdef _DEBUG
ostream& operator<<(ostream& rOst, Inventaire const& inv)
{
	inv.afficheDebugInv(rOst);

	return rOst;
}
#endif