﻿#include "StdLibAndNewOperator.h"

#include <OgreException.h>
#include <OgrePlatform.h>

#include <fcntl.h>
#include <tchar.h>
#include <io.h>

#include "AppMain.h"
#include "IDMgr.h"
#include "ExceptionPerso.h"


/* Singletons */
IDMgr* IDMgr::mpsInstanceUnique = nullptr;
AppMain* AppMain::mpsInstanceUnique = nullptr;

#if OGRE_PLATFORM == OGRE_PLATFORM_WINRT || OGRE_PLATFORM == OGRE_PLATFORM_WIN32 //Windows x86

#define WIN32_LEAN_AND_MEAN //Désactive les fonctionnalités inutiles
#include "windows.h"

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)   //Main pour Windows

#else
int main(int argc, char **argv) //Main standard
#endif

{
#ifdef _DEBUG
	AllocConsole();
	*stdout = *_tfdopen(_open_osfhandle((intptr_t) GetStdHandle(STD_OUTPUT_HANDLE), _O_APPEND), _T("a"));

	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );	//Fuite mémoire
#endif

	AppMain *pApp = AppMain::getInstance();   //Le jeu

	/* On lance le jeu et on récupère les éventuelles exceptions levées pour les afficher */
	try
	{
		pApp->start();
		AppMain::destroy();
	}
	catch(Ogre::Exception& e)
	{
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32 || OGRE_PLATFORM == OGRE_PLATFORM_WINRT
		MessageBoxA(NULL, e.getFullDescription().c_str(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
		fprintf(stderr, "An exception has occurred: %s\n", e.getFullDescription().c_str());
#endif
	}
	catch(ExceptionPerso& e)	//Exception perso
	{
		e.what();
	}
	catch(std::exception& e)
	{
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32 || OGRE_PLATFORM == OGRE_PLATFORM_WINRT
		MessageBoxA(NULL, e.what(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
		fprintf(stderr, "An exception has occurred: %s\n", e.what());
#endif
	}

#ifdef _DEBUG
	FreeConsole();
#endif

	return EXIT_SUCCESS;
}