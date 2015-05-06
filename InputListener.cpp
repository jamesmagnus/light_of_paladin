#include "enumerations.h"
#include "InputListener.h"
#include "CeguiMgr.h"

#include <OgreCamera.h>
#include <OgreLogManager.h>
#include <OgreRenderWindow.h>
#include <OIS/OISMouse.h>
#include <OIS/OISInputManager.h>

using namespace Ogre;

InputListener::InputListener(RenderWindow *pWindow, Camera *pCam, CeguiMgr *pCEGUI)
{
	assert(pWindow != nullptr && pCam != nullptr && pCEGUI != nullptr);

	mpWindow = pWindow;
	mpCamera = pCam;
	mpCEGUIMgr = pCEGUI;
	mCurrentEvent = FrameEvent();

	startOIS(); //Initialisation d'OIS
}

InputListener::~InputListener()
{
	WindowEventUtilities::removeWindowEventListener(mpWindow, this);    //On déréférence cet écouteur d'évènements
	windowClosing(mpWindow); //Appelée manuellement dans le destructeur si la fenêtre est fermée par une source externe
}

bool InputListener::frameRenderingQueued(FrameEvent const& evt)
{
	Vector3 deplacement = Vector3::ZERO;
	Real movement = evt.timeSinceLastFrame * VITESSE_TRANS_CAM;
	mCurrentEvent = evt;

	/* Si la fenêtre s'est fermée on coupe Ogre */
	if (mpWindow->isClosed())
	{
		return false;
	}

	if (mpInputManager == nullptr)
	{
		return false;
	}

	/* Mise à jour des périphériques d'entrée */
	mpMouse->capture();
	mpKeyBoard->capture();

	Vector3Move moving = dynamic_cast<KeyBoardEventListener*>(mpKeyBoard->getEventCallback())->getMove();

	switch (moving.x)
	{
	case EMove::BACK:
		deplacement.x += movement;
		break;

	case EMove::FORWARD:
		deplacement.x -= movement;
		break;
	}

	switch (moving.z)
	{
	case EMove::BACK:
		deplacement.z += movement;
		break;

	case EMove::FORWARD:
		deplacement.z -= movement;
	}

	/* Enfin on déplace la caméra */
	mpCamera->moveRelative(deplacement);

	return true;    //Ogre continue
}

void InputListener::startOIS()
{
	LogManager::getSingletonPtr()->logMessage("**** Init OIS ****");

	size_t windowHnd = 0;

	/* On récupère les infos sur la fenêtre depuis l'OS */
	mpWindow->getCustomAttribute("WINDOW", &windowHnd);

	/* On crée le gestionnaire */
	mpInputManager = OIS::InputManager::createInputSystem(windowHnd);

	/* On crée les objets relatifs à chaque périphérique */
	mpMouse = static_cast<OIS::Mouse*>(mpInputManager->createInputObject(OIS::OISMouse, true));
	mpKeyBoard = static_cast<OIS::Keyboard*>(mpInputManager->createInputObject(OIS::OISKeyboard, true));

	mpKeyBoard->setEventCallback(new KeyBoardEventListener(this, mpKeyBoard, mpCEGUIMgr));
	mpMouse->setEventCallback(new MouseEventListener(mpCamera, &mCurrentEvent, mpCEGUIMgr));

	windowResized(mpWindow);    //On appelle manuellement cette méthode une fois pour initialiser la taille de la fenêtre

	WindowEventUtilities::addWindowEventListener(mpWindow, this);   //On lie l'écouteur avec la fenêtre
}

void InputListener::windowResized(RenderWindow* rw)
{
	unsigned int width, height, depth;
	int left, top;

	/* On récupère les nouvelles dimensions/positions de la fenêtre */
	rw->getMetrics(width, height, depth, left, top);

	/* On récupère l'état de la souris */
	const OIS::MouseState &ms = mpMouse->getMouseState();

	/* On le met à jour avec les nouvelles valeurs */
	ms.width = width;
	ms.height = height;
}

bool InputListener::windowClosing(RenderWindow* rw)
{
	if (rw == mpWindow)  //Si la fenêtre fermée est bien la notre
	{
		clearInputListeners();
	}

	return false;
}

