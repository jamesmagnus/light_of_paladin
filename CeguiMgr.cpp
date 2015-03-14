#include "CeguiMgr.h"

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>


CeguiMgr::CeguiMgr()
{
	mpRenderer = &CEGUI::OgreRenderer::bootstrapSystem();

	CEGUI::Font::setDefaultResourceGroup("Fonts");
	CEGUI::Scheme::setDefaultResourceGroup("Schemes");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
	CEGUI::WindowManager::setDefaultResourceGroup("Layouts");

	CEGUI::SchemeManager::getSingletonPtr()->createFromFile("TaharezLook.scheme");
	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");

	CEGUI::Window* myRoot = CEGUI::WindowManager::getSingleton().createWindow( "DefaultWindow", "_MasterRoot" );
	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow( myRoot );

	CEGUI::Window *myImageWindow = CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/StaticImage","PrettyWindow" );
	myImageWindow->setPosition(CEGUI::UVector2(CEGUI::UDim(0.5,0),CEGUI::UDim(0.5,0)));
	myImageWindow->setSize(CEGUI::USize(CEGUI::UDim(0,150), CEGUI::UDim(0,100)));
	myImageWindow->setProperty("Image","TaharezLook/ButtonLeftNormal");
	CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->addChild(myImageWindow);
}


CeguiMgr::~CeguiMgr()
{
}

void CeguiMgr::injectOISKeyEvent(bool IsDown, OIS::KeyEvent keyEvent)
{
	if (IsDown)
	{
		CEGUI::System::getSingletonPtr()->getDefaultGUIContext().injectKeyDown((CEGUI::Key::Scan)keyEvent.key);
		CEGUI::System::getSingletonPtr()->getDefaultGUIContext().injectChar(keyEvent.text);
	} 
	else
	{
		CEGUI::System::getSingletonPtr()->getDefaultGUIContext().injectKeyUp((CEGUI::Key::Scan)keyEvent.key);
	}
}

void CeguiMgr::injectOISMouseRotation(float relativeX, float relativeY, float elapsedTime)
{
	CEGUI::System::getSingletonPtr()->getDefaultGUIContext().injectMouseMove(relativeX, relativeY);
	CEGUI::System::getSingletonPtr()->injectTimePulse(elapsedTime);
}

void injectOISMouseButton(bool IsDown, OIS::MouseButtonID buttonID)
{
	if (IsDown == true)
	{
		switch (buttonID)
		{
		case OIS::MB_Left:
			CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(CEGUI::LeftButton);
			break;
		case OIS::MB_Middle:
			CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(CEGUI::MiddleButton);
			break;
		case OIS::MB_Right:
			CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(CEGUI::RightButton);
			break;
		case OIS::MB_Button3:
			CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(CEGUI::X1Button);
			break;
		case OIS::MB_Button4:
			CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(CEGUI::X2Button);
			break;
		default:	
			break;

		}
	}
	else
	{
		switch (buttonID)
		{
		case OIS::MB_Left:
			CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(CEGUI::LeftButton);
			break;
		case OIS::MB_Middle:
			CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(CEGUI::MiddleButton);
			break;
		case OIS::MB_Right:
			CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(CEGUI::RightButton);
			break;
		case OIS::MB_Button3:
			CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(CEGUI::X1Button);
			break;
		case OIS::MB_Button4:
			CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(CEGUI::X2Button);
			break;
		default:	
			break;
		}
	}

}
