#include "GameConsole.h"
#include "ExceptionPerso.h"

#include <OgreLogManager.h>

using namespace CEGUI;

const std::set<std::string> GameConsole::msCommandes = GameConsole::staticSetInit();

const std::set<std::string> GameConsole::staticSetInit()
{
	const std::string tmp[] = {"say", "quit", "help", "dance", "tp", "invoke", "kill"};
	return std::set<std::string>(tmp, tmp + sizeof(tmp)/sizeof(tmp[0]));
}

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
		CEGUI::System::getSingletonPtr()->getDefaultGUIContext().getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");
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
			std::string command = inString.substr(1, commandEnd - 1);
			std::string commandArgs;

			if (!(commandEnd==std::string::npos))
			{
				commandArgs = inString.substr(commandEnd + 1, std::string::npos);
			}

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
				std::string outString = "Liste des commandes: ";

				std::set<std::string> cmd = getCommandes();

				for (std::set<std::string>::const_iterator it = cmd.cbegin(); it != cmd.cend(); ++it)
				{
					outString += (*it)+", ";
				}

				outString.erase(outString.length()-2);

				OutputText(outString, CEGUI::Colour(0.9f, 0.1f, 0.1f));
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

std::set<std::string> GameConsole::getCommandes()
{
	return msCommandes;
}
