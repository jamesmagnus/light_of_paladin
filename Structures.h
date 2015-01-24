#pragma once

#include <Ogre.h>

class HeightFieldShape;

enum class EDegat{PHYSIQUE, MAGIQUE, BRUT};
enum EStat{VIE_MAX, MANA_MAX, VITESSE, FORCE, INTELLIGENCE, DISCRETION, ARMURE, REMPART, REFLEXION, GUERISON, ESTATMAX};
enum class EPopo{FAIBLE, MOYENNE, FORTE, LEGENDAIRE};
enum class ETypeArmure{CASQUE, PLASTRON, GANT_G, GANT_D, BOTTE_G, BOTTE_D, JAMBIERE_G, JAMBIERE_D};

typedef struct sTableauChunks
{
	HeightFieldShape* ppChunk[9];
	Ogre::Vector3 positionJoueur;
} TableauChunks;