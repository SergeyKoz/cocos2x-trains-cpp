#include "GameMapScene.h"

USING_NS_CC;

Scene* GameMapScene::createScene()
{
	//int d = 10 * Field::getInstance()->scale;

    auto scene = Scene::createWithPhysics();

	Field::getInstance()->scene = scene;

	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	
	auto BackgroundLayer = BackgroundLayer::create();
	scene->addChild(BackgroundLayer);

	auto MenuLayer = MenuLayer::create();
	Field::getInstance()->menuLayer = MenuLayer;
	scene->addChild(MenuLayer, ZIndexMenu);

	auto MapLayer = MapLayer::create();
	Field::getInstance()->mapLayer = MapLayer;
	scene->addChild(MapLayer);

	auto TrainsLayer = TrainsLayer::create();
	Field::getInstance()->trainsLayer = TrainsLayer;
	scene->addChild(TrainsLayer);

    // return the scene
    return scene;
}