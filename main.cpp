#include <OgreException.h>
#include <OgrePlatform.h>

#include <stdlib.h>
#include <crtdbg.h>
#include <fcntl.h>
#include <tchar.h>
#include <io.h>

#include "AppMain.h"
#include "GestionnaireID.h"
#include "ExceptionPerso.h"


/* Singletons */
GestionnaireID* GestionnaireID::mpInstanceUnique = nullptr;

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

	// Flush all denormal/subnormal numbers (2^-1074 to 2^-1022) to zero.
	// Typically operations on denormals are very slow, up to 100 times slower than normal numbers.
	_MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);

	AppMain app;   //Le jeu

	/* On lance le jeu et on récupère les éventuelles exceptions levées pour les afficher */
	try
	{
		app.start();
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