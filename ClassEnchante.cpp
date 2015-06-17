#include "StdLibAndNewOperator.h"
#include "ClassEnchante.h"
#include "ClassSort.h"

Enchante::Enchante(Ogre::SceneNode *pNode, int prix, float poid, std::string const& nom, bool IsUnique, bool IsVisible, Sort *pEnchantement):Item(pNode, prix, poid, nom, IsUnique, IsVisible)
{
	mpEnch = pEnchantement;
}


Enchante::~Enchante()
{
}

Sort* Enchante::getEnchantement() const
{
	return mpEnch;
}

bool Enchante::setEnchantement(Sort* pEnchantement)
{
	bool ret = getEnchantement() ? true : false;

	mpEnch = pEnchantement;

	return ret;
}

#ifdef _DEBUG
void Enchante::afficheDebug(std::ostream& rOst) const 
{
	Item::afficheDebug(rOst);

	if (mpEnch != nullptr)
	{
		rOst << "Enchantement: Oui" << std::endl << "Nom enchantement: " << mpEnch->getNom() << std::endl;
	} 
	else
	{
		rOst << "Enchantement: Non" << std::endl;
	}

	rOst << "-----------------------------------------------" << std::endl;
}
#endif

bool Enchante::compare(Item const& rSecondItem) const 
{
	/* D'après le RTTI on sait que l'item passé en paramètre est un Enchante */

	Enchante const& rItemEnchante = dynamic_cast<Enchante const&>(rSecondItem);

	Sort* p = rItemEnchante.getEnchantement();
	bool test;

	if (p != nullptr && mpEnch != nullptr)
	{
		test = (p->getNom() == mpEnch->getNom());
	}
	else
	{
		test = false;
	}

	return (Item::compare(rSecondItem) && ((p == nullptr && mpEnch == nullptr) || test));
}
