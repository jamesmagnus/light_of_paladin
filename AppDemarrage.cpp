#include <OgreTerrain.h>
#include <OgreTextAreaOverlayElement.h>
#include <Newton.h>
#include <PagedGeometry.h>
#include <BatchPage.h>
#include <ImpostorPage.h>
#include <TreeLoader3D.h>
#include <SkyX.h>
#include <Hydrax.h>
#include <Noise/Perlin/Perlin.h>
#include <Modules/ProjectedGrid/ProjectedGrid.h>

#include "AppDemarrage.h"
#include "InputListener.h"
#include "ClassPersonnage.h"
#include "GestionnaireID.h"
#include "GestionnaireTerrain.h"
#include "ExceptionPerso.h"
#include "ClassArme.h"
#include "ClassEpee.h"
#include "ClassArmure.h"
#include "ClassInventaire.h"

using namespace Ogre;

AppDemarrage::AppDemarrage()
{
	mpRoot = nullptr;
	mpWindow = nullptr;
	mpSceneMgr = nullptr;
	mpCam = nullptr;
	mpSky = nullptr;
	mpTerrain = nullptr;
	mpWater = nullptr;
	mpTrees = nullptr;
}

AppDemarrage::~AppDemarrage()
{
	delete mpTrees->getPageLoader();
	delete mpTrees;
	delete mpWater;

	/* On supprime la racine si elle existe */
	if(mpRoot != nullptr)
	{
		delete mpRoot;
		mpRoot = nullptr;
	}

	/* Destruction des singletons */
	GestionnaireID::destroy();
}

void AppDemarrage::start()
{
	if(!initOGRE()) //Démarrage de Ogre
	{
		throw ExceptionPerso("Erreur dans AppDemarrage::initOGRE(), mais Ogre ne parait pas avoir levé une exception.", FATAL);
	}

	/* Création du singleton gestionnaire ID */
	GestionnaireID::getInstance();

	if(!createScene())  //Création de la scène
	{
		throw ExceptionPerso("Erreur lors de la création de la scène.", ERREUR);
	}

	InputListener *listener = new InputListener(mpWindow, mpCam);   //Ecouteur d'évènement

	mpRoot->addFrameListener(listener);

	infiniteLoop(); //Boucle de rendu
}

bool AppDemarrage::initOGRE()
{
	Ogre::ConfigFile config;    //Gestionnaire de fichier de config Ogre

	/* Chargement selon la compilation */
#ifdef _DEBUG
	mpRoot = new Root("plugins_d.cfg", "ogre.cfg", "Ogre_d.log");
	config.load("resources_d.cfg");
#else
	mpRoot = new Root("plugins.cfg", "ogre.cfg", "Ogre.log");
	config.load("resources.cfg");
#endif

	ConfigFile::SectionIterator sectionI = config.getSectionIterator();

	String archName, secName, typeName;

	while (sectionI.hasMoreElements())  //Tant qu'il reste des sections à lire
	{
		secName = sectionI.peekNextKey();
		ConfigFile::SettingsMultiMap *pSettingsMap = sectionI.getNext();
		ConfigFile::SettingsMultiMap::iterator i;

		/* On ajoute toutes les ressources */
		for (i=pSettingsMap->begin(); i != pSettingsMap->end(); ++i)
		{
			typeName = i->first;
			archName = i->second;

			ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
		}
	}

	/* Si on ne parvient pas à charger un fichier de config pour l'API de rendu, ni à lancer le dialogue de configuration, on quitte */
	if (!(mpRoot->restoreConfig() || mpRoot->showConfigDialog()))
	{
		return false;
	}

	/* Initialise la fenêtre de rendu avec son titre */
	mpWindow = mpRoot->initialise(true, "SAM");

	/* Niveau de mipMap (1x1x1) */
	TextureManager::getSingleton().setDefaultNumMipmaps(MIP_UNLIMITED);
	ResourceGroupManager::getSingleton().initialiseAllResourceGroups(); //On charge tout et on calcule les niveaux de mipMap

	/* Création du scène manager */
	mpSceneMgr = mpRoot->createSceneManager(ST_EXTERIOR_FAR, "SceneManager");

	/* Activation du filtrage anisotropique, niveau 8 */
	MaterialManager::getSingleton().setDefaultTextureFiltering(TFO_ANISOTROPIC);
	MaterialManager::getSingleton().setDefaultAnisotropy(8);

	return true;
}

bool AppDemarrage::createScene()
{
	if(!(createBase() && createSky() && createTerrain() && createObject() && createPersonnage()))
	{
		return false;
	}    

	return true;
}

