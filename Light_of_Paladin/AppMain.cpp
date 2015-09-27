#include "StdLibAndNewOperator.h"
#include "AppMain.h"
#include "WaterMgr.h"
#include "LightMgr.h"
#include "IDMgr.h"
#include "ExceptionPerso.h"
#include "InputListener.h"
#include "TerrainMgr.h"
#include "CeguiMgr.h"
#include "GameConsole.h"
#include "FMODSoundMgr.h"
#include "PhysicMgr.h"

#include <SkyX.h>
#include <OgreTerrainGroup.h>
#include <PagedGeometry.h>
#include <BatchPage.h>
#include <ImpostorPage.h>
#include <TreeLoader3D.h>

#include <boost/thread.hpp>
#include <boost/chrono.hpp>

#include "ClassEpee.h"
#include "ClassArmure.h"
#include <btBulletDynamicsCommon.h>

using namespace Ogre;

AppMain::AppMain()
{
	LogManager *pLogMgr = OGRE_NEW LogManager();
	LogManager::getSingletonPtr()->createLog("LoP.log", true);
	LogManager::getSingletonPtr()->logMessage(LML_NORMAL, "!***! Light of Paladin started !***!");

	mpRoot = nullptr;
	mpWindow = nullptr;
	mpSceneMgr = nullptr;
	mpCam = nullptr;
	mpSky = nullptr;
	mpTerrain = nullptr;
	mpWater = nullptr;
	mpTrees = nullptr;
	mpWater = nullptr;
	mpCam = nullptr;
	mpCeguiMgr = nullptr;
	mpListener = nullptr;
	mpSoundMgr = nullptr;
	mpPhysicMgr = nullptr;

	std::srand(time(nullptr));
}

AppMain::~AppMain()
{
	LogManager::getSingletonPtr()->logMessage(LML_NORMAL, "AppMain destruction started...");

	LogManager::getSingletonPtr()->logMessage(LML_NORMAL, "Destruction SkyX...");
	if (mpRoot != nullptr && mpWindow != nullptr && mpSky != nullptr)
	{
		mpRoot->removeFrameListener(mpSky);
		mpWindow->removeListener(mpSky);
		mpSky->remove();
		delete mpSky;
		mpSky = nullptr;
	}

	LogManager::getSingletonPtr()->logMessage(LML_NORMAL, "Destruction paged geometry...");
	if (mpTrees != nullptr && mpTrees->getPageLoader() != nullptr)
	{
		delete mpTrees->getPageLoader();
		delete mpTrees;
		mpTrees = nullptr;
	}

	LogManager::getSingletonPtr()->logMessage(LML_NORMAL, "Destruction water manager...");
	if (mpWater != nullptr)
	{
		delete mpWater;
		mpWater = nullptr;
	}

	LogManager::getSingletonPtr()->logMessage(LML_NORMAL, "Destruction lights manager...");
	if (mpLum != nullptr)
	{
		delete mpLum;
		mpLum = nullptr;
	}

	LogManager::getSingletonPtr()->logMessage(LML_NORMAL, "Destruction terrains manager...");
	if (mpTerrain != nullptr)
	{
		delete mpTerrain;
		mpTerrain = nullptr;
	}

	LogManager::getSingletonPtr()->logMessage(LML_NORMAL, "Destruction frame and window's event listener...");
	if (mpListener != nullptr)
	{
		delete mpListener;
		mpListener = nullptr;
	}

	LogManager::getSingletonPtr()->logMessage(LML_NORMAL, "Destruction CEGUI Manager...");
	if (mpCeguiMgr != nullptr)
	{
		delete mpCeguiMgr;
		mpCeguiMgr = nullptr;
	}

	LogManager::getSingletonPtr()->logMessage(LML_NORMAL, "Destruction Bullet...");
	delete mpPhysicMgr;

	LogManager::getSingletonPtr()->logMessage(LML_NORMAL, "Closing window...");
	if (mpWindow != nullptr)
	{
		mpWindow->destroy();
	}

	LogManager::getSingletonPtr()->logMessage(LML_NORMAL, "Destruction Ogre...");
	if(mpRoot != nullptr)
	{
		delete mpRoot;
		mpRoot = nullptr;
	}

	LogManager::getSingletonPtr()->logMessage(LML_NORMAL, "Destruction FMOD...");
	if (mpSoundMgr != nullptr)
	{
		delete mpSoundMgr;
		mpSoundMgr = nullptr;
	}

	/* Destruction des singletons */
	LogManager::getSingletonPtr()->logMessage(LML_NORMAL, "Destruction singletons...");

	IDMgr::destroy();
	LogManager::getSingletonPtr()->destroyLog(LogManager::getSingletonPtr()->getDefaultLog());
	delete LogManager::getSingletonPtr();
}

