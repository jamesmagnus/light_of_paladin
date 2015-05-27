#include "ClassDocument.h"

#include <string>

Document::Document(Ogre::SceneNode *pNode, int prix, float poid, std::string const& nom, bool IsUnique, bool IsVisible, Sort *pEnchantement):Enchante(pNode, prix, poid, nom, IsUnique, IsVisible, pEnchantement)
{
	mTitre="Default Title";
	mContenu="Default Content";
}

Document::~Document()
{

}

void Document::setTitre(std::string const& titre)
{
	if (titre != "")
	{
		mTitre = titre;
	}
}

std::string const& Document::getTitre() const
{
	return mTitre;
}

void Document::setContenu(std::string const& contenu)
{
	if (contenu != "")
	{
		mContenu = contenu;
	}
}

std::string const& Document::getContenu() const
{
	return mContenu;
}
