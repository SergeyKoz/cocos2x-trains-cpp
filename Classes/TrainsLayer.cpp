#include "TrainsLayer.h"

// on "init" you need to initialize your instance
bool TrainsLayer::init()
{ 
    if ( !Layer::init() )
    {
        return false;
    }
		/*
		for c = 1, #Game.Trains do
            Game.Trains[c]:Init()
        end
		*/

	Director::getInstance()->getScheduler()->schedule(CC_CALLBACK_1(TrainsLayer::trainsMoveCallback, this), this, 0.05f, false, "trainsMoving");

	/*Director::getInstance()->getScheduler()->schedule([&](float dt) {
		log("scheduled");
	}, this, 0.5f, false, "trainsMowing");*/


    return true;
}

void TrainsLayer::onEnter()
{
	Layer::onEnter();

	Field *Game = Field::getInstance();
}

void TrainsLayer::trainsMoveCallback(float dt)
{

	Field *Game = Field::getInstance();

	for (int i = 0; i < Game->trains.size(); i++) {
		Game->trains[i].Move();
	}
	
	/*
	 local Trains = GameField:Instance().Trains
    --local x
    --local x = os.clock()              
    for c = 1, #Trains do
        --x = os.clock() 
        Trains[c]:Move() 
        --print(string.format("Train ".. c .. ": %.2f\n", os.clock() - x))
    end
	*/
	//log("scheduled");
}
