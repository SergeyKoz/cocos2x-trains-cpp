#include "MapLayer.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool MapLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    /*auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(MapLayer::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(
		origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
		origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);*/

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("My Trains", "fonts/Marker Felt.ttf", 16);
    
    // position the label on the center of the screen
    label->setPosition(
		Vec2(origin.x + visibleSize.width/2,
        origin.y + visibleSize.height - label->getContentSize().height));
	label->setColor(Color3B::BLACK);

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    //auto sprite = Sprite::create("rails.png");

    // position the sprite on the center of the screen
    //sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    //this->addChild(sprite, 0);
    
    return true;
}

void MapLayer::onEnter()
{
	Layer::onEnter();

	// Register Touch Event
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(MapLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(MapLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(MapLayer::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	test();
}

bool MapLayer::onTouchBegan(Touch* touch, Event* event)
{
	Field *Game = Field::getInstance();

	startLocation = touch->getLocation();
	Vec2 pos = this->getPosition();

	if (Game->constuctionMode == Rails || Game->constuctionMode == Semafores) {
		MapPoint c = {
			(int)round((-pos.x + startLocation.x) / (Game->scale * 10)),
			(int)round((-pos.y + startLocation.y) / (Game->scale * 10))
		};

		if (Game->constuctionMode == Rails) {
			if (path.Init(c)) {
				touchMode = BuildRails;
			}
		}

		if (Game->constuctionMode == Semafores) {			
			MapIndent d = {
				c.x - ((-pos.x + startLocation.x) / (Game->scale * 10)),
				c.y - ((-pos.y + startLocation.y) / (Game->scale * 10))
			};

			if (semaphore.Show(c, d)) {
				touchMode = SemaphoreShow;
			}
		}

	}

	return true;
}

void MapLayer::onTouchMoved(Touch* touch, Event* event)
{
	if (startLocation.x != -1 && startLocation.y != -1) {
		Field *Game = Field::getInstance();

		Vec2 loc = touch->getLocation();
		Vec2 pos = this->getPosition();

		Vec2 p;
		if (touchMode == Move) {
			p = { pos.x + loc.x - startLocation.x, pos.y + loc.y - startLocation.y };
			p.x = p.x < 0 ? p.x : 0;
			p.y = p.y < 0 ? p.y : 0;
			this->setPosition(p);
		}

		if (touchMode == BuildRails || touchMode == SemaphoreShow) {
			MapPoint p = { (int)round((-pos.x + loc.x) / (Game->scale * 10)), (int)round((-pos.y + loc.y) / (Game->scale * 10)) };
			if (touchMode == BuildRails) {
				path.Show(p);
			}

			if (touchMode == SemaphoreShow) {
				MapIndent d = {
					p.x - ((-pos.x + loc.x) / (Game->scale * 10)),
					p.y - ((-pos.y + loc.y) / (Game->scale * 10))
				};

				if (!semaphore.Show(p, d)) {
					semaphore.Hide();
				}
			}
		}

		startLocation = loc;
	}
}

void MapLayer::onTouchEnded(Touch* touch, Event* event)
{
	Field *Game = Field::getInstance();
	if (touchMode == BuildRails) {
		path.Set();
	}

	if (touchMode == SemaphoreShow) {
		semaphore.Set();
	}

	touchMode = Move;
	startLocation = { -1, -1 };
}

void MapLayer::test() {

	Field *Game = Field::getInstance();
	int x, y;

	//Game->cells[18][15].Connect(&Game->cells[15][14], 1);
	string command = "path --add --path=[{\"from\":{\"x\":18,\"y\":15},\"to\":{\"x\":15,\"y\":14},\"point\":1}]";
	Cmd::Exec(command);

	/*
	int d = 1;
	for (int i = 0; i < 1; i++) {
		for (int j = 0; j < 1; j++) {
			x = (j + 1) * 50 - 50;
			y = (i + 1) * 25 - 25;
		}
	}*/

}
