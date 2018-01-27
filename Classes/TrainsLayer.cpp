#include "TrainsLayer.h"

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
}

void TrainsLayer::trainsMoveCallback(float dt)
{
	Field *Game = Field::getInstance();

	/*std::chrono::steady_clock::time_point start, end;

	start = std::chrono::steady_clock::now();*/
	for (int i = 0; i < Game->trains.size(); i++) {
		Game->trains[i].move();
	}
	
	/*end = std::chrono::steady_clock::now();

	std::chrono::duration<double> elapsed_seconds = end - start;
	CCLOG("%f seconds", elapsed_seconds.count());*/
}
