#include <OGRE/Ogre.h>

#include "AppDemarrage.h"

#if OGRE_PLATFORM == PLATFORM_WIN32 || OGRE_PLATFORM == OGRE_PLATFORM_WIN32 //Windows x86

#define WIN32_LEAN_AND_MEAN //Désactive les fonctionnalités inutiles
#include "windows.h"

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)   //Main pour Windows

#else

int main(int argc, char **argv) //Main standard

#endif

{
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

    return EXIT_SUCCESS;
}