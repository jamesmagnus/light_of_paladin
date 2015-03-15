#pragma once

#include "ClassItem.h"

class Personnage;

/* Classe pour gérer les armes, sémantique d'entité */
/* Classe abstraite */
class Arme: public Item
{
protected:

	int mDegat;
	float mVitesse, mResistance;

public:

	/* Constructeur */
	/* pNode, adresse du noeud de Ogre */
	/* prix, poid, nom, caractéristiques de l'item */
	/* IsUnique, true si l'item ne peut se trouver 2 fois dans un même inventaire, false par défaut */
	/* degat, vitesse, resistance, caractéristiques de l'arme */
	/* IsVisible, true si l'arme doit être rendue par Ogre */
	Arme(Ogre::SceneNode *pNode, int degat, float vitesse=1.0f, float resistance=1.0f, int prix=0, float poid=1.0f, std::string const& nom="defaultWeapon", bool IsUnique=false, bool IsVisible=true);

	/* Destructeur */
	virtual ~Arme();

	/* Renvoie les dégat qu'inflige l'arme seule */
	int getDegat() const;

	/* Modifie les dégats de l'arme */
	void setDegat(int degat);

	/* Renvoie la vitesse de frappe de l'arme /seconde */
	float getVitesse() const;

	/* Modifie la vitesse d'attaque */
	/* vitesse, vitesse d'attaque en coup/seconde */
	void setVitesse(float vitesse);

	/* Renvoie la résistance actuelle de l'arme 0.0 -> 1.0 */
	float getResistance() const;

	/* Change la résistance actuelle de l'arme */
	/* resistance, entre 0.0 et 1.0 */
	void setResistance(float resistance);

	/* Diminue la résistance de l'arme, à appeler à chaque utilisation de l'arme */
	void decreaseResistance();

	/* Clonage, méthode virtuelle pure */
	virtual Arme* clone() const override =0;

	/* Le personnage peut-il s'équiper de cette arme, méthode virtuelle pure */
	virtual bool canUse(Personnage *pJoueur) const override =0;

#ifdef _DEBUG
	/* Affiche des informations sur l'objet dans la console, DEBUG */
	virtual void afficheDebug(std::ostream& rOst) const override;
#endif
};

/* Surcharge opérateurs externes */

/* == */ 
bool operator==(Item const& inv1, Item const& inv2);

#ifdef _DEBUG
/* << */
std::ostream& operator<<(std::ostream& rOst, Arme const& obj);
#endif
