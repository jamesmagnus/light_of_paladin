#include "InputListener.h"

#include <OgreCamera.h>
#include <OgreLogManager.h>
#include <OgreRenderWindow.h>
#include <OIS/OISMouse.h>
#include <OIS/OISKeyboard.h>
#include <OIS//OISInputManager.h>

using namespace Ogre;

InputListener::InputListener(RenderWindow *pWindow, Camera *pCam)
{
	mpWindow = pWindow;
	mpCamera = pCam;

	mToucheAppuyee = false;
	mVitesse = 600.0;
	mVitesseRotation = 0.25;

	startOIS(); //Initialisation d'OIS
}

InputListener::~InputListener()
{
	WindowEventUtilities::removeWindowEventListener(mpWindow, this);    //On déréférence cet écouteur d'évènements
	windowClosed(mpWindow); //Appelée manuellement dans le destructeur si on ferme sans utiliser la croix
}

bool InputListener::frameRenderingQueued(const FrameEvent& evt)
{
	/* Si la fenêtre s'est fermée on coupe Ogre */
	if (mpWindow->isClosed())
	{
		return false;
	}

	/* Mise à jour des périphériques d'entrée */
	mpMouse->capture();
	mpKeyBoard->capture();

	/* On arrête Ogre si ECHAP est enfoncée */
	if (mpKeyBoard->isKeyDown(OIS::KC_ESCAPE))
	{
		return false;
	}

	/* De même pour alt+F4 */
	if (mpKeyBoard->isKeyDown(OIS::KC_F4) && mpKeyBoard->isModifierDown(OIS::Keyboard::Modifier::Alt))
	{
		return false;
	}

	Ogre::Vector3 deplacement = Ogre::Vector3::ZERO;    //Vecteur de déplacement
	mMouvement = mVitesse * evt.timeSinceLastFrame; //Valeur du déplacement en fonction des FPS

	/* La touche A d'un clavier QWERTY correspond au Q sur un AZERTY */
	if(mpKeyBoard->isKeyDown(OIS::KC_LEFT) || mpKeyBoard->isKeyDown(OIS::KC_A))
	{
		deplacement.x -= mMouvement;
	}
	if(mpKeyBoard->isKeyDown(OIS::KC_RIGHT) || mpKeyBoard->isKeyDown(OIS::KC_D))
	{
		deplacement.x += mMouvement;
	}
	if(mpKeyBoard->isKeyDown(OIS::KC_UP) || mpKeyBoard->isKeyDown(OIS::KC_W)) // W correspond au Z du AZERTY
	{
		deplacement.z -= mMouvement;
	}
	if(mpKeyBoard->isKeyDown(OIS::KC_DOWN) || mpKeyBoard->isKeyDown(OIS::KC_S))
	{
		deplacement.z += mMouvement;
	}

	/* On récupère l'état de la souris */
	const OIS::MouseState &mouseState = mpMouse->getMouseState();

	/* On calcule la rotation à partir des coordonnées relatives à la dernière position */
	mRotationX = Degree(-mouseState.Y.rel * mVitesseRotation);
	mRotationY = Degree(-mouseState.X.rel * mVitesseRotation);

	/* Enfin on déplace la caméra */
	mpCamera->yaw(mRotationY);
	mpCamera->pitch(mRotationX);
	mpCamera->moveRelative(deplacement);

	return true;    //Ogre continue
}

void InputListener::startOIS()
{
	LogManager::getSingletonPtr()->logMessage("**** Init OIS ****");

	OIS::ParamList pl;
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;

	/* On récupère les infos sur la fenêtre depuis l'OS */
	mpWindow->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

	/* On crée le gestionnaire */
	mpInputManager = OIS::InputManager::createInputSystem(pl);

	/* On crée les objets relatifs à chaque périphérique */
	mpMouse = static_cast<OIS::Mouse*>(mpInputManager->createInputObject(OIS::OISMouse, false));
	mpKeyBoard = static_cast<OIS::Keyboard*>(mpInputManager->createInputObject(OIS::OISKeyboard, false));

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

void InputListener::windowClosed(RenderWindow* rw)
{
	if (rw == mpWindow)  //Si la fenêtre fermée est bien la notre
	{
		/* On test si le gestionnaire existe toujours. On détruit les objets du gestionnaire, puis le gestionnaire */
		if (mpInputManager != nullptr)  
		{
			mpInputManager->destroyInputObject(mpMouse);
			mpInputManager->destroyInputObject(mpKeyBoard);

			OIS::InputManager::destroyInputSystem(mpInputManager);

			mpInputManager = nullptr;
		}
	}
}