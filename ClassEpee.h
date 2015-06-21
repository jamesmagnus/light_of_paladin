#pragma once

#include "ClassArme.h"

/* Classe finale, gére les épées */
class Epee:public Arme
{
public:

	/* Constructeur */
	/* pNode, adresse du noeud de Ogre */
	/* shapeType, enum Shape qui détermine quel forme est utilisée pour représenter l'objet */
	/* prix, poid, nom, caractéristiques de l'item */
	/* IsUnique, true si l'item ne peut se trouver 2 fois dans un même inventaire, false par défaut */
	/* degat, vitesse, resistance, caractéristiques de l'épée */
	/* IsVisible, true si l'épée doit être rendue par Ogre */
	Epee(Ogre::SceneNode *pNode, EShape shapeType, int degat, float vitesse=1.0f, float resistance=1.0f, int prix=0, float poid=1.0f, std::string const& nom="defaultWeapon", bool IsUnique=false, bool IsVisible=true);

	virtual ~Epee();

	/* Prédicat, renvoie true si les deux épées sont équivalentes (les mêmes sauf leur id) */
	virtual bool compare(Item const& rSecondeEpee) const override;

	/* Clonage */
	virtual Epee* clone() const override;

	/* Le personnage peut-il s'équiper de cette épée */
	virtual bool canUse(Personnage const& rJoueur) const override;

#ifdef _DEBUG
	/* Affiche des informations sur l'objet dans la console, DEBUG */
	virtual void afficheDebug(std::ostream& rOst) const override;
#endif
};
