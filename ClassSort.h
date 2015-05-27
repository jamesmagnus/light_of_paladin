#pragma once

#include <string>

class Sort
{
public:

	/* Constructeur */
	Sort();

	/* Destructeur */
	virtual ~Sort();

	/* Renvoie le nom du sort */
	std::string const getNom() const;
};