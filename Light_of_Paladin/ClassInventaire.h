#pragma once

#include "ClassItem.h"

#include <map>

/* Classe pour gérer un inventaire, sémantique de valeur */
class Inventaire
{
	friend bool operator==(Inventaire const& inv1, Inventaire const& inv2);
	friend bool operator<(Inventaire const& inv1, Inventaire const& inv2);

protected:

	std::map<unsigned long, Item*> mStuff; //Pointeurs sur des Items, repérés par l'id
	int mNb, mMax;
	float mPoidTotal;

public:

	/* Constructeur */
	/* max, le nombre d'emplacements de l'inventaire */
	Inventaire(int max=10);

	/* Constructeur par copie, clone les items */
	Inventaire(Inventaire const& rOriginal);

	/* Opérateur d'assignement, clone les items */
	Inventaire& operator=(Inventaire const& rOriginal);

	/* Destructeur */
	virtual ~Inventaire();

	/* Renvoie le nombre d'items dans l'inventaire */
	inline int getNB() const;

	/* Renvoie le nombre max d'emplacement */
	inline int getMax() const;

	/* Modifie le nombre max d'emplacement */
	/* Renvoie si le nombre max a pu être modifié ( trop d'item ) */
	bool setMax(int newMax);

	/* Renvoie le poid de tous les objets contenus dans l'inventaire */
	inline float getPoidTotal() const;

	/* Ajoute un item par référence */
	/* Renvoie l'ID de l'item ajouté ou 0 en cas de problème */
	unsigned long ajout(Item& rItem);

	/* Ajoute un item par pointeur */
	/* Renvoie l'ID de l'item ajouté ou 0 en cas de problème */
	unsigned long ajout(Item* const pItem);

	/* Supprime un item par son pointeur */
	/* Renvoie true si l'item existait */
	bool suppr(Item* const pItem); 

	/* Supprime un item par son ID */
	/* Renvoie true si l'item existait */
	bool suppr(unsigned long ID);

	/* Vide l'inventaire */
	/* Renvoie si true si l'inventaire était vide */
	bool clear();

	/* Récupère un item par son ID */
	/* ID, l'identifiant de l'item */
	/* Retourne l'adresse de l'item ou nullptr */
	Item* getItem(unsigned long ID) const;

	/* Renvoie true si l'item demandé, ou son ID, est trouvé */
	inline bool existe(unsigned long ID) const;
	inline bool existe(Item* pItem) const;

#ifdef _DEBUG
	/* Affiche des informations sur l'inventaire dans la console, DEBUG */
	void afficheDebugInv(std::ostream& rOst) const;
#endif


	/* Surcharge des opérateurs internes */

	/* += */
	Inventaire& operator+=(Inventaire const& inv);
};


/* Surcharge des opérateurs externes*/

/* + */
Inventaire operator+(Inventaire const& inv1, Inventaire const& inv2);

/* == */
/* Deux inventaires sont égaux s'ils ont le même nombre d'objets et que ces objets sont les mêmes */
bool operator==(Inventaire const& inv1, Inventaire const& inv2);

/* < */
/* Un inventaire est inférieur à un autre s'il contient moins d'objet */
bool operator<(Inventaire const& inv1, Inventaire const& inv2);

#ifdef _DEBUG
/* << */
std::ostream& operator<<(std::ostream& rOst, Inventaire const& inv);
#endif

/* Fonctions inline */
inline int Inventaire::getNB() const
{
	return mNb;
}

inline int Inventaire::getMax() const
{
	return mMax;
}

inline bool Inventaire::existe(unsigned long ID) const
{
	return mStuff.find(ID) != mStuff.end();
}

inline bool Inventaire::existe(Item* pItem) const
{
	return mStuff.find(pItem->getID()) != mStuff.end();
}

inline float Inventaire::getPoidTotal() const
{
	return mPoidTotal;
}
