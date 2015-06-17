#pragma once

#include "CeguiMgr.h"

#include <boost/core/noncopyable.hpp>

#include <CEGUI/CEGUI.h>

#include <set>

/* Définitions des couleurs utilisées dans la console */
#define Couleur( r, v, b) CEGUI::Colour(r/255.0f, v/255.0f, b/255.0f)

#define CONSOLE_CYAN Couleur(0x0, 0xFF, 0xFF)
#define CONSOLE_NOIR Couleur(0x0, 0x0, 0x0)
#define CONSOLE_BLEU Couleur(0x0, 0x0, 0xFF)
#define CONSOLE_MAGENTA Couleur(0xFF, 0x0, 0xFF)
#define CONSOLE_VERT Couleur(0x0, 0x80, 0x0)
#define CONSOLE_GRIS Couleur(0x80, 0x80, 0x80)
#define CONSOLE_VERT_CLAIR Couleur(0x0, 0xFF, 0x0)
#define CONSOLE_BORDEAUX Couleur(0x80, 0x0, 0x0)
#define CONSOLE_BLEU_MARINE Couleur(0x0, 0x0, 0x80)
#define CONSOLE_OLIVE Couleur(0x80, 0x80, 0x0)
#define CONSOLE_VIOLET Couleur(0x80, 0x0, 0x80)
#define CONSOLE_ROUGE Couleur(0xFF, 0x0, 0x0)
#define CONSOLE_ARGENT Couleur(0xC0, 0xC0, 0xC0)
#define CONSOLE_SARCELLE Couleur(0x0, 0x80, 0x80)
#define CONSOLE_BLANC Couleur(0xFF, 0xFF, 0xFF)
#define CONSOLE_JAUNE Couleur(0xFF, 0xFF, 0x0)

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
	static std::set<std::string> const& getCommandes();

	/* Méthode statique */
	/* Construit l'ensemble statique des commandes de la classe */
	static std::set<std::string> const staticSetInit();

private:

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
	void ParseText(CEGUI::String const& msg);

	/* Ajoute le texte passé en paramètre dans la fenêtre de la console */
	/* msg, le texte à ajouter */
	/* colour, la couleur du texte (blanc par défaut) */
	void OutputText(CEGUI::String const& msg, CEGUI::Colour const& colour = CONSOLE_BLANC) const;

	/* Exécute une commande passée en paramètre */
	/* command, std::string contenant une commande valide */
	/* args, std::vector de std::string contenant les différents arguments de la commande */
	void exeCommande(std::string const& command, std::vector<std::string> const& args) const;

	CeguiMgr *mpCeguiMgr;
	CEGUI::Window *mConsoleWindow;
	bool mIsVisible;

	/* Ensemble static contenant toutes les commandes disponibles */
	static std::set<std::string> const msCommandes;
};

