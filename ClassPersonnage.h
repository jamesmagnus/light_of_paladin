#pragma once

#include "ClassHumanoide.h"
#include "enumerations.h"

namespace Ogre
{
	class SceneNode;
}

class Arme;
class Inventaire;
class Item;

/* Cette classe est utilisée pour gérer les personnages du jeu, sémantique d'entité */
class Personnage: public Humanoide
{
protected:

    int m_mana, m_niveau, m_XP;
    int m_stat[EStat::ESTATMAX];
    Arme *mp_arme;

public:

    /* Constructeur */
    /* pNode, adresse du noeud de scène lié au personnage */
    /* stat, tableau de int qui représente les compétences du personnage */
    /* IsVisible, true si le personnage doit être rendu par Ogre */
    /* nom, le nom du personnage */
    /* niveau, le niveau du personnage */
    /* XP, l'XP du personnage 0 -> 1000 */
    Personnage(Ogre::SceneNode *pNode, int stat[EStat::ESTATMAX], bool IsVisible=true, std::string nom="DefaultName", int niveau=1, int XP=0); 

    /* Destructeur */
    virtual ~Personnage(); 

    /* Renvoie si le personnage est vivant */
    bool isVivant() const;

    /* Fait boire une potion de vie */
    bool boitPopoVie(EPopo type);

    /* Fait boire une potion de mana */
    bool boitPopoMana(EPopo type);

    /* Inflige des dégâts au personnage */
    /* nbDegat: quantité de dégât brut */
    /* type: type de dégât (physique, magique) */
    void prendDegat(int nbDegat, EDegat type);

    /* Attaque un autre personnage */
    /* rCible: référence vers la cible */
    void attaque(Personnage& rCible) const;

    /* Permet de changer l'arme */
    /* nouvelleArme: std::string nom de la nouvelle arme */
    /* Renvoie si le changement à réussi */
    bool changeArme(Arme *pNouvelleArme);

    /* Affecte un inventaire au personnage */
    /* Renvoie true s'il n'y avait pas d'inventaire déjà lié, sinon false et l'inventaire n'est pas remplacer */
    bool setInventaire(Inventaire *pInventaire);

    /* Supprime l'inventaire du personnage mais l'objet continue d'exister */
    /* Renvoie true s'il y en avait un, sinon false */
    bool supprInventaire();

    /* Permet au personnage de placer un objet dans son inventaire */
    /* Renvoie l'ID de l'item ajouté ou -1 si l'inventaire est plein */
    int placerItem(Item& rItem);
    int placerItem(Item* const pItem);

    /* Renvoie un pointeur vers l'arme actuelle */
    Arme* quelleArme();

    /* Renvoie la valeur des attaques physiques calculée à partir de l'arme et des stats du personnage */
    int valeurAttaqueBase() const;

    /* Vide l'inventaire mais il conserve sa taille max, appeler SetMax() pour la changer */
    /* Retourne true s'il y avait un inventaire à vider */
    bool viderInventaire();

	/* Clonage, méthode virtuelle pure */
	virtual Personnage* clone() const override=0;

#ifdef _DEBUG
	/* Affiche des informations sur l'objet dans la console, DEBUG */
	virtual void afficheDebug(std::ostream& rOst) const override=0;
#endif
};

/* Surcharge des opérateurs externes */

#ifdef _DEBUG
/* << */
std::ostream& operator<<(std::ostream& rOst, Personnage const& obj);
#endif