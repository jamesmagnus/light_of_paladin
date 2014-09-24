#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <Ogre.h>

#include "ClassItem.h"
#include "ClassPersonnage.h"
#include "ClassInventaire.h"
#include "ClassArme.h"


using namespace std;

Personnage::Personnage(Ogre::SceneNode *pNode, int stat[EStat::ESTATMAX], bool IsVisible, std::string nom, int niveau, int XP):Humanoide(pNode, IsVisible, stat[VIE_MAX], nom)
{
    for (int i=0; i<ESTATMAX; i++)
    {
        m_stat[i] = stat[i];
    }

    m_niveau = niveau;
    m_XP = XP;
    m_mana = m_stat[MANA_MAX];
    mp_arme = nullptr;
    mp_inventaire = nullptr;
}

Personnage::~Personnage()
{
    if(mp_arme != nullptr)
    {
        delete mp_arme;
        mp_arme = nullptr;
    }

    if (mp_inventaire != nullptr)
    {
        delete mp_inventaire;
        mp_inventaire = nullptr;
    }
}

bool Personnage::isVivant() const
{
    if(mVie > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Personnage::boitPopoVie(EPopo type)
{
    if (mVie == m_stat[VIE_MAX])
    {
        return false;
    }
    else
    {
        int vieRendue = 0;

        switch (type)
        {
        case FAIBLE:
            vieRendue = 30 + 180*m_stat[GUERISON];
            break;
        case MOYENNE:
            vieRendue = 55 + 180*m_stat[GUERISON];
            break;
        case FORTE:
            vieRendue = 90 + 180*m_stat[GUERISON];
            break;
        case LEGENDAIRE:
            vieRendue = 135 + 180*m_stat[GUERISON];
            break;
        default:
            break;
        }

        mVie += vieRendue;

        if(mVie > m_stat[VIE_MAX])
        {
            mVie = m_stat[VIE_MAX];
        }

        return true;
    }
}

bool Personnage::boitPopoMana(EPopo type)
{
    if (m_mana == m_stat[MANA_MAX])
    {
        return false;
    } 
    else
    {
        int manaRendu = 0;

        switch (type)
        {
        case FAIBLE:
            manaRendu = 50 + 200*m_stat[GUERISON];
            break;
        case MOYENNE:
            manaRendu = 80 + 200*m_stat[GUERISON];
            break;
        case FORTE:
            manaRendu = 110 + 200*m_stat[GUERISON];
            break;
        case LEGENDAIRE:
            manaRendu = 160 + 200*m_stat[GUERISON];
            break;
        default:
            break;
        }

        m_mana += manaRendu;

        if (m_mana > m_stat[MANA_MAX])
        {
            m_mana = m_stat[MANA_MAX];
        }

        return true;
    }
}

void Personnage::prendDegat(int degatBrut, EDegat type)
{
    int degat = 0;

    switch (type)
    {
    case PHYSIQUE:
        degat = degatBrut * (1 - m_stat[ARMURE]);
        break;
    case MAGIQUE:
        degat = degatBrut * (1 - m_stat[REMPART]);
        break;
    case BRUT:
        degat = degatBrut;
        break;
    default:
        break;
    }

    mVie -= degat;

    if(mVie < 0)
    {
        mVie = 0;
    }
}

void Personnage::attaque(Personnage &rCible) const
{
    if (mp_arme != nullptr && mp_arme->getResistance() > 0.0)
    {
        rCible.prendDegat(valeurAttaqueBase(), PHYSIQUE);
        mp_arme->decreaseResistance();
    }
    else
    {
        rCible.prendDegat(1, PHYSIQUE);
    }
}

bool Personnage::changeArme(Arme *nouvelleArme)
{
    mp_arme = nouvelleArme;

    return true;
}

Arme* Personnage::quelleArme()
{
    return mp_arme;
}

int Personnage::valeurAttaqueBase() const
{
    if(mp_arme != nullptr)
    {
        return mp_arme->getDegat() * m_stat[FORCE];
    }
    else
    {
        return 1;
    }
}

bool Personnage::setInventaire(Inventaire *pInventaire)
{
    if (mp_inventaire != nullptr)
    {
        return false;
    }
    else if (pInventaire != nullptr)
    {
        mp_inventaire = pInventaire;

        return true;
    }
    else
    {
        return false;
    }
}

bool Personnage::supprInventaire()
{
    if (mp_inventaire != nullptr)
    {
        mp_inventaire = nullptr;

        return true;
    }
    else
    {
        return false;
    }
}

bool Personnage::viderInventaire()
{
    if (mp_inventaire != nullptr)
    {
        mp_inventaire->~Inventaire();

        return true;
    } 
    else
    {
        return false;
    }
}

int Personnage::placerItem(Item& rItem)
{
    return mp_inventaire->ajout(rItem);
}

int Personnage::placerItem(Item* const pItem)
{
    return mp_inventaire->ajout(pItem);
}

