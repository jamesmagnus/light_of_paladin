#pragma once

#include <OIS/OISKeyboard.h>
#include <OIS/OISMouse.h>

#include <boost/noncopyable.hpp>

class InputListener;
namespace CEGUI
{
	class OgreRenderer;
}

/* Classe pour g�rer l'interface graphique */
/* S�mantique d'entit�, h�rite de boost::noncopyable */
/* Non d�rivable */
class CeguiMgr: private boost::noncopyable
{
private:
	CEGUI::OgreRenderer* mpRenderer;
	bool mIsMenuMode;

	/* Met � jour les informations internes du gestionnaire apr�s un changement de mode */
	void updateMode();

public:

	/* Constructeur */
	CeguiMgr();

	/* Destructeur */
	~CeguiMgr();

	/* Permet d'injecter un �v�nement pression d'une touche */
	/* IsDown, true si la touche a �t� enfonc�e, false sinon */
	/* keyEvent, l'�v�nement pression d'une touche fourni par OIS */
	void injectOISKeyEvent(bool IsDown, OIS::KeyEvent const& keyEvent);

	/* Permet d'injecter un �v�nement bouton souris */
	/* IsDown, true si le bouton a �t� enfonc�e, false sinon */
	/* buttonID, l'identifiant du bouton fourni par OIS */
	void injectOISMouseButton(bool IsDown, OIS::MouseButtonID buttonID);

	/* Permet d'injecter un �v�nement d�placement souris */
	/* relativeX, relativeY, d�placements relatifs de la souris selon ses axes */
	/* elapsedTime, le temps �coul� depuis la derni�re frame */
	void injectOISMouseRotation(float relativeX, float relativeY, float elapsedTime);

	/* Charge un sch�ma XML */
	/* scheme, le nom du fichier � charger */
	void loadScheme(std::string const& scheme);

	/* Bascule du mode menu au mode jeu */
	/* mode, bool�en false pour jeu, true pour menu */
	/* pas de param�tre -> permet de connaitre le mode sans le changer */
	/* Renvoie true si on �tait en mode menu false sinon */
	bool shiftMode() const;
	bool shiftMode(bool const mode);
};

