#include <OGRE/Ogre.h>

#include <conio.h>
#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <fcntl.h>
#include <signal.h>
#include <io.h>
#include <tchar.h>

#include "AppDemarrage.h"
#include "GestionnaireID.h"

/* Singletons */
GestionnaireID* GestionnaireID::mpInstanceUnique = nullptr;

#if OGRE_PLATFORM == PLATFORM_WIN32 || OGRE_PLATFORM == OGRE_PLATFORM_WIN32 //Windows x86

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
#endif

    AppDemarrage app;   //Le jeu

    /* On lance le jeu et on récupère les éventuelles exceptions levées pour les afficher */
    try
    {
        app.start();
    }
    catch(Ogre::Exception& e)
    {

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32

        MessageBoxA(NULL, e.getFullDescription().c_str(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);

#else

        fprintf(stderr, "An exception has occurred: %s\n", e.getFullDescription().c_str());

#endif

    }
    catch(std::exception& e)	//Exception perso
    {
        e.what();
    }

#ifdef _DEBUG
	FreeConsole();
#endif

    return EXIT_SUCCESS;
}