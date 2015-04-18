#pragma once

#include "Structures.h"

#include <OgrePrerequisites.h>
#include <OgreMath.h>
#include <OgreFrameListener.h>
#include <OgreWindowEventUtilities.h>

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

/* Classe pour g�rer les entr�es utilisateurs */
/* H�rite de Ogre::FrameListener et Ogre::WindowEventListener */
class InputListener: public Ogre::FrameListener, Ogre::WindowEventListener
{
public:

    /* Constructeur */
    /* pWindow, pointeur sur la fen�tre de rendue de Ogre */
    /* pCam, pointeur sur la cam�ra */
    InputListener(Ogre::RenderWindow *pWindow, Ogre::Camera *pCam, CeguiMgr *pCEGUI);

    /* Destructeur */
    virtual ~InputListener();

    /* S'ex�cute pendant le rendu */
    /* Renvoie false si le programme doit s'arr�ter */
    bool frameRenderingQueued(Ogre::FrameEvent const& evt) override;

    /* Initialise OIS, appel�e par le constructeur */
    void startOIS();

    /* Appel�e lors du redimensionnement de la fen�tre */
    virtual void windowResized(Ogre::RenderWindow* rw) override;

    /* Appel�e lors de la fermeture de la fen�tre */
    virtual bool windowClosing(Ogre::RenderWindow* rw) override;

	/* D�truit les �couteurs de p�riph�riques d'OIS et entraine le retour de false au prochain appel de frameRenderingQueued() */
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

	/* Callback pour les �v�nements du clavier */
	virtual bool keyPressed(OIS::KeyEvent const& arg) override;
	virtual bool keyReleased(OIS::KeyEvent const& arg) override;

	/* R�cup�re la structure indiquant sur quels axes un d�placement est en cours */
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

	/* Callback pour les �v�nements de la souris */
	virtual bool mousePressed(OIS::MouseEvent const& arg, OIS::MouseButtonID id) override;
	virtual bool mouseReleased(OIS::MouseEvent const& arg, OIS::MouseButtonID id) override;
	virtual bool mouseMoved(OIS::MouseEvent const& arg);
};