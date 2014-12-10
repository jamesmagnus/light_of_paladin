#include "Affichable.h"

using namespace Ogre;

Affichable::Affichable(SceneNode *pNode, bool IsVisible)
{
    mpNoeud = pNode;
    mIsVisible = IsVisible;
}

Affichable::~Affichable()
{
    mpNoeud = nullptr;     //On ne détruit pas le noeud de scène, il est géré par Ogre
}

void Affichable::setVisibility(bool visible)
{
    mIsVisible = visible;
}

bool Affichable::getVisibility() const
{
    return mIsVisible;
}

bool Affichable::setNode(SceneNode *pNoeud)
{
    if(mpNoeud != nullptr)
    {
        mpNoeud = pNoeud;
        return true;
    }
    else
    {
        mpNoeud = pNoeud;
        return false;
    }
}

SceneNode* Affichable::getNode() const
{
    return mpNoeud;
}

#ifdef _DEBUG
void Affichable::afficheDebug(std::ostream& rOst) const
{
	rOst << "Visible:" << std::boolalpha << mIsVisible << std::endl;
}
#endif

/* Surcharge des opérateurs externes */

#ifdef _DEBUG
/* << */
std::ostream& operator<<(std::ostream& rOst, Affichable const& obj)
{
	obj.afficheDebug(rOst);

	return rOst;
}
#endif
