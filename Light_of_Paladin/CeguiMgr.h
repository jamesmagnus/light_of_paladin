#pragma once

#include <OIS/OISKeyboard.h>
#include <OIS/OISMouse.h>

#include <boost/core/noncopyable.hpp>

class InputListener;
namespace CEGUI
{
	class OgreRenderer;
}

/* Classe pour gérer l'interface graphique */
/* Sémantique d'entité, hérite de boost::noncopyable */
/* Non dérivable */
class CeguiMgr: private boost::noncopyable
{
private:
	CEGUI::OgreRenderer* mpRenderer;
	bool mIsMenuMode;

	/* Met à jour les informations internes du gestionnaire après un changement de mode */
	void updateMode();

public:

	/* Constructeur */
	CeguiMgr();

	/* Destructeur */
	~CeguiMgr();

	/* Permet d'injecter un évènement pression d'une touche */
	/* IsDown, true si la touche a été enfoncée, false sinon */
	/* keyEvent, l'évènement pression d'une touche fourni par OIS */
	void injectOISKeyEvent(bool IsDown, OIS::KeyEvent const& keyEvent);

	/* Permet d'injecter un évènement bouton souris */
	/* IsDown, true si le bouton a été enfoncée, false sinon */
	/* buttonID, l'identifiant du bouton fourni par OIS */
	void injectOISMouseButton(bool IsDown, OIS::MouseButtonID buttonID);

	/* Permet d'injecter un évènement déplacement souris */
	/* relativeX, relativeY, déplacements relatifs de la souris selon ses axes */
	/* elapsedTime, le temps écoulé depuis la dernière frame */
	void injectOISMouseRotation(float relativeX, float relativeY, float elapsedTime);

	/* Charge un schéma XML */
	/* scheme, le nom du fichier à charger */
	void loadScheme(std::string const& scheme);

	/* Bascule du mode menu au mode jeu */
	/* mode, booléen false pour jeu, true pour menu */
	/* pas de paramètre -> permet de connaitre le mode sans le changer */
	/* Renvoie true si on était en mode menu false sinon */
	bool shiftMode() const;
	bool shiftMode(bool const mode);
};

