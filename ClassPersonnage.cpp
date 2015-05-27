#include "ClassPersonnage.h"
#include "ClassInventaire.h"
#include "ClassArme.h"

using namespace std;

Personnage::Personnage(Ogre::SceneNode *pNode, int stat[EStat::ESTATMAX], bool IsVisible, std::string const& nom, int niveau, int XP):Humanoide(pNode, IsVisible, stat[EStat::VIE_MAX], nom)
{
    for (int i=0; i<EStat::ESTATMAX; i++)
    {
        m_stat[i] = stat[i];
    }

    m_niveau = niveau;
    m_XP = XP;
    m_mana = m_stat[MANA_MAX];
    mp_arme = nullptr;
    mpInventaire = nullptr;
}

Personnage::~Personnage()
{
    if(mp_arme != nullptr)
    {
        delete mp_arme;
        mp_arme = nullptr;
    }

    if (mpInventaire != nullptr)
    {
        delete mpInventaire;
        mpInventaire = nullptr;
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
		case EPopo::FAIBLE:
            vieRendue = 30 + 180*m_stat[GUERISON];
            break;
        case EPopo::MOYENNE:
            vieRendue = 55 + 180*m_stat[GUERISON];
            break;
        case EPopo::FORTE:
            vieRendue = 90 + 180*m_stat[GUERISON];
            break;
        case EPopo::LEGENDAIRE:
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
        case EPopo::FAIBLE:
            manaRendu = 50 + 200*m_stat[GUERISON];
            break;
        case EPopo::MOYENNE:
            manaRendu = 80 + 200*m_stat[GUERISON];
            break;
        case EPopo::FORTE:
            manaRendu = 110 + 200*m_stat[GUERISON];
            break;
        case EPopo::LEGENDAIRE:
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
	case EDegat::PHYSIQUE:
        degat = degatBrut * (1 - m_stat[ARMURE]);
        break;
    case EDegat::MAGIQUE:
        degat = degatBrut * (1 - m_stat[REMPART]);
        break;
    case EDegat::BRUT:
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
        rCible.prendDegat(valeurAttaqueBase(), EDegat::PHYSIQUE);
        mp_arme->decreaseResistance();
    }
    else
    {
        rCible.prendDegat(1, EDegat::PHYSIQUE);
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
    if (mpInventaire != nullptr)
    {
        return false;
    }
    else if (pInventaire != nullptr)
    {
        mpInventaire = pInventaire;

        return true;
    }
    else
    {
        return false;
    }
}

bool Personnage::supprInventaire()
{
    if (mpInventaire != nullptr)
    {
        mpInventaire = nullptr;

        return true;
    }
    else
    {
        return false;
    }
}

bool Personnage::viderInventaire()
{
    if (mpInventaire != nullptr)
    {
        delete mpInventaire;

        return true;
    } 
    else
    {
        return false;
    }
}

int Personnage::placerItem(Item& rItem)
{
    return mpInventaire->ajout(rItem);
}

int Personnage::placerItem(Item* const pItem)
{
    return mpInventaire->ajout(pItem);
}

#ifdef _DEBUG
std::ostream& operator<<(std::ostream& rOst, Personnage const& obj)
{
	obj.afficheDebug(rOst);

	return rOst;
}
#endif