void AppMain::start()
{
	LogManager::getSingletonPtr()->logMessage(LML_NORMAL, "Starting FMOD...");
	mpSoundMgr = LOP_NEW FMODSoundMgr();

	LogManager::getSingletonPtr()->logMessage(LML_NORMAL, "Starting Ogre...");
	if(!initOGRE()) //Démarrage de Ogre
	{
		throw ExceptionPerso("Erreur dans AppMain::initOGRE(), mais Ogre ne parait pas avoir levé une exception.", FATAL);
	}

	LogManager::getSingletonPtr()->logMessage(LML_NORMAL, "Starting Bullet...");
	mpPhysicMgr = LOP_NEW PhysicMgr();
	if (!mpPhysicMgr->initBullet()) //Physique et collision
	{
		throw ExceptionPerso("Erreur lors de l'initialisation du moteur Bullet.", FATAL);
	}

	LogManager::getSingletonPtr()->logMessage(LML_NORMAL, "Create basics...");
	if (!createBase())
	{
		throw ExceptionPerso("Erreur lors de la création des éléments basiques du rendu", FATAL);
	}

	LogManager::getSingletonPtr()->logMessage(LML_NORMAL, "Create CEGUI interface...");
	mpCeguiMgr = LOP_NEW CeguiMgr();

	LogManager::getSingletonPtr()->logMessage(LML_NORMAL, "Create window's event listener...");
	mpListener = LOP_NEW InputListener(mpWindow, mpCam, mpCeguiMgr);   //Ecouteur d'évènement pour les entrées utilisateurs
	mpRoot->addFrameListener(mpListener);

	/* Création du singleton gestionnaire ID */
	IDMgr::getInstance();

	LogManager::getSingletonPtr()->logMessage(LML_NORMAL, "Loading scene elements...");
	if(!createScene())  //Création de la scène
	{
		throw ExceptionPerso("Erreur lors de la création de la scène.", ERREUR);
	}

	mpRoot->addFrameListener(mpSoundMgr);

	mpSoundMgr->loadSound("media/fmod/music/ambiance_ballade.mp3", "ballade");

	LogManager::getSingletonPtr()->logMessage(LML_NORMAL, "Starting rendering loop...");
	infiniteLoop(); //Boucle de rendu*/
}

bool AppMain::initOGRE()
{
	Ogre::ConfigFile config;    //Gestionnaire de fichier de config Ogre

#ifdef _DEBUG
	mpRoot = OGRE_NEW Root("plugins_d.cfg", "ogre.cfg");
	config.load("resources_d.cfg");
#else
	mpRoot = OGRE_NEW Root("plugins.cfg", "ogre.cfg");
	config.load("resources.cfg");
#endif

	LogManager::getSingletonPtr()->setDefaultLog(LogManager::getSingletonPtr()->getLog("LoP.log"));

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
	mpWindow = mpRoot->initialise(true, "Light of Paladin");

	/* Niveau de mipMap (1x1) */
	TextureManager::getSingleton().setDefaultNumMipmaps(MIP_UNLIMITED);
	ResourceGroupManager::getSingleton().initialiseAllResourceGroups(); //On charge tout et on calcule les niveaux de mipMap

	/* Création du scène manager */
	mpSceneMgr = mpRoot->createSceneManager("OctreeSceneManager", "SceneManager");

	/* Activation du filtrage anisotropique, niveau 16 */
	MaterialManager::getSingleton().setDefaultTextureFiltering(TFO_ANISOTROPIC);
	MaterialManager::getSingleton().setDefaultAnisotropy(16);

	return true;
}

bool AppMain::createScene()
{
	if(!(createSky() && createTerrain() && createLight() && createObject() && createPersonnage()))
	{
		return false;
	}

	return true;
}

bool AppMain::createBase()
{
	mpSceneMgr->setShadowTechnique(SHADOWTYPE_TEXTURE_ADDITIVE_INTEGRATED);

	mpCam = mpSceneMgr->createCamera("Camera");
	mpCam->setPosition(Vector3(0.0, 10.0, 0.0));
	mpCam->lookAt(Vector3(10.0, 10.0, 10.0));
	mpCam->setNearClipDistance(2.0f);
	mpCam->setCastShadows(false);

	if (mpRoot->getRenderSystem()->getCapabilities()->hasCapability(RSC_INFINITE_FAR_PLANE))
	{
		mpCam->setFarClipDistance(TAILLE_MONDE);
	}
	else
	{
		mpCam->setFarClipDistance(2000);
	}

	Viewport *vp = mpWindow->addViewport(mpCam);
	vp->setBackgroundColour(ColourValue(0.0, 0.0, 0.0, 1.0));
	mpCam->setAspectRatio(vp->getActualWidth()/Real(vp->getActualHeight()));

	return true;
}

