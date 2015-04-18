#include "GameConsole.h"
#include "ExceptionPerso.h"

#include <OgreLogManager.h>

using namespace CEGUI;

GameConsole::GameConsole(CeguiMgr *pCeguiMgr)
{
	mConsoleWindow = nullptr;
	mIsVisible = false;

	mpCeguiMgr = pCeguiMgr;
}


GameConsole::~GameConsole()
{
}

void GameConsole::CreateCEGUIWindow()
{
	mpCeguiMgr->loadScheme("TaharezLook.scheme");
	mConsoleWindow = WindowManager::getSingletonPtr()->loadLayoutFromFile("console.layout");

	if (mConsoleWindow != nullptr)
	{
		System::getSingletonPtr()->getDefaultGUIContext().getRootWindow()->addChild(mConsoleWindow);
		this->RegisterHandlers();
	}
	else
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LogMessageLevel::LML_CRITICAL, "CEGUI can't initialize the game console. Be sure that console.layout exists.");
		throw ExceptionPerso("CEGUI can't initialize the game console. Be sure that console.layout exists.", ERREUR);
	}
}

void GameConsole::RegisterHandlers()
{
	mConsoleWindow->getChild("SendButton")->subscribeEvent(PushButton::EventClicked, &GameConsole::HandleSendButtonPressed, this);
	mConsoleWindow->getChild("EditBox")->subscribeEvent(Editbox::EventTextAccepted, &GameConsole::HandleTextSubmitted, this);
}

bool GameConsole::HandleTextSubmitted(CEGUI::EventArgs const&e)
{
	CEGUI::String Msg = mConsoleWindow->getChild("EditBox")->getText();

	this->ParseText(Msg);

	mConsoleWindow->getChild("EditBox")->setText("");

	return true;
}

bool GameConsole::HandleSendButtonPressed(CEGUI::EventArgs const&e)
{
	CEGUI::String Msg = mConsoleWindow->getChild("EditBox")->getText();
	this->ParseText(Msg);
	mConsoleWindow->getChild("EditBox")->setText("");

	return true;
}

void GameConsole::ParseText(CEGUI::String msg)
{
	std::string inString = msg.c_str();

	if (inString.length() >= 1)
	{
		if (inString.at(0) == '/')
		{
			std::string::size_type commandEnd = inString.find(" ", 1);
			if (commandEnd == std::string::npos)
			{

			}
			std::string command = inString.substr(1, commandEnd - 1);
			std::string commandArgs = inString.substr(commandEnd + 1, std::string::npos);

			for(std::string::size_type i=0; i < command.length(); i++)
			{
				command[i] = tolower(command[i]);
			}

			if (command == "say")
			{
					std::string outString = "Vous:" + commandArgs;
					OutputText(outString);
				
			}
			else if (command == "quit")
			{

			}
			else if (command == "help")
			{
				std::string outString = "Liste des commandes:";
				OutputText(outString);
			}
			else
			{
				std::string outString = "<" + inString + "> is an invalid command.";
				this->OutputText(outString,CEGUI::Colour(1.0f,0.0f,0.0f));
			}
		}
		else
		{
			this->OutputText(inString);
		}
	} 
}

void GameConsole::OutputText(CEGUI::String msg, CEGUI::Colour const& colour)
{
	CEGUI::Listbox *outputWindow = static_cast<CEGUI::Listbox*>(mConsoleWindow->getChild("ChatBox"));

	CEGUI::ListboxTextItem* newItem=nullptr;

	newItem = new CEGUI::ListboxTextItem(msg);
	newItem->setTextColours(colour);
	outputWindow->addItem(newItem);
}
