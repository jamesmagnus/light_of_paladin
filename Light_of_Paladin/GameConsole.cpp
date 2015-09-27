#include "StdLibAndNewOperator.h"
#include "GameConsole.h"
#include "ExceptionPerso.h"
#include "AppMain.h"
#include "FMODSoundMgr.h"

#include <OgreLogManager.h>

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

#include <CEGUI/PCRERegexMatcher.h>

using namespace CEGUI;

std::set<std::string> const GameConsole::msCommandes = GameConsole::staticSetInit();

std::set<std::string> const GameConsole::staticSetInit()
{
	std::vector<std::string> const tmp = { "say", "quit", "help", "dance", "tp", "invoke", "kill", "play_sound", "stop_sound" };
	return std::set<std::string>(tmp.cbegin(), tmp.cend());
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
		System::getSingletonPtr()->getDefaultGUIContext().getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");
		System::getSingletonPtr()->getDefaultGUIContext().getRootWindow()->addChild(mConsoleWindow);
		RegisterHandlers();
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

bool GameConsole::HandleTextSubmitted(EventArgs const&e)
{
	String Msg = mConsoleWindow->getChild("EditBox")->getText();

	ParseText(Msg);

	mConsoleWindow->getChild("EditBox")->setText("");

	return true;
}

bool GameConsole::HandleSendButtonPressed(EventArgs const&e)
{
	String Msg = mConsoleWindow->getChild("EditBox")->getText();
	ParseText(Msg);
	mConsoleWindow->getChild("EditBox")->setText("");

	return true;
}

void GameConsole::ParseText(String const& msg)
{
	std::string inString = msg.c_str();
	CEGUI::PCRERegexMatcher pcre;
	pcre.setRegexString(R"((\/\w+)((?(?=[ ]).*)))");

	if (pcre.getMatchStateOfString(msg) == CEGUI::PCRERegexMatcher::MatchState::MS_VALID)
	{
		inString.erase(0, 1);	// On efface le '/'
		std::transform(inString.begin(), inString.end(), inString.begin(), tolower);

		std::string::size_type posSpace = inString.find(" ");
		std::string command = inString.substr(0, posSpace);	//Le premier mot est la commande

		std::vector<std::string> args;
		posSpace != std::string::npos ? inString.erase(0, posSpace + 1) : inString.erase();	// On efface la commande et l'espace suit

		if (getCommandes().find(command) == getCommandes().cend())	//Commande incorrecte
		{
			std::string outString = "<" + command + "> n'est pas une commande valide.";
			OutputText(outString, CONSOLE_ROUGE);
		}
		else
		{
			while (inString != "")	// On récupère tous les arguments de la commande
			{
				posSpace = inString.find(" ");
				args.push_back(inString.substr(0, posSpace));
				posSpace != std::string::npos ? inString.erase(0, posSpace + 1) : inString.erase();
			}

			exeCommande(command, args);
		}
	}
}

void GameConsole::exeCommande(std::string const& command, std::vector<std::string> const& args) const
{
	if (command == "say")
	{
		std::string saying;

		for (auto word : args)
		{
			saying += word;
		}

		std::string outString = "Vous:" + saying;
		OutputText(outString);

	}
	else if (command == "quit")
	{

	}
	else if (command == "tp")
	{

	}
	else if (command == "dance")
	{

	}
	else if (command == "kill")
	{

	}
	else if (command == "invoke")
	{

	}
	else if (command == "help")
	{
		std::string outString = "Liste des commandes: ";

		std::set<std::string> const cmd = getCommandes();

		for (std::set<std::string>::const_iterator it = cmd.cbegin(); it != cmd.cend(); ++it)
		{
			outString += *it + ", ";
		}

		outString.erase(outString.length() - 2);

		OutputText(outString, CONSOLE_OLIVE);
	}
	else if (command == "play_sound")
	{
		for (auto son : args)
		{
			try
			{
				AppMain::getInstance()->getFMODSoundMgr()->playLoadedSound(son);
			}
			catch (ExceptionPerso const& e)
			{
				std::string msgErr = "Le son <" + son + "> n'a pas pu être trouvé. ";
				OutputText(msgErr, CONSOLE_ROUGE);
			}
		}
	}
	else if (command == "stop_sound")
	{
		for (auto son : args)
		{
			try
			{
				bool wasPlayed = AppMain::getInstance()->getFMODSoundMgr()->stopSound(son);

				if (wasPlayed)
				{
					OutputText(std::string("<") + son + "> était en lecture", CONSOLE_BLEU_MARINE);
				}
				else
				{
					OutputText(std::string("<") + son + "> n'était pas en lecture", CONSOLE_BLEU_MARINE);
				}
			}
			catch (ExceptionPerso const& e)
			{
				std::string msgErr = "Le son <" + son + "> n'a pas pu être trouvé. ";
				OutputText(msgErr, CONSOLE_ROUGE);
			}
		}
	}
}

void GameConsole::OutputText(String const& msg, Colour const& colour) const
{
	Listbox *outputWindow = static_cast<Listbox*>(mConsoleWindow->getChild("ChatBox"));

	ListboxTextItem* newItem = LOP_NEW ListboxTextItem(msg);
	newItem->setTextColours(colour);
	outputWindow->addItem(newItem);
}

std::set<std::string> const& GameConsole::getCommandes()
{
	return msCommandes;
}
