#pragma once

#include <set>
#include <vector>

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>

class GestionnaireID
{
protected:

    boost::random::mt19937 mEngine;
    boost::random::uniform_int_distribution<unsigned long> *mpLongDistrib;
    std::set<unsigned long> mIDExistants;
    const unsigned int mIDMax;

public:

    /* Constructeur */
    /* maxID, le nombre total d'ID unique pouvant être générés, entre 1 et maxID+1, 0 est une erreur */
    GestionnaireID(const unsigned int maxID);

    /* Destructeur */
    virtual ~GestionnaireID();

    /* Génére un nouvel ID unique, s'il n'y a plus d'ID disponible lève une exception */
    unsigned long newID();

    /* Retourne true s'il reste encore des IDs diponibles */
    bool isMoreIDFree() const;

    /* Retourne true si l'ID existe déjà */
    bool IsIDPresent(unsigned long id) const;

    /* Memorise une liste d'IDs déjà utilisés afin qu'il ne soit plus générer */
    /* liste, un std::vector<long> contenant les IDs */
    /* Retourne true s'il reste des IDs disponibles */
    bool memoriseID(std::vector<unsigned long> liste);
};