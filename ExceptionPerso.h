#pragma once

#include <exception>

#include "enumerations.h"

class ExceptionPerso : public std::exception
{
public:

    /* Constructeur */
    ExceptionPerso(const char* const & message, ENiveau niv) throw();

    /* Destructeur */
    virtual ~ExceptionPerso() throw();

    /* Renvoie le niveau de l'exception */
    ENiveau getLvl() const throw();

    /* Affiche le message de l'exception */
    virtual const char* what() const throw();

protected:

    ENiveau mNiveau;
};