bool AppDemarrage::createBase()
{
	mpSceneMgr->setAmbientLight(ColourValue(0.7f, 0.7f, 0.7f));
	mpSceneMgr->setShadowTechnique(SHADOWTYPE_TEXTURE_ADDITIVE_INTEGRATED);

	mpCam = mpSceneMgr->createCamera("Camera");
	mpCam->setPosition(Vector3(0.0, 80.0, 100.0));
	mpCam->lookAt(Vector3(0.0, 0.0, 0.0));
	mpCam->setNearClipDistance(2.0f);
	mpCam->setCastShadows(false);

	if (mpRoot->getRenderSystem()->getCapabilities()->hasCapability(RSC_INFINITE_FAR_PLANE))
	{
		mpCam->setFarClipDistance(60000);
	}
	else
	{
		mpCam->setFarClipDistance(30000);
	}

	Viewport *vp = mpWindow->addViewport(mpCam);
	vp->setBackgroundColour(ColourValue(1.0, 0.0, 1.0, 1.0));
	mpCam->setAspectRatio(vp->getActualWidth()/Real(vp->getActualHeight()));

	return true;
}

bool AppDemarrage::createSky()
{
	Light *pSoleil = mpSceneMgr->createLight("soleil");
	pSoleil->setType(Light::LT_DIRECTIONAL);
	pSoleil->setDirection(Vector3(3.0f, -1.0f, 0.0f));
	pSoleil->setDiffuseColour(ColourValue(0.7f, 0.68f, 0.73f));
	pSoleil->setSpecularColour(ColourValue(0.7f, 0.68f, 0.73f));

	mpWindow->getViewport(0)->setBackgroundColour(ColourValue(0.0f, 0.0f, 0.0f));

	mpSky = new SkyX::SkyX(mpSceneMgr, new SkyX::BasicController());

	mpSky->create();

	mpRoot->addFrameListener(mpSky);
	mpWindow->addListener(mpSky);

	// Couche de nuages basique
	mpSky->getCloudsManager()->add(SkyX::CloudLayer::Options());

	mpSky->getMoonManager()->setMoonSize(0.9f);

	return true;
}

bool AppDemarrage::createTerrain()
{
	mpTerrain = new GestionnaireTerrain(257, 10000, mpSceneMgr, mpSceneMgr->getLight("soleil"), mpCam, mpCam->getViewport());

	mpWater = new Hydrax::Hydrax(mpSceneMgr, mpCam, mpWindow->getViewport(0));

	Hydrax::Module::ProjectedGrid *module = new Hydrax::Module::ProjectedGrid(mpWater, new Hydrax::Noise::Perlin(), Ogre::Plane(Ogre::Vector3::UNIT_Y, 30.0), Hydrax::MaterialManager::NM_VERTEX, Hydrax::Module::ProjectedGrid::Options());

	mpWater->setModule(module);

	mpWater->loadCfg("HydraxDemo.hdx");

	mpWater->update(0.0);

	// Create water
	mpWater->create();

	mpTrees = new Forests::PagedGeometry();

	mpTrees->setCamera(mpCam);
	mpTrees->setPageSize(50);
	mpTrees->setBounds(Forests::TBounds(-5000, -5000, 5000, 5000));

	mpTrees->addDetailLevel<Forests::BatchPage>(500, 50);
	mpTrees->addDetailLevel<Forests::ImpostorPage>(1000, 100);

	//Create a new TreeLoader3D object first
	Forests::TreeLoader3D *treeLoader = new Forests::TreeLoader3D(mpTrees, Forests::TBounds(-5000, -5000, 5000, 5000));

	Entity *pEnt1 = mpSceneMgr->createEntity("tree", "arbre.mesh"), *pEnt2 = mpSceneMgr->createEntity("lila", "lila.mesh"), *pEnt3 = mpSceneMgr->createEntity("apple tree", "pommier.mesh");

	Entity* vege[] = {pEnt1, pEnt2, pEnt3};

	float x, y, z, yaw, scale;
	int t;
	for (int i = 0; i < 2000; i++){
		yaw = Math::RangeRandom(0.0f, 360.0f);
		x = Math::RangeRandom(-5000.0f, 5000.0f);
		z = Math::RangeRandom(-5000.0f, 5000.0f);
		scale = Math::RangeRandom(0.2f, 0.9f);
		t = static_cast<int>(Math::RangeRandom(0, 3));
		y = mpTerrain->getTerrains()->getTerrain(0, 0)->getHeightAtWorldPosition(x, 200, z);

		treeLoader->addTree(vege[t], Vector3(x, y, z), Degree(yaw), scale);
	}

	mpTrees->setPageLoader(treeLoader);

	/* TerrainLayerBlendMap *pBlendMap = mpTerrain->getLayerBlendMap(1);

	float *pBlend = pBlendMap->getBlendPointer();
	for (uint16 y=0; y < mpTerrain->getLayerBlendMapSize(); y++)
	{
	for (uint16 x=0; x < mpTerrain->getLayerBlendMapSize(); x++)
	{
	Real terrainX, terrainY;

	pBlendMap->convertImageToTerrainSpace(x, y, &terrainX, &terrainY);

	Real height = mpTerrain->getHeightAtTerrainPosition(terrainX, terrainY);

	if (height >= 800)
	{
	*pBlend++ = 1; //Neige au dessus de 800
	}
	else if (height <= 600)
	{
	*pBlend++ = 255;    //Roche en dessous de 400
	}
	else
	{
	*pBlend++ = height * (-1.27f) + 1017;   //Progressivement entre les deux
	}
	}
	}

	pBlendMap->dirty();
	pBlendMap->update();

	mpTerrain->freeTemporaryResources();*/


	return true;
}

