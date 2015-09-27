#include "StdLibAndNewOperator.h"
#include <string>
#include <iostream>

#include <OgrePlatform.h>

#if OGRE_PLATFORM == OGRE_PLATFORM_WINRT || OGRE_PLATFORM == OGRE_PLATFORM_WIN32 //Windows x86

#include "windows.h"

#endif

#include "ExceptionPerso.h"

using namespace std;

ExceptionPerso::ExceptionPerso(const char* const & message, ENiveau niv) throw(): exception(message)
{
    mNiveau = niv;
}


ExceptionPerso::~ExceptionPerso() throw()
{

}

ENiveau ExceptionPerso::getLvl() const throw()
{
    return mNiveau;
}

const char* ExceptionPerso::what() const throw()
{
    string lvl;

    switch (getLvl())
    {
    case ERREUR:
        lvl = "An exception has occurred! - ERROR";
        break;

    case INFO:
        lvl = "An exception has occurred! - INFO";
        break;

    case FATAL:
        lvl = "An exception has occurred! - FATAL";
        break;

    default:
        lvl = "An exception has occurred! - default";
        break;
    }

#if OGRE_PLATFORM == OGRE_PLATFORM_WINRT || OGRE_PLATFORM == OGRE_PLATFORM_WIN32

    /* On utilise la fenêtre message d'erreur classique sous Windows */
    MessageBoxA(NULL, std::exception::what(), lvl.c_str(), MB_OK | MB_ICONERROR | MB_TASKMODAL | MB_SETFOREGROUND);

#else
    /* La sortie d'erreurs standard sinon */
    fprintf(stderr, "%s %s\n", lvl.c_str(), std::exception::what());

#endif

    return (lvl + std::exception::what()).c_str();
}
