#pragma once

#include "ClassItem.h"

enum class ETypeArmure{CASQUE, PLASTRON, GANT_G, GANT_D, BOTTE_G, BOTTE_D, JAMBIERE_G, JAMBIERE_D};

/* Classe finale qui sert à manipuler les différentes parties d'armure */
/* Sémantique d'entité */
class Armure : public Item
{
private:
	int mPtsProtection;
	float mEtat;
	ETypeArmure mType;

public:

	/* Constructeur */
	/* pNode, adresse du noeud de Ogre */
	/* prix, poid, nom, caractéristiques de l'item */
	/* IsUnique, true si l'armure ne peut se trouver 2 fois dans un même inventaire, false par défaut */
	/* IsVisible, true si l'armure doit être rendue par Ogre */
	/* pointProtection, etat, caractéristiques de l'armure */
	Armure(Ogre::SceneNode *pNode, ETypeArmure type, int prix=0, float poid=1.0f, std::string nom="DefaultArmor", bool IsUnique=false, bool IsVisible=true, int pointProtection=0, float etat=1.0f);

	/* Destructeur */
	virtual ~Armure();

	/* Renvoie le nombre de points de protection de la pièce d'armure */
	int getPtsProtection() const;

	/* Change le nombre de points de protection fourni par la pièce d'armure */
	/* pts, le nouveau nombre de points */
	void setPtsProtection(int pts);

	/* Renvoie l'état de la pièce d'armure 0.0 -> 1.0 */
	float getEtat() const;

	/* Change l'état de la pièce d'armure */
	/* etat, le nouvel état de la pièce 0.0 -> 1.0 */
	void setEtat(float etat);

	/* Renvoie le type d'armure, appartient à l'enum ETypeArmure */
	ETypeArmure getType() const;

	/* Modifie le type de l'armure, attention il faut modifier le mesh ! */
	/* type, le nouveau type de l'armure ETypeArmure */
	void setType(ETypeArmure type);

	/* Clonage */
	virtual Armure* clone() const override;

	/* Prédicat, renvoie true si le personnage peut s'équiper de la pièce d'armure */
	virtual bool canUse(Personnage *pJoueur) const override;

	/* Prédicat, renvoie true si les deux armures sont équivalentes (les mêmes sauf leur id) */
	virtual bool compare(Item const& rSecondeArmure) const override;

#ifdef _DEBUG
	/* Affiche des informations sur l'objet dans la console, DEBUG */
	virtual void afficheDebug(std::ostream& rOst) const override;
#endif
};

/* Surcharge des opérateurs externes */

#ifdef _DEBUG
/* << */
std::ostream& operator<<(std::ostream& rOst, Armure const& obj);
#endif