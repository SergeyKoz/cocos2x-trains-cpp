#include "GameMapScene.h"

USING_NS_CC;

Scene* GameMapScene::createScene()
{
	//int d = 10 * Field::getInstance()->scale;

    auto scene = Scene::create();

	auto BackgroundLayer = BackgroundLayer::create();
	scene->addChild(BackgroundLayer);

	auto Maplayer = MapLayer::create();
	Field::getInstance()->mapLayer = Maplayer;
	scene->addChild(Maplayer);

	auto TrainsLayer = TrainsLayer::create();
	Field::getInstance()->trainsLayer = TrainsLayer;
	scene->addChild(TrainsLayer);

    // return the scene
    return scene;
}