void InputListener::clearInputListeners()
{
	/* On test si le gestionnaire existe toujours. On détruit les objets du gestionnaire, puis le gestionnaire */
	if (mpInputManager != nullptr)  
	{
		if (mpKeyBoard != nullptr)
		{
			if (mpKeyBoard->getEventCallback() != nullptr)
			{
				delete mpKeyBoard->getEventCallback();
			}
			mpInputManager->destroyInputObject(mpKeyBoard);
			mpKeyBoard=nullptr;
		}


		if (mpMouse != nullptr)
		{
			if (mpMouse->getEventCallback() != nullptr)
			{
				delete mpMouse->getEventCallback();
			}
			mpInputManager->destroyInputObject(mpMouse);
			mpMouse = nullptr;
		}

		OIS::InputManager::destroyInputSystem(mpInputManager);
		mpInputManager = nullptr;
	}
}

KeyBoardEventListener::KeyBoardEventListener(InputListener *pListener, OIS::Keyboard const *pKeyBoard, CeguiMgr *pCeguiMgr)
{
	mpInputListener = pListener;
	mpKeyBoard = pKeyBoard;
	mpCEGUIMgr = pCeguiMgr;

	mActualMove.x = mActualMove.y = mActualMove.z = EMove::STOP;
}

KeyBoardEventListener::~KeyBoardEventListener()
{
}

bool KeyBoardEventListener::keyPressed(OIS::KeyEvent const& arg)
{
	mpCEGUIMgr->injectOISKeyEvent(true, arg);

	if (arg.key == OIS::KC_ESCAPE)
	{
		mpInputListener->clearInputListeners();
		return false;
	}

	if (arg.key == OIS::KC_F4 && mpKeyBoard->isModifierDown(OIS::Keyboard::Alt))
	{
		mpInputListener->clearInputListeners();
		return false;
	}

	switch (arg.key)
	{
	case OIS::KC_RIGHT: case OIS::KC_D:
		mActualMove.x = EMove::BACK ;
		break;

	case OIS::KC_LEFT: case OIS::KC_A:
		mActualMove.x = EMove::FORWARD;
		break;

	case OIS::KC_UP: case OIS::KC_W:
		mActualMove.z = EMove::FORWARD;
		break;

	case OIS::KC_DOWN: case OIS::KC_S:
		mActualMove.z = EMove::BACK;
		break;

	case OIS::KC_TAB:
		mpCEGUIMgr->shiftMode(!mpCEGUIMgr->shiftMode());
	}

	return true;
}

bool KeyBoardEventListener::keyReleased(OIS::KeyEvent const& arg)
{
	mpCEGUIMgr->injectOISKeyEvent(false, arg);

	switch (arg.key)
	{
	case OIS::KC_RIGHT: case OIS::KC_D: case OIS::KC_LEFT: case OIS::KC_A:
		mActualMove.x = EMove::STOP ;
		break;

	case OIS::KC_UP: case OIS::KC_W: case OIS::KC_DOWN: case OIS::KC_S:
		mActualMove.z = EMove::STOP;
		break;
	}

	return true;
}

Vector3Move const& KeyBoardEventListener::getMove() const
{
	return mActualMove;
}

MouseEventListener::MouseEventListener(Ogre::Camera *pCam, Ogre::FrameEvent const *pEventTime, CeguiMgr *pCEGUIMgr)
{
	mpCamera = pCam;
	mpEventTime = pEventTime;
	mpCEGUIMgr = pCEGUIMgr;
}

MouseEventListener::~MouseEventListener()
{

}

bool MouseEventListener::mousePressed(OIS::MouseEvent const& arg, OIS::MouseButtonID id)
{
	mpCEGUIMgr->injectOISMouseButton(true, id);

	return true;
}

bool MouseEventListener::mouseReleased(OIS::MouseEvent const& arg, OIS::MouseButtonID id)
{
	mpCEGUIMgr->injectOISMouseButton(false, id);

	return true;
}

bool MouseEventListener::mouseMoved(OIS::MouseEvent const& arg)
{
	/* On récupère l'état de la souris */
	const OIS::MouseState &mouseState = arg.state;

	mpCEGUIMgr->injectOISMouseRotation(static_cast<float>(mouseState.X.rel), static_cast<float>(mouseState.Y.rel), mpEventTime->timeSinceLastFrame);

	/* On calcule la rotation à partir des coordonnées relatives à la dernière position */
	Radian mRotationX = Degree(-mouseState.Y.rel * VITESSE_ROTATION_CAM);
	Radian mRotationY = Degree(-mouseState.X.rel * VITESSE_ROTATION_CAM);

	mpCamera->yaw(mRotationY);
	mpCamera->pitch(mRotationX);

	return true;
}
