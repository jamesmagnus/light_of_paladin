#pragma once

#include "CeguiMgr.h"

#include <boost/noncopyable.hpp>

#include <CEGUI/CEGUI.h>

#include <set>

/* Classe qui s'occupe de la console de chat et de commande */
/* Sémantique d'entité, hérite de boost::noncopyable */
class GameConsole: private boost::noncopyable
{
public:
	
	/* Constructeur */
	GameConsole(CeguiMgr *pCeguiMgr);

	/* Destructeur */
	~GameConsole();

	/* Construit la console */
	/* Lève une exception en cas d'erreur */
	void CreateCEGUIWindow();

	/* Afficher ou masquer la console */
	void setVisible(bool isVisible);
	
	/* Renvoie true si la console est visible actuellement, false sinon */
	bool IsVisible() const;

	/* Méthode statique */
	/* Renvoie un ensemble contenant toute les commandes existantes */
	static std::set<std::string> getCommandes();

	/* Méthode statique */
	/* Construit l'ensemble statique des commandes de la classe */
	static const std::set<std::string> staticSetInit();

private:
	
	/* Ensemble static contenant toutes les commandes disponibles */
	static const std::set<std::string> msCommandes;

	/* Set callback */
	void RegisterHandlers();

	/* Gestion évènements texte envoyé */
	/* Renvoie true */
	bool HandleTextSubmitted(CEGUI::EventArgs const& e);
	
	/* Gestion évènements bouton pressé */
	/* Renvoie true */
	bool HandleSendButtonPressed(CEGUI::EventArgs const& e);         

	/* Recherche des commande dans le message */
	/* msg, le message à ananlyser */
	void ParseText(CEGUI::String msg);

	/* Ajoute le texte passé en paramètre dans la fenêtre de la console */
	/* msg, le texte à ajouter */
	/* colour, la couleur du texte (blanc par défaut) */
	void OutputText(CEGUI::String msg, CEGUI::Colour const& colour = CEGUI::Colour(0xFFFFFFFF));

	CeguiMgr *mpCeguiMgr;
	CEGUI::Window *mConsoleWindow;
	bool mIsVisible;
};

