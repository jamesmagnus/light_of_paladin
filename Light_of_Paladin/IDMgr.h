#pragma once

#include <set>
#include <vector>

#include <boost/core/noncopyable.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>


/* Classe utilisée pour générer les identifiants unique de chaque item du jeu */
/* Classe finale, non dérivable */
/* Sémantique d'entité, hérite de coost::noncopyable */
/* Singleton */
class IDMgr: private boost::noncopyable
{
private:
	static IDMgr *mpsInstanceUnique;

    boost::random::mt19937 mEngine;
    boost::random::uniform_int_distribution<unsigned long> *mpLongDistrib;
    std::set<unsigned long> mIDExistants;

    /* Constructeur interne du singleton */
    IDMgr();

    /* Destructeur interne */
    ~IDMgr();

	/* Constructeur par copie interdit */
	IDMgr(IDMgr const& rOriginal);

	/* Opérateur d'affectation interdit */
	IDMgr& operator=(IDMgr const& rOriginal);

public:

	/* Renvoie un pointeur vers l'unique instance du gestionnaire d'ID */
	static IDMgr* getInstance();

	/* Détruit l'unique instance */
	static void destroy();

    /* Génére un nouvel ID unique, s'il n'y a plus d'ID disponible lève une exception */
    unsigned long newID();

    /* Retourne true s'il reste encore des IDs diponibles */
    bool isMoreIDFree() const;

    /* Retourne true si l'ID existe déjà */
    bool IsIDPresent(unsigned long id) const;

    /* Memorise une liste d'IDs déjà utilisés afin qu'il ne soit plus générer */
    /* liste, un std::vector<unsigned long> contenant les IDs */
    /* Retourne true s'il reste des IDs disponibles après mémorisation */
    bool memoriseID(std::vector<unsigned long> const& liste);
};