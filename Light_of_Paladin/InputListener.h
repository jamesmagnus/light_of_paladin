#pragma once

#include "Structures.h"

#include <OgrePrerequisites.h>
#include <OgreMath.h>
#include <OgreFrameListener.h>
#include <OgreWindowEventUtilities.h>

#include <boost/core/noncopyable.hpp>

#include <OIS/OISKeyboard.h>
#include <OIS/OISMouse.h>

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
/* Classe finale, non dérivable */
/* Sémantique d'entité, hérite de boost::noncopyable */
class InputListener: public Ogre::FrameListener, Ogre::WindowEventListener, private boost::noncopyable
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
    bool frameStarted(Ogre::FrameEvent const& evt) override;

    /* Initialise OIS, appelée par le constructeur */
    void startOIS();

    /* Appelée lors du redimensionnement de la fenêtre */
    virtual void windowResized(Ogre::RenderWindow* rw) override;

    /* Appelée lors de la fermeture de la fenêtre */
    virtual bool windowClosing(Ogre::RenderWindow* rw) override;

	/* Détruit les écouteurs de périphériques d'OIS et entraine le retour de false au prochain appel de frameRenderingQueued() */
	void clearInputListeners();

protected:
    Ogre::RenderWindow *mpWindow;
    Ogre::Camera *mpCamera;

    OIS::InputManager *mpInputManager;
    OIS::Mouse *mpMouse;
    OIS::Keyboard *mpKeyBoard;

    CeguiMgr *mpCEGUIMgr;

    Ogre::FrameEvent mCurrentEvent;
	Ogre::Radian mRotationX;
	Ogre::Radian mRotationY;
};

class KeyBoardEventListener: public OIS::KeyListener
{
private:
	InputListener *mpInputListener;
	OIS::Keyboard const *mpKeyBoard;
	Vector3Move mActualMove;
	Ogre::Camera *mpCamera;
	CeguiMgr *mpCEGUIMgr;

public:
	/* Constructeur */
	KeyBoardEventListener(InputListener *pListener, OIS::Keyboard const *pKeyBoard, CeguiMgr *pCeguiMgr);

	/* Destructeur */
	~KeyBoardEventListener();

	/* Callback pour les événements du clavier */
	virtual bool keyPressed(OIS::KeyEvent const& arg) override;
	virtual bool keyReleased(OIS::KeyEvent const& arg) override;

	/* Récupère la structure indiquant sur quels axes un déplacement est en cours */
	Vector3Move const& getMove() const; 
};

class MouseEventListener: public OIS::MouseListener
{
private:
	Ogre::Camera *mpCamera;
	Ogre::FrameEvent const *mpEventTime;
	CeguiMgr *mpCEGUIMgr;

public:
	/* Constructeur */
	MouseEventListener(Ogre::Camera *pCam, Ogre::FrameEvent const *pEventTime, CeguiMgr *pCEGUIMgr);

	/* Destructeur */
	~MouseEventListener();

	/* Callback pour les événements de la souris */
	virtual bool mousePressed(OIS::MouseEvent const& arg, OIS::MouseButtonID id) override;
	virtual bool mouseReleased(OIS::MouseEvent const& arg, OIS::MouseButtonID id) override;
	virtual bool mouseMoved(OIS::MouseEvent const& arg);
};