bool AppMain::createSky()
{
	mpSky = LOP_NEW SkyX::SkyX(mpSceneMgr, LOP_NEW SkyX::BasicController());
	mpSky->create();

	mpRoot->addFrameListener(mpSky);
	mpWindow->addListener(mpSky);

	// Couche de nuages basique
	mpSky->getCloudsManager()->add(SkyX::CloudLayer::Options());

	mpSky->getMoonManager()->setMoonSize(0.3f);

	mpSky->setTimeMultiplier(0.02f);

	return true;
}

bool AppMain::createTerrain()
{
	Light *pSoleil = mpSceneMgr->createLight("soleil");
	pSoleil->setType(Light::LT_DIRECTIONAL);
	pSoleil->setDirection(Vector3(0.0f, -1.0f, 3.0f));
	pSoleil->setDiffuseColour(ColourValue(0.8f, 0.68f, 0.73f));
	pSoleil->setSpecularColour(ColourValue(0.8f, 0.68f, 0.73f));

	mpTerrain = LOP_NEW TerrainMgr(TAILLE_IMG_HEIGHTMAP, TAILLE_MONDE, mpSceneMgr, mpSceneMgr->getLight("soleil"), mpCam, mpCam->getViewport(), mpRoot);

	//boost::thread ThTerrainCreationHavok(&AppMain::createTerrainHavokMultiThreaded, this);

	mpRoot->addFrameListener(mpTerrain->getPtrChunk());

	mpWater = LOP_NEW WaterMgr(mpSceneMgr, mpCam, mpWindow->getViewport(0), mpSky);
	mpRoot->addFrameListener(mpWater);

	mpWater->setHauteur(150.0f);

	// Create water
	mpWater->create();

	mpTrees = LOP_NEW Forests::PagedGeometry();

	mpTrees->setCamera(mpCam);
	mpTrees->setPageSize(50);
	mpTrees->setBounds(Forests::TBounds(0, 0, 10000, 10000));

	mpTrees->addDetailLevel<Forests::BatchPage>(500, 50);
	mpTrees->addDetailLevel<Forests::ImpostorPage>(1000, 100);

	//Create a new TreeLoader3D object first
	Forests::TreeLoader3D *treeLoader = LOP_NEW Forests::TreeLoader3D(mpTrees, Forests::TBounds(0, 0, 10000, 10000));

	Entity *pEnt1 = mpSceneMgr->createEntity("tree", "bouleau.mesh"), *pEnt2 = mpSceneMgr->createEntity("lila", "lila.mesh"), *pEnt3 = mpSceneMgr->createEntity("apple tree", "pommier.mesh");

	Entity* vege[] = {pEnt1, pEnt2, pEnt3};

	float x, y, z, yaw, scale;
	int t;
	for (int i = 0; i < 100; i++){
		yaw = Math::RangeRandom(0.0f, 360.0f);
		x = Math::RangeRandom(0.0f, 10000.0f);
		z = Math::RangeRandom(0.0f, 10000.0f);
		scale = Math::RangeRandom(0.2f, 0.9f);
		t = static_cast<int>(Math::RangeRandom(0, 3));
		y = mpTerrain->getTerrains()->getTerrain(0, 0)->getHeightAtWorldPosition(x, 5000.0f, z);

		if(y > 300.0f)
		{
			treeLoader->addTree(vege[t], Vector3(x, y, z), Degree(yaw), scale);
		}
	}

	mpTrees->setPageLoader(treeLoader);

	return true;
}

bool AppMain::createObject()
{

	return true;
}

