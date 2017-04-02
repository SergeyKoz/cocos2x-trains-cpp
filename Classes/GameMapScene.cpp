#include "GameMapScene.h"

USING_NS_CC;

Scene* GameMapScene::createScene()
{

	int d = 10 * Field::getInstance()->scale;

    // 'scene' is an autorelease object
    auto scene = Scene::create();

	auto BackgroundLayer = MapBackgroundLayer::create();
	scene->addChild(BackgroundLayer);

    // 'layer' is an autorelease object
	auto layer = GameMapLayer::create();
	scene->addChild(layer);

	auto TrainsLayer = MapTrainsLayer::create();
	Field::getInstance()->trainsLayer = TrainsLayer;
	scene->addChild(TrainsLayer);

    // return the scene
    return scene;
}