#include "GestionnaireID.h"
#include "ExceptionPerso.h"

#include <ctime>
#include <climits>

using namespace boost;

GestionnaireID::GestionnaireID()
{
    mEngine.seed(static_cast<uint32_t>(time(nullptr)));	//Init

    mpLongDistrib = new boost::random::uniform_int_distribution<unsigned long>(1, ULONG_MAX);	//Distribution uniforme entre 1 et max
}

GestionnaireID::~GestionnaireID()
{
}

GestionnaireID* GestionnaireID::getInstance()
{
	if (mpInstanceUnique == nullptr)
	{
		mpInstanceUnique = new GestionnaireID();
	} 
	
	return mpInstanceUnique;
}

void GestionnaireID::destroy()
{
	if(mpInstanceUnique != nullptr)
	{
		if(mpInstanceUnique->mpLongDistrib != nullptr)
		{
			delete mpInstanceUnique->mpLongDistrib;
			mpInstanceUnique->mpLongDistrib = nullptr;
		}

		delete mpInstanceUnique;
		mpInstanceUnique = nullptr;
	}
}

unsigned long GestionnaireID::newID()
{
    unsigned long id=0;
    std::pair<std::set<unsigned long>::iterator, bool> retPair;
    retPair.second = false;

    if (!isMoreIDFree())
    {
        throw ExceptionPerso("Plus d'IDs disponibles", ERREUR);	//S'il n'y a plus d'id on lève une exception
    }

    do 
    {
        id = mpLongDistrib->operator()(mEngine);	//On choisit un id au hasard
        retPair = mIDExistants.insert(id);	//On tente de le mettre dans le set

    } while (!retPair.second);	//Si on a pu le mettre c'est qu'il n'était pas utilisé

    return id;
}

bool GestionnaireID::isMoreIDFree() const
{
    if (mIDExistants.size() >= ULONG_MAX)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool GestionnaireID::memoriseID(std::vector<unsigned long> liste)
{
    std::vector<unsigned long>::iterator it;

    for (it=liste.begin(); it != liste.end(); ++it)
    {
        auto retval = mIDExistants.insert(*it);
		assert(retval.second);
    }

    return isMoreIDFree();
}

bool GestionnaireID::IsIDPresent(unsigned long id) const
{
    return mIDExistants.find(id) != mIDExistants.end();
}
