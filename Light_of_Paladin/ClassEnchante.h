#pragma once

#include "ClassItem.h"

class Sort;

class Enchante :public Item
{
private:

	Sort *mpEnch;

public:

	/* Constructeur */
	/* pNode, l'adresse du noeud de Ogre */
	/* shapeType, enum Shape qui détermine quel forme est utilisée pour représenter l'objet */
	/* prix, poid, nom, caractéristiques de l'item enchanté */
	/* IsUnique, true si l'item enchanté ne peut se trouver 2 fois dans un même inventaire, false par défaut */
	/* IsVisible, true si l'item enchanté doit être rendu par Ogre */
	Enchante(Ogre::SceneNode *pNode, EShape shapeType, int prix=0, float poid=1.0, std::string const& nom="defaultItemEnchanted", bool IsUnique=false, bool IsVisible=true, Sort *pEnchantement=nullptr);

	/* Destructeur */
	virtual ~Enchante();

	/* Renvoie l'adresse de l'enchantement */
	/* nullptr si pas d'enchantement */
	Sort* getEnchantement() const;

	/* Change l'enchantement de l'item */
	/* pEnchantement, adresse du nouveau sort, nullptr pour désenchanter */
	/* Renvoie true si un enchantement était déja présent */
	bool setEnchantement(Sort* pEnchantement);

#ifdef _DEBUG
	/* Affiche des informations sur l'objet dans la console, DEBUG */
	virtual void afficheDebug(std::ostream& rOst) const override;
#endif

	/* Prédicat, renvoie true si les deux items enchantés sont équivalents (les mêmes sauf leur id) */
	virtual bool compare(Item const& rSecondItem) const override;
};
