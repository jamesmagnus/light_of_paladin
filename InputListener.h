#pragma once

#include <OgrePrerequisites.h>
#include <OgreMath.h>
#include <OgreFrameListener.h>
#include <OgreWindowEventUtilities.h>

class CeguiMgr;

namespace Ogre
{
	class RenderWindow;
	class Camera;
}

namespace OIS
{
	class InputManager;
	class Mouse;
	class Keyboard;
}

/* Classe pour gérer les entrées utilisateurs */
/* Hérite de Ogre::FrameListener et Ogre::WindowEventListener */
class InputListener: public Ogre::FrameListener, Ogre::WindowEventListener
{
public:

    /* Constructeur */
    /* pWindow, pointeur sur la fenêtre de rendue de Ogre */
    /* pCam, pointeur sur la caméra */
    InputListener(Ogre::RenderWindow *pWindow, Ogre::Camera *pCam, CeguiMgr *pCEGUI);

    /* Destructeur */
    virtual ~InputListener();

    /* S'exécute pendant le rendu */
    /* Renvoie false si le programme doit s'arrêter */
    bool frameRenderingQueued(const Ogre::FrameEvent& evt) override;

    /* Initialise OIS, appelée par le constructeur */
    void startOIS();

    /* Appelée lors du redimensionnement de la fenêtre */
    virtual void windowResized(Ogre::RenderWindow* rw) override;

    /* Appelée lors de la fermeture de la fenêtre */
    virtual void windowClosed(Ogre::RenderWindow* rw) override;

protected:
    Ogre::RenderWindow *mpWindow;
    Ogre::Camera *mpCamera;

    OIS::InputManager *mpInputManager;
    OIS::Mouse *mpMouse;
    OIS::Keyboard *mpKeyBoard;

    CeguiMgr *mpCEGUIMgr;

    Ogre::Real mMouvement;
    Ogre::Real mVitesse;
    Ogre::Real mVitesseRotation;

    Ogre::Radian mRotationX;
    Ogre::Radian mRotationY;
};