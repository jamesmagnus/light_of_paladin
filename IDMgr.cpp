#include "IDMgr.h"
#include "ExceptionPerso.h"

#include <ctime>
#include <climits>

using namespace boost;

IDMgr::IDMgr()
{
	mEngine.seed(static_cast<uint32_t>(time(nullptr)));	//Init

	mpLongDistrib = new boost::random::uniform_int_distribution<unsigned long>(1, ULONG_MAX);	//Distribution uniforme entre 1 et max
}

IDMgr::~IDMgr()
{
	if(mpsInstanceUnique != nullptr)
	{
			delete mpsInstanceUnique->mpLongDistrib;
			mpsInstanceUnique->mpLongDistrib = nullptr;
	}

		delete mpsInstanceUnique;
		mpsInstanceUnique = nullptr;
}

IDMgr* IDMgr::getInstance()
{
	if (mpsInstanceUnique == nullptr)
	{
		mpsInstanceUnique = new IDMgr();
	} 

	return mpsInstanceUnique;
}

void IDMgr::destroy()
{
	delete mpsInstanceUnique;
}

unsigned long IDMgr::newID()
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

bool IDMgr::isMoreIDFree() const
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

bool IDMgr::memoriseID(std::vector<unsigned long> const& liste)
{
	for (std::vector<unsigned long>::const_iterator it=liste.begin(); it != liste.end(); ++it)
	{
		auto retval = mIDExistants.insert(*it);
		assert(retval.second);
	}

	return isMoreIDFree();
}

bool IDMgr::IsIDPresent(unsigned long id) const
{
	return mIDExistants.find(id) != mIDExistants.end();
}
