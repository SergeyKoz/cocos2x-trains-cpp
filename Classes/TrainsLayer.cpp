#include "TrainsLayer.h"
#include "MenuLayer.h"

// on "init" you need to initialize your instance
bool TrainsLayer::init()
{ 
    if ( !Layer::init() )
    {
        return false;
    }

	Director::getInstance()->getScheduler()->schedule(CC_CALLBACK_1(TrainsLayer::trainsMoveCallback, this), this, 0.2f, false, "trainsMoving");
    return true;
}

void TrainsLayer::onEnter()
{
	Layer::onEnter();

	Field *Game = Field::getInstance();

	for (int i = 0; i < Game->trains.size(); i++) {
		Game->trains[i].init();
	}

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(TrainsLayer::onContactBegin, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
}

void TrainsLayer::trainsMoveCallback(float dt)
{
	Field *Game = Field::getInstance();

	if (Game->gameMode == GameMode::ModeOn) {
		/*std::chrono::steady_clock::time_point start, end;
		start = std::chrono::steady_clock::now();*/
		for (int i = 0; i < Game->trains.size(); i++) {
			Game->trains[i].move();
		}	
		/*end = std::chrono::steady_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;
		CCLOG("%f callcack seconds", elapsed_seconds.count());*/
	}
}

bool TrainsLayer::onContactBegin(PhysicsContact &contact)
{
	try {
		PhysicsBody *a = contact.getShapeA()->getBody();
		PhysicsBody *b = contact.getShapeB()->getBody();
		if (a->getCollisionBitmask() != b->getCollisionBitmask()) {
			throw collision;			
		}
	}
	catch (exception& e)
	{
		CCLOG("< %s", e.what());
		Field *game = Field::getInstance();
		game->gameMode = GameMode::ModeOff;

		MenuLayer *menu = (MenuLayer*)game->menuLayer;
		menu->PauseButton->enable(false);
	}	
	return true;
}
