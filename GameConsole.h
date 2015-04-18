#pragma once

#include "CeguiMgr.h"

#include <boost/noncopyable.hpp>

#include <CEGUI/CEGUI.h>

/* Classe s'occupe de la console de chat et de commande */
/* Sémantique d'entité, hérite de boost::noncopyable */
class GameConsole: private boost::noncopyable
{
public:
	
	/* Constructeur */
	GameConsole(CeguiMgr *pCeguiMgr);

	/* Destructeur */
	~GameConsole();

	/* Construit la console */
	/* Léve une exception en cas d'erreur */
	void CreateCEGUIWindow();

	/* Afficher ou masquer la console */
	void setVisible(bool isVisible);

	/* Renvoie true si la console est visible actuellement, false sinon */
	bool IsVisible() const;

private:
	
	/* Set callback */
	void RegisterHandlers();

	bool HandleTextSubmitted(CEGUI::EventArgs const&e);
	bool HandleSendButtonPressed(CEGUI::EventArgs const&e);         
	void ParseText(CEGUI::String msg);
	void OutputText(CEGUI::String msg, CEGUI::Colour const& colour = CEGUI::Colour(0xFFFFFFFF));

	CeguiMgr *mpCeguiMgr;
	CEGUI::Window *mConsoleWindow;
	bool mIsVisible;
};

