#include "StdLibAndNewOperator.h"
#include "ClassConsommable.h"
#include "ExceptionPerso.h"

using namespace std;

Consommable::Consommable(Ogre::SceneNode *pNode, int prix, float poid, std::string const& nom, bool IsUnique, bool IsVisible):Item(pNode, prix, poid, nom, IsUnique, IsVisible)
{
	mNombre = 1;
}

Consommable::~Consommable()
{

}

unsigned int Consommable::getNombre() const
{
	return mNombre;
}

void Consommable::addObjet()
{
	mNombre++;
}

void Consommable::addObjet(unsigned int nbr)
{
	mNombre += nbr;
}

bool Consommable::supprObjet()
{
	mNombre--;

	if (mNombre > 0)
	{
		return true;
	} 
	else // Il n'y a plus d'objet
	{
		delete this;
		return false;
	}
}

bool Consommable::supprObjet(unsigned int nbr)
{
	if (mNombre - nbr >= 0)
	{
		mNombre -= nbr;
	}
	else
	{
		throw ExceptionPerso("Pas assez d'objet", ENiveau::INFO); 
	}

	if (mNombre > 0)
	{
		return true;
	} 
	else
	{
		delete this;
		return false;
	}
}