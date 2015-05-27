#include "FMODSoundMgr.h"
#include "ExceptionPerso.h"

#include <fmod_errors.h>
#include <string>

using namespace FMOD;

FMODSoundMgr::FMODSoundMgr(): Ogre::FrameListener()
{
	pSys = nullptr;

	FMOD_RESULT res = System_Create(&pSys);

	if (res != FMOD_OK)
	{
		throw ExceptionPerso((std::string("Erreur lors de la création du système FMOD: ") + FMOD_ErrorString(res)).c_str(), FATAL);
	}

	res = pSys->init(1024, FMOD_INIT_3D_RIGHTHANDED, nullptr);

	if (res != FMOD_OK)
	{
		throw ExceptionPerso((std::string("Erreur lors de l'initialisation du système FMOD: ") + FMOD_ErrorString(res)).c_str(), FATAL);
	}
}


FMODSoundMgr::~FMODSoundMgr()
{
}

bool FMODSoundMgr::frameStarted(Ogre::FrameEvent const& evt)
{
	pSys->update();

	return true;
}

bool FMODSoundMgr::loadSound(std::string const& fichier, std::string const& nom)
{
	Sound *ps;
	pSys->createStream(fichier.c_str(), 0, nullptr, &ps);

	std::pair<std::map<std::string, Sound*>::iterator, bool> ret = mSoundPtrMap.insert(make_pair(nom, ps));

	return ret.second;
}

void FMODSoundMgr::playLoadedSound(std::string const& nom, bool const paused) const
{
	Sound *ps = mSoundPtrMap.at(nom);

	if (ps != nullptr)
	{
		pSys->playSound(ps, nullptr, paused, nullptr);
	}
	else
	{
		throw ExceptionPerso((std::string("Impossible de lire ") + nom).c_str(), ERREUR);
	}
}
