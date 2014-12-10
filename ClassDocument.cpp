#include "ClassDocument.h"

Document::Document(Ogre::SceneNode *pNode, int prix, float poid, std::string nom, bool IsUnique, bool IsVisible):Item(pNode, prix, poid, nom, IsUnique, IsVisible)
{
	mTitre="Default Title";
	mContenu="Default Content";
}

Document::~Document()
{

}

void Document::setTitre(std::string titre)
{
	if (titre != "")
	{
		mTitre = titre;
	}
}

std::string Document::getTitre() const
{
	return mTitre;
}

void Document::setContenu(std::string contenu)
{
	if (contenu != "")
	{
		mContenu = contenu;
	}
}

std::string Document::getContenu() const
{
	return mContenu;
}


/* Surcharge des opérateurs externes */

#ifdef _DEBUG
/* << */
std::ostream& operator<<(std::ostream& rOst, Document const& obj)
{
	obj.afficheDebug(rOst);

	return rOst;
}
#endif