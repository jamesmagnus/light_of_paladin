#include "GestionnaireID.h"
#include "ExceptionPerso.h"

#include <ctime>
#include <set>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>

using namespace boost;

GestionnaireID::GestionnaireID(const unsigned int maxID): mIDMax(maxID)
{
    mEngine.seed(static_cast<uint32_t>(time(nullptr)));

    mpLongDistrib = new boost::random::uniform_int_distribution<unsigned long>(1, mIDMax+1);
}


GestionnaireID::~GestionnaireID()
{
    if (mpLongDistrib != nullptr)
    {
        delete mpLongDistrib;
        mpLongDistrib = nullptr;
    }
}

unsigned long GestionnaireID::newID()
{
    unsigned long id=0;
    std::pair<std::set<unsigned long>::iterator, bool> retPair;
    retPair.second = false;

    if (!isMoreIDFree())
    {
        throw ExceptionPerso("Plus d'IDs disponibles", ERREUR);
    }

    do 
    {
        id = mpLongDistrib->operator()(mEngine);
        retPair = mIDExistants.insert(id);

    } while (!retPair.second);

    return id;
}

bool GestionnaireID::isMoreIDFree() const
{
    if (mIDExistants.size() < mIDMax)
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

    for (it=liste.begin(); it != liste.end(); it++)
    {
        mIDExistants.insert(*it);
    }

    return isMoreIDFree();
}

bool GestionnaireID::IsIDPresent(unsigned long id) const
{
    return mIDExistants.find(id) != mIDExistants.end();
}