bool AppDemarrage::createObject()
{

	return true;
}

bool AppDemarrage::createPersonnage()
{
	Entity *pEnt1 = mpSceneMgr->createEntity("pingouin", "penguin.mesh");
	SceneNode *pNodePeng = mpSceneMgr->getRootSceneNode()->createChildSceneNode("nodePengouin", Vector3(100.0f, 50.0f, 0.0f));
	pNodePeng->attachObject(pEnt1);

	Entity *pEnt2 = mpSceneMgr->createEntity("rylai", "rylai.mesh");
	SceneNode *pNodeRylai = pNodePeng->createChildSceneNode("nodeRylai", Vector3(-23.0f, 8.0f, 20.0f));
	pNodeRylai->pitch(Degree(45.0f));
	pNodeRylai->scale(Vector3(10.0, 10.0, 10.0));
	pNodeRylai->attachObject(pEnt2);

	ParticleSystem* sunParticle = mpSceneMgr->createParticleSystem("Boule de feu", "Particule/FireBall");
	SceneNode* particleNode = pNodePeng->createChildSceneNode("ParticleFire");
	particleNode->attachObject(sunParticle);
	particleNode->setPosition(0, 30, 0);

	int stat[ESTATMAX]={0};
	ajoutPersonnage(pNodePeng, "Samuel", stat, 1, 0, Vector3(0.0f), Vector3(0.0f));

	return true;
}

void AppDemarrage::infiniteLoop()
{
	Personnage *pSam = nullptr;
	bool bSens = true;


	/* test */
	try
	{
		pSam = getPersonnage("Samuel");
	}
	catch(std::exception& e)
	{
		e.what();
	}
	/* test */

	while (true)
	{
		WindowEventUtilities::messagePump();

		mpWater->update(0.01);

		if (!mpRoot->renderOneFrame())
		{
			return;
		}

		if (pSam != nullptr)
		{
			if(bSens && pSam->getNode()->getPosition().x < 200.0f)
			{
				pSam->getNode()->translate(0.1f, 0.0f, 0.0f);
			}
			else
			{
				bSens = false;
			}

			if (!bSens && pSam->getNode()->getPosition().x > 0.0f)
			{
				pSam->getNode()->translate(-0.1f, 0.0f, 0.0f);
			}
			else
			{
				bSens = true;
			}
		}

		mpTrees->update();
	}
}

bool AppDemarrage::ajoutPersonnage(Ogre::SceneNode *pNoeud, std::string nom, int stat[EStat::ESTATMAX], int niveau, int XP, Ogre::Vector3 position, Ogre::Vector3 rotation)
{
	//Personnage *pPersonnage =  new Personnage(pNoeud, stat, true, nom, niveau, XP);

	std::pair<std::map<std::string, Personnage*>::iterator, bool> retVal;

	//retVal = mmapPersonnages.insert(std::pair<std::string, Personnage*>(nom, pPersonnage));

	return retVal.second;
}

Personnage* AppDemarrage::getPersonnage(std::string nom) const
{
	std::map<std::string, Personnage*>::const_iterator it;
	it = mmapPersonnages.find(nom);

	if (it != mmapPersonnages.end())
	{
		return it->second;
	}
	else
	{
		std::string mesg = nom+": "+"Ce personnage n'existe pas. Opération abandonnée.";
		throw ExceptionPerso(mesg.c_str(), INFO);
	}
}