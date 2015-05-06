#pragma once

#include "CeguiMgr.h"

#include <boost/noncopyable.hpp>

#include <CEGUI/CEGUI.h>

#include <set>

/* Classe s'occupe de la console de chat et de commande */
/* S�mantique d'entit�, h�rite de boost::noncopyable */
class GameConsole: private boost::noncopyable
{
public:
	
	/* Constructeur */
	GameConsole(CeguiMgr *pCeguiMgr);

	/* Destructeur */
	~GameConsole();

	/* Construit la console */
	/* L�ve une exception en cas d'erreur */
	void CreateCEGUIWindow();

	/* Afficher ou masquer la console */
	void setVisible(bool isVisible);
	
	/* Renvoie true si la console est visible actuellement, false sinon */
	bool IsVisible() const;

	/* M�thode statique */
	/* Renvoie un ensemble contenant toute les commandes existantes */
	static std::set<std::string> getCommandes();

	/* M�thode statique */
	/* Construit l'ensemble statique des commandes de la classe */
	static const std::set<std::string> staticSetInit();

private:
	
	/* Ensemble static contenant toutes les commandes disponibles */
	static const std::set<std::string> msCommandes;

	/* Set callback */
	void RegisterHandlers();

	/* Gestion �v�nements texte envoy� */
	/* Renvoie true */
	bool HandleTextSubmitted(CEGUI::EventArgs const& e);
	
	/* Gestion �v�nements bouton press� */
	/* Renvoie true */
	bool HandleSendButtonPressed(CEGUI::EventArgs const& e);         

	/* Recherche des commande dans le message */
	/* msg, le message � ananlyser */
	void ParseText(CEGUI::String msg);

	/* Ajoute le texte pass� en param�tre dans la fen�tre de la console */
	/* msg, le texte � ajouter */
	/* colour, la couleur du texte (blanc par d�faut) */
	void OutputText(CEGUI::String msg, CEGUI::Colour const& colour = CEGUI::Colour(0xFFFFFFFF));

	CeguiMgr *mpCeguiMgr;
	CEGUI::Window *mConsoleWindow;
	bool mIsVisible;
};

