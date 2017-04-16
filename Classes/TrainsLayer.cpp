#include "TrainsLayer.h"

// on "init" you need to initialize your instance
bool TrainsLayer::init()
{ 
    if ( !Layer::init() )
    {
        return false;
    }
    // to do

    return true;
}

/*void TrainsLayer::onEnter()
{
	Layer::onEnter();

	//Path* PathFinder = new Path();

	// Register Touch Event
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(TrainsLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(TrainsLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(TrainsLayer::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	test();
}*/

/*bool TrainsLayer::onTouchBegan(Touch* touch, Event* event)
{
	Field *Game = Field::getInstance();
	
	startLocation = touch->getLocation();
	Vec2 LayerPosition = this->getPosition();

	int cx = LayerPosition.x;
	int cy = LayerPosition.y;
		
	if (Game->constuctionMode == Rails){

		cx = round((-cx + startLocation.x) / (Game->scale * 10));
		cy = round((-cy + startLocation.y) / (Game->scale * 10));

		//MapPoint Point = { cx, cy };	
		//if (PathFinder.Init(Point)) {
		if (PathFinder.Init({ cx, cy })) {
			touchMode = BuildRails;
		}
		
		//touchBeginPoint = { touch->getLocation().x, touch->getLocation().y };
		//Vec2 touchBeginPoint = touch->getLocation();

	}

	if (Game->constuctionMode == Semafores){

	}

	return true;
}

void TrainsLayer::onTouchMoved(Touch* touch, Event* event)
{
	if (startLocation.x != -1 && startLocation.y != -1){
		Field *Game = Field::getInstance();

		Vec2 location = touch->getLocation();
		Vec2 LayerPosition = this->getPosition();

		float cx = LayerPosition.x;
		float cy = LayerPosition.y;

		float px, py;

		if (touchMode == Move){
			px = cx + location.x - startLocation.x;
			py = cy + location.y - startLocation.y;

			px = px < 0 ? px : 0;
			py = py < 0 ? py : 0;
			this->setPosition({px, py});
		}

		//Vec2 touchBeginPoint = touch->getLocation();
		//touchBeginPoint = { touch->getLocation().x, touch->getLocation().y };

		if (touchMode == BuildRails || touchMode == SemaphoreShow){
			px = round((-cx + location.x) / (Game->scale * 10));
			py = round((-cy + location.y) / (Game->scale * 10));

			//MapPoint Point = {px, py};

			if (touchMode == BuildRails){
				//PathFinder.Show(Point);
				PathFinder.Show({ (int)px, (int)py });
			}
		}

		startLocation = location;
	}
}

void TrainsLayer::onTouchEnded(Touch* touch, Event* event)
{
	Field *Game = Field::getInstance();
	if (touchMode == BuildRails){
		PathFinder.Set();
	}

	if (touchMode == SemaphoreShow){

	}

	touchMode = Move;
	startLocation = { -1, -1 };
}*/

/*void TrainsLayer::test(){

	Field *Game = Field::getInstance();
	int x, y;

	Game->cells[18][15].Connect(&Game->cells[15][14], 1);
	
	/ *
	int d = 1;
	for (int i = 0; i < 1; i++){
		for (int j = 0; j < 1; j++){
			x = (j + 1) * 50 - 50;
			y = (i + 1) * 25 - 25;
		}
	}* /

}*/