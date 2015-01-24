#include <Ogre.h>
#include <OgreTerrainGroup.h>
#include <OgreFileSystemLayer.h>
#include <OgreImage.h>

#include <cstringt.h>

#include "GestionnaireID.h"
#include "GestionnaireTerrain.h"
#include "ExceptionPerso.h"

using namespace Ogre;

GestionnaireTerrain::GestionnaireTerrain(unsigned int tailleHeightMap, unsigned int tailleTerrain, SceneManager *pSceneMgr, Light *mpSoleil, Camera *pCam, Viewport *pViewPort)
{
    mpSceneMgr = pSceneMgr;
    mTailleTerrain = tailleTerrain;
    mTailleHeightMap = tailleHeightMap;
    mpOptions = nullptr;
    mpTerrainGroup = nullptr;
    mpIDGestion = nullptr;

    mpIDGestion = GestionnaireID::getInstance();

    mpOptions = OGRE_NEW TerrainGlobalOptions();
    mpOptions->setMaxPixelError(4);
    mpOptions->setCompositeMapDistance(20000);
    mpOptions->setLightMapDirection(mpSoleil->getDerivedDirection());
    mpOptions->setCompositeMapAmbient(mpSceneMgr->getAmbientLight());
    mpOptions->setCompositeMapDiffuse(mpSoleil->getDiffuseColour());

    mpTerrainGroup = OGRE_NEW TerrainGroup(mpSceneMgr, Terrain::Alignment::ALIGN_X_Z, tailleHeightMap, static_cast<Real>(tailleTerrain));
    mpTerrainGroup->setOrigin(Vector3::ZERO);
    mpTerrainGroup->setFilenameConvention("data","ter");

    Terrain::ImportData& imp = mpTerrainGroup->getDefaultImportSettings();
	imp.inputBias=0.0f;
    imp.inputScale = 2000.0f;
    imp.minBatchSize = 65;
    imp.maxBatchSize = 129;

    imp.layerList.resize(2);
    imp.layerList[0].worldSize = 140;
    imp.layerList[0].textureNames.push_back("grass_green-01_diffusespecular.dds");
    imp.layerList[0].textureNames.push_back("grass_green-01_normalheight.dds");
    imp.layerList[1].worldSize = 120;
    imp.layerList[1].textureNames.push_back("terrainsnow01.dds");
    imp.layerList[1].textureNames.push_back("terrainsnow01_N.dds");

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
				int num = x*largeur + y+1;
				std::string name;

				if (num < 10)
				{
					name = "island_00" + std::to_string(num) + ".bmp";
				} 
				else
				{
					name = "island_0" + std::to_string(num) + ".bmp";
				}

				if(!ResourceGroupManager::getSingleton().resourceExists(ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, name))
				{
					throw ExceptionPerso(("HeightMap:" + name + " introuvable.").c_str(), FATAL);
				}

				Image img;
                img.load("island.bmp", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

                mpTerrainGroup->defineTerrain(x, y, &img);
                mpTerrainGroup->loadTerrain(x, y, true);
                mpTerrainGroup->getTerrain(x, y)->save("media/terrain/" + mpTerrainGroup->generateFilename(x, y));
            }
        }
    }

	TerrainLayerBlendMap *pBlendMap = mpTerrainGroup->getTerrain(0, 0)->getLayerBlendMap(1);

	float *pBlend = pBlendMap->getBlendPointer();
	for (uint16 y=0; y < mpTerrainGroup->getTerrain(0, 0)->getLayerBlendMapSize(); y++)
	{
		for (uint16 x=0; x < mpTerrainGroup->getTerrain(0, 0)->getLayerBlendMapSize(); x++)
		{
			Real terrainX, terrainY;

			pBlendMap->convertImageToTerrainSpace(x, y, &terrainX, &terrainY);

			Real height = mpTerrainGroup->getTerrain(0, 0)->getHeightAtTerrainPosition(terrainX, terrainY);

			if (height >= 1800.0f)
			{
				*pBlend++ = 1; //Neige au dessus de 1500
			}
			else if (height <= 1350.0f)
			{
				*pBlend++ = 255;    //Roche en dessous de 1200
			}
			else
			{
				*pBlend++ = 255 + (height-1350)*(-255/450);   //Progressivement entre les deux
			}
		}
	}

	pBlendMap->dirty();
	pBlendMap->update();

    mpTerrainGroup->freeTemporaryResources();
}

GestionnaireTerrain::~GestionnaireTerrain()
{
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

    if (mpIDGestion != nullptr)
    {
        mpIDGestion = nullptr;
    }
}

unsigned long GestionnaireTerrain::addTerrain(int x, int y, std::string nom)
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

TerrainLayerBlendMap* GestionnaireTerrain::getBlendMap(unsigned long id) const
{
    int x = mID_XY.find(id)->second.first;
    int y = mID_XY.find(id)->second.second;

    return mpTerrainGroup->getTerrain(x, y)->getLayerBlendMap(1);
}

std::pair<int, int> GestionnaireTerrain::getXYFromID(unsigned long id) const
{
    std::map<unsigned long, std::pair<int, int>>::const_iterator it = mID_XY.find(id);

    if (it == mID_XY.end())
    {
        throw ExceptionPerso("Terrain introuvable, id:" + id, INFO);
    }

    return it->second;
}