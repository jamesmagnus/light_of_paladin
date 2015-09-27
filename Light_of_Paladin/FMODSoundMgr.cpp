#include "StdLibAndNewOperator.h"
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

bool FMODSoundMgr::frameRenderingQueued(Ogre::FrameEvent const& evt)
{
	pSys->update();

	return true;
}

bool FMODSoundMgr::loadSound(std::string const& fichier, std::string const& nom)
{
	Sound *pS;

	pSys->createStream(fichier.c_str(), 0, nullptr, &pS);

	std::pair<std::map<std::string, std::pair<Sound*, Channel*>>::iterator, bool> ret = mSoundPtrMap.insert(std::make_pair(nom, std::make_pair(pS, nullptr)));

	return ret.second;
}

void FMODSoundMgr::playLoadedSound(std::string const& nom, bool const paused)
{
	try
	{
		Sound *pS = mSoundPtrMap.at(nom).first;
		pSys->playSound(pS, nullptr, paused, &mSoundPtrMap.at(nom).second);
	}
	catch(...)
	{
		throw ExceptionPerso((std::string("Impossible de lire ") + nom).c_str(), ERREUR);
	}
}

bool FMODSoundMgr::stopSound(std::string const& nom) const
{
	try
	{
		Sound *pS = mSoundPtrMap.at(nom).first;
		Channel *pC = mSoundPtrMap.at(nom).second;

		bool ret;
		pC->isPlaying(&ret);

		pC->stop();

		return ret;
	}
	catch(...)
	{
		throw ExceptionPerso((std::string("Impossible de lire ") + nom).c_str(), ERREUR);
	}
}
