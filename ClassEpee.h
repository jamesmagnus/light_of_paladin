#pragma once

#include "ClassArme.h"

/* Classe finale, gére les épées */
class Epee:public Arme
{
private:

	/* Constructeur de copie interdit */
	Epee(Epee const& original);

	/* Opérateur d'assignement interdit */
	Epee& operator=(Epee const& original);

public:

	/* Constructeur */
	/* pNode, adresse du noeud de Ogre */
	/* prix, poid, nom, caractéristiques de l'item */
	/* IsUnique, true si l'item ne peut se trouver 2 fois dans un même inventaire, false par défaut */
	/* degat, vitesse, resistance, caractéristiques de l'épée */
	/* IsVisible, true si l'épée doit être rendue par Ogre */
	Epee(Ogre::SceneNode *pNode, int degat, float vitesse=1.0f, float resistance=1.0f, int prix=0, float poid=1.0f, std::string nom="defaultWeapon", bool IsUnique=false, bool IsVisible=true);

	virtual ~Epee();

	/* Prédicat, renvoie true si les deux épées sont équivalentes (les mêmes sauf leur id) */
	virtual bool compare(Item const& rSecondeEpee) const override;

	/* Clonage */
	virtual Epee* clone() const override;

	/* Le personnage peut-il s'équiper de cette épée */
	virtual bool canUse(Personnage *pJoueur) const override;

#ifdef _DEBUG
	/* Affiche des informations sur l'objet dans la console, DEBUG */
	virtual void afficheDebug(std::ostream& rOst) const override;
#endif
};

/* Surcharge opérateurs externes */

#ifdef _DEBUG
/* << */
std::ostream& operator<<(std::ostream& rOst, Epee const& obj);
#endif