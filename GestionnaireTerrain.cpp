#include <Ogre.h>
#include <OgreTerrainGroup.h>
#include <OgreFileSystemLayer.h>

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

    mpIDGestion = new GestionnaireID(12000);

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
    imp.inputScale = 1000;
    imp.minBatchSize = 33;
    imp.maxBatchSize = 65;

    imp.layerList.resize(2);
    imp.layerList[0].worldSize = 200;
    imp.layerList[0].textureNames.push_back("grass_green-01_diffusespecular.dds");
    imp.layerList[0].textureNames.push_back("grass_green-01_normalheight.dds");
    imp.layerList[1].worldSize = 60;
    imp.layerList[1].textureNames.push_back("terrainsnow01.dds");
    imp.layerList[1].textureNames.push_back("terrainsnow01_N.dds");

        int largeur = 1, longueur = 1;

    for(int x = 0; x < largeur; x++)
    {
        for(int y = 0; y < longueur; y++)
        {
            if (ResourceGroupManager::getSingleton().resourceExists(ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, mpTerrainGroup->generateFilename(x, y)))
            {
                mpTerrainGroup->defineTerrain(x, y, mpTerrainGroup->generateFilename(x, y));
                mpTerrainGroup->loadTerrain(x, y, true);
            } 
            else
            {

                Image img;
                img.load("heighmap1.jpg", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

                if(x % 2 != 0)
                    img.flipAroundY();
                if(y % 2 != 0)
                    img.flipAroundX();

                mpTerrainGroup->defineTerrain(x, y, &img);
                mpTerrainGroup->loadTerrain(x, y, true);
                mpTerrainGroup->getTerrain(x, y)->save("media/" + mpTerrainGroup->generateFilename(x, y));
            }
        }
    }

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
        delete mpIDGestion;
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