bool AppMain::createPersonnage()
{
	Entity *pEnt1 = mpSceneMgr->createEntity("pingouin", "penguin.mesh");
	SceneNode *pNodePeng = mpSceneMgr->getRootSceneNode()->createChildSceneNode("nodePengouin", Vector3(1200.0f, 1500.0f, 1200.0f));
	pNodePeng->attachObject(pEnt1);

	Entity *pEnt2 = mpSceneMgr->createEntity("rylai", "rylai.mesh");
	SceneNode *pNodeRylai = pNodePeng->createChildSceneNode("nodeRylai", Vector3(-23.0f, 8.0f, 20.0f));
	pNodeRylai->pitch(Degree(45.0f));
	pNodeRylai->scale(Vector3(10.0, 10.0, 10.0));
	pNodeRylai->attachObject(pEnt2);

	Entity *pEnt3 = mpSceneMgr->createEntity("palace", "palace.mesh");
	SceneNode *pNodeTux = mpSceneMgr->getRootSceneNode()->createChildSceneNode("nodePalace", Vector3(800.0f, 500.0f, 800.0f));
	pNodeTux->setScale(10.0f, 10.0f, 10.0f);
	pNodeTux->attachObject(pEnt3);

	ParticleSystem* sunParticle = mpSceneMgr->createParticleSystem("Boule de feu", "Particule/FireBall");
	SceneNode* particleNode = pNodePeng->createChildSceneNode("ParticleFire");
	particleNode->attachObject(sunParticle);
	particleNode->setPosition(0, 30, 0);

	int stat[ESTATMAX]={0};
//	ajoutPersonnage(pNodePeng, "Samuel", stat, 1, 0, Vector3(0.0f), Vector3(0.0f));

	return true;
}

bool AppMain::createLight()
{
	mpLum = LOP_NEW LightMgr(mpSceneMgr, mpSceneMgr->getLight("soleil"), mpSky, mpWater, ColourValue(0.8f, 0.8f, 0.8f));

	mpRoot->addFrameListener(mpLum);

	return true;
}

void AppMain::infiniteLoop()
{
	Personnage *pSam = nullptr;
	bool bSens = true;

	GameConsole* p = LOP_NEW GameConsole(mpCeguiMgr);
	p->CreateCEGUIWindow();

	//test

	Epee *eppee = new Epee(static_cast<Ogre::SceneNode*>(mpSceneMgr->getEntity("pingouin")->getParentNode()), EShape::BOX, 200);

	eppee->setMasse(55);

	eppee->createMotionState(btQuaternion(0, 0, 0, 1), btVector3(1200, 1500, 1200));

	eppee->createBody();

	mpPhysicMgr->getWorld().addRigidBody(eppee->getBodyPtr());


	try
	{
		pSam = getPersonnage("Samuel");
	}
	catch(std::exception& e)
	{
		e.what();
	}

	//test

	static boost::chrono::milliseconds const ref(1000);

	unsigned int fps = 0;

	boost::chrono::system_clock::time_point tempsDebut = boost::chrono::system_clock::now();
	boost::chrono::system_clock::time_point tempsFin;

	while (true)
	{
		WindowEventUtilities::messagePump();

		if (!mpRoot->renderOneFrame())
		{
			return;
		}

		mpTrees->update();

		
		//test
		btTransform trans;
		eppee->getMotionState().getWorldTransform(trans);

		btVector3 btVect = trans.getOrigin();

		eppee->getNode()->setPosition(btVect.getX(), btVect.getY(), btVect.getZ());

		mpPhysicMgr->getWorld().stepSimulation(5, 10);
		//test

		tempsFin = boost::chrono::system_clock::now();

		if (boost::chrono::duration_cast<boost::chrono::milliseconds>(tempsFin - tempsDebut) < ref)
		{
			fps++;
		} 
		else
		{
			std::cout << fps << std::endl;
			fps=0;
			tempsDebut = boost::chrono::system_clock::now();
		}
	}
}

bool AppMain::ajoutPersonnage(Ogre::SceneNode *pNoeud, std::string const& nom, int stat[EStat::ESTATMAX], int niveau, int XP, Ogre::Vector3 const& position, Ogre::Vector3 const& rotation)
{
	//Personnage *pPersonnage =  LOP_NEW Personnage(pNoeud, stat, true, nom, niveau, XP);

	std::pair<std::map<std::string, Personnage*>::iterator, bool> retVal;

	//retVal = mmapPersonnages.insert(std::pair<std::string, Personnage*>(nom, pPersonnage));

	return retVal.second;
}

Personnage* AppMain::getPersonnage(std::string const& nom) const
{
	std::map<std::string, Personnage*>::const_iterator it;
	it = mmapPersonnages.find(nom);

	if (it != mmapPersonnages.end())
	{
		return it->second;
	}
	else
	{
		std::string mesg = nom+": Ce personnage n'existe pas. Opération abandonnée.";
		throw ExceptionPerso(mesg.c_str(), INFO);
	}
}

FMODSoundMgr* AppMain::getFMODSoundMgr() const
{
	return mpSoundMgr;
}

AppMain* AppMain::getInstance()
{
	if (mpsInstanceUnique == nullptr)
	{
		mpsInstanceUnique = LOP_NEW AppMain;
	}
	
	return mpsInstanceUnique;
}

void AppMain::destroy()
{
		delete mpsInstanceUnique;
		mpsInstanceUnique = nullptr;
}
