#include "GestionnaireTerrain.h"
#include "GestionnaireID.h"
#include "ExceptionPerso.h"

#include "Chunk.h"

#include <OgreTerrainGroup.h>
#include <OgreRoot.h>

using namespace Ogre;

GestionnaireTerrain::GestionnaireTerrain(unsigned int tailleHeightMap, unsigned int tailleMonde, SceneManager *pSceneMgr, Light *mpSoleil, Camera *pCam, Viewport *pViewPort, Root *pRoot, hkpWorld *pHavokWorld)
{
    mpSceneMgr = pSceneMgr;
    mTailleTerrain = tailleMonde;
    mTailleHeightMap = tailleHeightMap;
	mpRoot = pRoot;
	mpHavokWorld = pHavokWorld;

    mpIDGestion = GestionnaireID::getInstance();

	mpChunksMgn = new ChunkManager(pCam, this, pHavokWorld);

    mpOptions = OGRE_NEW TerrainGlobalOptions();
    mpOptions->setMaxPixelError(1);

	if (mpRoot->getRenderSystem()->getCapabilities()->hasCapability(RSC_INFINITE_FAR_PLANE))
	{
		mpOptions->setCompositeMapDistance(50000);
	}
	else
	{
		mpOptions->setCompositeMapDistance(25000);
	}
    mpOptions->setLightMapDirection(mpSoleil->getDerivedDirection());
    mpOptions->setCompositeMapAmbient(mpSceneMgr->getAmbientLight());
    mpOptions->setCompositeMapDiffuse(mpSoleil->getDiffuseColour());

    mpTerrainGroup = OGRE_NEW TerrainGroup(mpSceneMgr, Terrain::Alignment::ALIGN_X_Z, tailleHeightMap, static_cast<Real>(tailleMonde));
    mpTerrainGroup->setOrigin(Vector3(tailleMonde/2.0f, 0.0f, tailleMonde/2.0f));
    mpTerrainGroup->setFilenameConvention("data","ter");

    Terrain::ImportData& imp = mpTerrainGroup->getDefaultImportSettings();
	imp.inputBias=0.0f;
    imp.inputScale = 1200.0f;
    imp.minBatchSize = 65;
    imp.maxBatchSize = 129;

    imp.layerList.resize(TEXTURE_MAX);
    imp.layerList[HERBE1].worldSize = 15;
    imp.layerList[HERBE1].textureNames.push_back("grass_green-01_diffusespecular.dds");
    imp.layerList[HERBE1].textureNames.push_back("grass_green-01_normalheight.dds");
	imp.layerList[HERBE2].worldSize = 15;
	imp.layerList[HERBE2].textureNames.push_back("grass_1024.jpg");
    imp.layerList[NEIGE1].worldSize = 15;
    imp.layerList[NEIGE1].textureNames.push_back("terrainsnow01.dds");
    imp.layerList[NEIGE1].textureNames.push_back("terrainsnow01_N.dds");

    int largeur = 1, longueur = 1;

    for(int x=0; x < largeur; x++)
    {
        for(int y=0; y < longueur; y++)
        {
            if (ResourceGroupManager::getSingleton().resourceExists(ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, mpTerrainGroup->generateFilename(x, y)))
            {
                mpTerrainGroup->defineTerrain(x, y, mpTerrainGroup->generateFilename(x, y));
                mpTerrainGroup->loadTerrain(x, y, true);
            } 
            else
            {
				Image img;
                img.load("island.bmp", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

                mpTerrainGroup->defineTerrain(x, y, &img);
                mpTerrainGroup->loadTerrain(x, y, true);
                mpTerrainGroup->getTerrain(x, y)->save("media/terrain/" + mpTerrainGroup->generateFilename(x, y));
            }
        }
    }

	TerrainLayerBlendMap *pBlendMap = mpTerrainGroup->getTerrain(0, 0)->getLayerBlendMap(NEIGE1);

	float *pBlend = pBlendMap->getBlendPointer();
	for (uint16 y=0; y < mpTerrainGroup->getTerrain(0, 0)->getLayerBlendMapSize(); y++)
	{
		for (uint16 x=0; x < mpTerrainGroup->getTerrain(0, 0)->getLayerBlendMapSize(); x++)
		{
			Real terrainX, terrainY;

			pBlendMap->convertImageToTerrainSpace(x, y, &terrainX, &terrainY);

			Real height = mpTerrainGroup->getTerrain(0, 0)->getHeightAtTerrainPosition(terrainX, terrainY);

			if (height >= 1050.0f)
			{
				*pBlend++ = 1.0f; //Neige au dessus de 1050
			}
			else if (height <= 825.0f)
			{
				*pBlend++ = 255.0f;    //Roche en dessous de 825
			}
			else
			{
				*pBlend++ = 255.0f + (height-825.0f)*(-255.0f/275.0f);   //Progressivement entre les deux
			}
		}
	}

	pBlendMap->dirty();
	pBlendMap->update();

    mpTerrainGroup->freeTemporaryResources();
}

GestionnaireTerrain::~GestionnaireTerrain()
{
	if (mpChunksMgn != nullptr)
	{
		delete mpChunksMgn;
		mpChunksMgn = nullptr;
	}

    if(mpTerrainGroup != nullptr)
    {
        OGRE_DELETE mpTerrainGroup;
        mpTerrainGroup = nullptr;
    }

    if (mpOptions != nullptr)
    {
        OGRE_DELETE mpOptions;
        mpOptions = nullptr;
    }
}

unsigned long GestionnaireTerrain::addTerrain(int x, int y, std::string const& nom)
{
    unsigned long id = mpIDGestion->newID();

    if (ResourceGroupManager::getSingleton().resourceExists(ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, mpTerrainGroup->generateFilename(x, y)))
    {
        mpTerrainGroup->defineTerrain(x, y, mpTerrainGroup->generateFilename(x, y));
        mpTerrainGroup->loadTerrain(x, y, true);
    } 
    else
    {
        Image img;
        img.load(nom, ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

        mpTerrainGroup->defineTerrain(x, y, &img);
        mpTerrainGroup->loadTerrain(x, y, true);
        mpTerrainGroup->getTerrain(x, y)->save("media/" + mpTerrainGroup->generateFilename(x, y));
    }

    std::pair<std::map<unsigned long, std::pair<int, int>>::iterator, bool> cdeVerif = mID_XY.insert(std::make_pair(id, std::make_pair(x, y)));

    assert(cdeVerif.second);

    mpTerrainGroup->getTerrain(x, y)->freeTemporaryResources();

    return id;
}

TerrainGroup* GestionnaireTerrain::getTerrains() const
{
    return mpTerrainGroup;
}

TerrainGlobalOptions* GestionnaireTerrain::getOptions() const
{
    return mpOptions;
}

ChunkManager* GestionnaireTerrain::getPtrChunk()
{
	return mpChunksMgn;
}
