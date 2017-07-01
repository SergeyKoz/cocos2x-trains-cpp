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
    //Size visibleSize = Director::getInstance()->getVisibleSize();
    //Vec2 origin = Director::getInstance()->getVisibleOrigin();
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
			Game->trainsLayer->setPosition(p);
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
	//int x, y;

	//Game->cells[18][15].Connect(&Game->cells[15][14], 1);
	string command = "path --add --path=[{\"from\":{\"x\":18,\"y\":15},\"to\":{\"x\":15,\"y\":14},\"point\":1}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"from\":{\"x\":38,\"y\":32},\"to\":{\"x\":39,\"y\":33},\"point\":5},{\"from\":{\"x\":37,\"y\":31},\"to\":{\"x\":38,\"y\":32},\"point\":5},{\"from\":{\"x\":36,\"y\":30},\"to\":{\"x\":37,\"y\":31},\"point\":5},{\"from\":{\"x\":35,\"y\":29},\"to\":{\"x\":36,\"y\":30},\"point\":5},{\"from\":{\"x\":34,\"y\":28},\"to\":{\"x\":35,\"y\":29},\"point\":5},{\"from\":{\"x\":33,\"y\":27},\"to\":{\"x\":34,\"y\":28},\"point\":5},{\"from\":{\"x\":32,\"y\":26},\"to\":{\"x\":33,\"y\":27},\"point\":5},{\"from\":{\"x\":31,\"y\":25},\"to\":{\"x\":32,\"y\":26},\"point\":5},{\"from\":{\"x\":30,\"y\":24},\"to\":{\"x\":31,\"y\":25},\"point\":5},{\"from\":{\"x\":29,\"y\":23},\"to\":{\"x\":30,\"y\":24},\"point\":5},{\"from\":{\"x\":28,\"y\":22},\"to\":{\"x\":29,\"y\":23},\"point\":5},{\"from\":{\"x\":27,\"y\":21},\"to\":{\"x\":28,\"y\":22},\"point\":5},{\"from\":{\"x\":26,\"y\":20},\"to\":{\"x\":27,\"y\":21},\"point\":5},{\"from\":{\"x\":25,\"y\":19},\"to\":{\"x\":26,\"y\":20},\"point\":5},{\"from\":{\"x\":24,\"y\":18},\"to\":{\"x\":25,\"y\":19},\"point\":5},{\"from\":{\"x\":23,\"y\":17},\"to\":{\"x\":24,\"y\":18},\"point\":5},{\"from\":{\"x\":22,\"y\":16},\"to\":{\"x\":23,\"y\":17},\"point\":5},{\"from\":{\"x\":19,\"y\":15},\"to\":{\"x\":22,\"y\":16},\"point\":5},{\"from\":{\"x\":18,\"y\":15},\"to\":{\"x\":19,\"y\":15},\"point\":4}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"from\":{\"x\":43,\"y\":34},\"to\":{\"x\":46,\"y\":33},\"point\":3},{\"from\":{\"x\":42,\"y\":34},\"to\":{\"x\":43,\"y\":34},\"point\":4},{\"from\":{\"x\":39,\"y\":33},\"to\":{\"x\":42,\"y\":34},\"point\":4}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"from\":{\"x\":48,\"y\":28},\"to\":{\"x\":48,\"y\":27},\"point\":2},{\"from\":{\"x\":48,\"y\":29},\"to\":{\"x\":48,\"y\":28},\"point\":2},{\"from\":{\"x\":47,\"y\":32},\"to\":{\"x\":48,\"y\":29},\"point\":2},{\"from\":{\"x\":46,\"y\":33},\"to\":{\"x\":47,\"y\":32},\"point\":3}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"from\":{\"x\":48,\"y\":5},\"to\":{\"x\":48,\"y\":4},\"point\":2},{\"from\":{\"x\":48,\"y\":6},\"to\":{\"x\":48,\"y\":5},\"point\":2},{\"from\":{\"x\":48,\"y\":7},\"to\":{\"x\":48,\"y\":6},\"point\":2},{\"from\":{\"x\":48,\"y\":8},\"to\":{\"x\":48,\"y\":7},\"point\":2},{\"from\":{\"x\":48,\"y\":9},\"to\":{\"x\":48,\"y\":8},\"point\":2},{\"from\":{\"x\":48,\"y\":10},\"to\":{\"x\":48,\"y\":9},\"point\":2},{\"from\":{\"x\":48,\"y\":11},\"to\":{\"x\":48,\"y\":10},\"point\":2},{\"from\":{\"x\":48,\"y\":12},\"to\":{\"x\":48,\"y\":11},\"point\":2},{\"from\":{\"x\":48,\"y\":13},\"to\":{\"x\":48,\"y\":12},\"point\":2},{\"from\":{\"x\":48,\"y\":14},\"to\":{\"x\":48,\"y\":13},\"point\":2},{\"from\":{\"x\":48,\"y\":15},\"to\":{\"x\":48,\"y\":14},\"point\":2},{\"from\":{\"x\":48,\"y\":16},\"to\":{\"x\":48,\"y\":15},\"point\":2},{\"from\":{\"x\":48,\"y\":17},\"to\":{\"x\":48,\"y\":16},\"point\":2},{\"from\":{\"x\":48,\"y\":18},\"to\":{\"x\":48,\"y\":17},\"point\":2},{\"from\":{\"x\":48,\"y\":19},\"to\":{\"x\":48,\"y\":18},\"point\":2},{\"from\":{\"x\":48,\"y\":20},\"to\":{\"x\":48,\"y\":19},\"point\":2},{\"from\":{\"x\":48,\"y\":21},\"to\":{\"x\":48,\"y\":20},\"point\":2},{\"from\":{\"x\":48,\"y\":22},\"to\":{\"x\":48,\"y\":21},\"point\":2},{\"from\":{\"x\":48,\"y\":23},\"to\":{\"x\":48,\"y\":22},\"point\":2},{\"from\":{\"x\":48,\"y\":24},\"to\":{\"x\":48,\"y\":23},\"point\":2},{\"from\":{\"x\":48,\"y\":25},\"to\":{\"x\":48,\"y\":24},\"point\":2},{\"from\":{\"x\":48,\"y\":26},\"to\":{\"x\":48,\"y\":25},\"point\":2},{\"from\":{\"x\":48,\"y\":27},\"to\":{\"x\":48,\"y\":26},\"point\":2}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"from\":{\"x\":48,\"y\":4},\"to\":{\"x\":47,\"y\":7},\"point\":7}]";
	Cmd::Exec(command);
	command = "path --add --switch=[{\"cell\":{\"x\":48,\"y\":4},\"point\":2}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"from\":{\"x\":42,\"y\":12},\"to\":{\"x\":41,\"y\":13},\"point\":7},{\"from\":{\"x\":43,\"y\":11},\"to\":{\"x\":42,\"y\":12},\"point\":7},{\"from\":{\"x\":44,\"y\":10},\"to\":{\"x\":43,\"y\":11},\"point\":7},{\"from\":{\"x\":45,\"y\":9},\"to\":{\"x\":44,\"y\":10},\"point\":7},{\"from\":{\"x\":46,\"y\":8},\"to\":{\"x\":45,\"y\":9},\"point\":7},{\"from\":{\"x\":47,\"y\":7},\"to\":{\"x\":46,\"y\":8},\"point\":7}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"from\":{\"x\":35,\"y\":15},\"to\":{\"x\":34,\"y\":15},\"point\":0},{\"from\":{\"x\":36,\"y\":15},\"to\":{\"x\":35,\"y\":15},\"point\":0},{\"from\":{\"x\":37,\"y\":15},\"to\":{\"x\":36,\"y\":15},\"point\":0},{\"from\":{\"x\":40,\"y\":14},\"to\":{\"x\":37,\"y\":15},\"point\":0},{\"from\":{\"x\":41,\"y\":13},\"to\":{\"x\":40,\"y\":14},\"point\":7}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"from\":{\"x\":29,\"y\":15},\"to\":{\"x\":28,\"y\":15},\"point\":0},{\"from\":{\"x\":30,\"y\":15},\"to\":{\"x\":29,\"y\":15},\"point\":0},{\"from\":{\"x\":31,\"y\":15},\"to\":{\"x\":30,\"y\":15},\"point\":0},{\"from\":{\"x\":32,\"y\":15},\"to\":{\"x\":31,\"y\":15},\"point\":0},{\"from\":{\"x\":33,\"y\":15},\"to\":{\"x\":32,\"y\":15},\"point\":0},{\"from\":{\"x\":34,\"y\":15},\"to\":{\"x\":33,\"y\":15},\"point\":0}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"from\":{\"x\":20,\"y\":15},\"to\":{\"x\":19,\"y\":15},\"point\":0},{\"from\":{\"x\":21,\"y\":15},\"to\":{\"x\":20,\"y\":15},\"point\":0},{\"from\":{\"x\":22,\"y\":15},\"to\":{\"x\":21,\"y\":15},\"point\":0},{\"from\":{\"x\":23,\"y\":15},\"to\":{\"x\":22,\"y\":15},\"point\":0},{\"from\":{\"x\":24,\"y\":15},\"to\":{\"x\":23,\"y\":15},\"point\":0},{\"from\":{\"x\":25,\"y\":15},\"to\":{\"x\":24,\"y\":15},\"point\":0},{\"from\":{\"x\":26,\"y\":15},\"to\":{\"x\":25,\"y\":15},\"point\":0},{\"from\":{\"x\":27,\"y\":15},\"to\":{\"x\":26,\"y\":15},\"point\":0},{\"from\":{\"x\":28,\"y\":15},\"to\":{\"x\":27,\"y\":15},\"point\":0}]";
	Cmd::Exec(command);
	command = "path --add --switch=[{\"cell\":{\"x\":19,\"y\":15},\"point\":0}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"from\":{\"x\":9,\"y\":14},\"to\":{\"x\":8,\"y\":15},\"point\":7},{\"from\":{\"x\":12,\"y\":13},\"to\":{\"x\":9,\"y\":14},\"point\":7},{\"from\":{\"x\":15,\"y\":14},\"to\":{\"x\":12,\"y\":13},\"point\":0}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"from\":{\"x\":8,\"y\":15},\"to\":{\"x\":7,\"y\":18},\"point\":6}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"from\":{\"x\":20,\"y\":33},\"to\":{\"x\":21,\"y\":34},\"point\":5},{\"from\":{\"x\":19,\"y\":32},\"to\":{\"x\":20,\"y\":33},\"point\":5},{\"from\":{\"x\":18,\"y\":31},\"to\":{\"x\":19,\"y\":32},\"point\":5},{\"from\":{\"x\":17,\"y\":30},\"to\":{\"x\":18,\"y\":31},\"point\":5},{\"from\":{\"x\":16,\"y\":29},\"to\":{\"x\":17,\"y\":30},\"point\":5},{\"from\":{\"x\":15,\"y\":28},\"to\":{\"x\":16,\"y\":29},\"point\":5},{\"from\":{\"x\":14,\"y\":27},\"to\":{\"x\":15,\"y\":28},\"point\":5},{\"from\":{\"x\":13,\"y\":26},\"to\":{\"x\":14,\"y\":27},\"point\":5},{\"from\":{\"x\":12,\"y\":25},\"to\":{\"x\":13,\"y\":26},\"point\":5},{\"from\":{\"x\":11,\"y\":24},\"to\":{\"x\":12,\"y\":25},\"point\":5},{\"from\":{\"x\":10,\"y\":23},\"to\":{\"x\":11,\"y\":24},\"point\":5},{\"from\":{\"x\":9,\"y\":22},\"to\":{\"x\":10,\"y\":23},\"point\":5},{\"from\":{\"x\":8,\"y\":21},\"to\":{\"x\":9,\"y\":22},\"point\":5},{\"from\":{\"x\":7,\"y\":18},\"to\":{\"x\":8,\"y\":21},\"point\":5}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"from\":{\"x\":22,\"y\":37},\"to\":{\"x\":21,\"y\":40},\"point\":7},{\"from\":{\"x\":21,\"y\":34},\"to\":{\"x\":22,\"y\":37},\"point\":6}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"from\":{\"x\":20,\"y\":41},\"to\":{\"x\":17,\"y\":42},\"point\":0},{\"from\":{\"x\":21,\"y\":40},\"to\":{\"x\":20,\"y\":41},\"point\":7}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"from\":{\"x\":6,\"y\":33},\"to\":{\"x\":5,\"y\":30},\"point\":2},{\"from\":{\"x\":7,\"y\":34},\"to\":{\"x\":6,\"y\":33},\"point\":1},{\"from\":{\"x\":8,\"y\":35},\"to\":{\"x\":7,\"y\":34},\"point\":1},{\"from\":{\"x\":9,\"y\":36},\"to\":{\"x\":8,\"y\":35},\"point\":1},{\"from\":{\"x\":10,\"y\":37},\"to\":{\"x\":9,\"y\":36},\"point\":1},{\"from\":{\"x\":11,\"y\":38},\"to\":{\"x\":10,\"y\":37},\"point\":1},{\"from\":{\"x\":12,\"y\":39},\"to\":{\"x\":11,\"y\":38},\"point\":1},{\"from\":{\"x\":13,\"y\":40},\"to\":{\"x\":12,\"y\":39},\"point\":1},{\"from\":{\"x\":14,\"y\":41},\"to\":{\"x\":13,\"y\":40},\"point\":1},{\"from\":{\"x\":17,\"y\":42},\"to\":{\"x\":14,\"y\":41},\"point\":1}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"from\":{\"x\":5,\"y\":5},\"to\":{\"x\":5,\"y\":4},\"point\":2},{\"from\":{\"x\":5,\"y\":6},\"to\":{\"x\":5,\"y\":5},\"point\":2},{\"from\":{\"x\":5,\"y\":7},\"to\":{\"x\":5,\"y\":6},\"point\":2},{\"from\":{\"x\":5,\"y\":8},\"to\":{\"x\":5,\"y\":7},\"point\":2},{\"from\":{\"x\":5,\"y\":9},\"to\":{\"x\":5,\"y\":8},\"point\":2},{\"from\":{\"x\":5,\"y\":10},\"to\":{\"x\":5,\"y\":9},\"point\":2},{\"from\":{\"x\":5,\"y\":11},\"to\":{\"x\":5,\"y\":10},\"point\":2},{\"from\":{\"x\":5,\"y\":12},\"to\":{\"x\":5,\"y\":11},\"point\":2},{\"from\":{\"x\":5,\"y\":13},\"to\":{\"x\":5,\"y\":12},\"point\":2},{\"from\":{\"x\":5,\"y\":14},\"to\":{\"x\":5,\"y\":13},\"point\":2},{\"from\":{\"x\":5,\"y\":15},\"to\":{\"x\":5,\"y\":14},\"point\":2},{\"from\":{\"x\":5,\"y\":16},\"to\":{\"x\":5,\"y\":15},\"point\":2},{\"from\":{\"x\":5,\"y\":17},\"to\":{\"x\":5,\"y\":16},\"point\":2},{\"from\":{\"x\":5,\"y\":18},\"to\":{\"x\":5,\"y\":17},\"point\":2},{\"from\":{\"x\":5,\"y\":19},\"to\":{\"x\":5,\"y\":18},\"point\":2},{\"from\":{\"x\":5,\"y\":20},\"to\":{\"x\":5,\"y\":19},\"point\":2},{\"from\":{\"x\":5,\"y\":21},\"to\":{\"x\":5,\"y\":20},\"point\":2},{\"from\":{\"x\":5,\"y\":22},\"to\":{\"x\":5,\"y\":21},\"point\":2},{\"from\":{\"x\":5,\"y\":23},\"to\":{\"x\":5,\"y\":22},\"point\":2},{\"from\":{\"x\":5,\"y\":24},\"to\":{\"x\":5,\"y\":23},\"point\":2},{\"from\":{\"x\":5,\"y\":25},\"to\":{\"x\":5,\"y\":24},\"point\":2},{\"from\":{\"x\":5,\"y\":26},\"to\":{\"x\":5,\"y\":25},\"point\":2},{\"from\":{\"x\":5,\"y\":27},\"to\":{\"x\":5,\"y\":26},\"point\":2},{\"from\":{\"x\":5,\"y\":28},\"to\":{\"x\":5,\"y\":27},\"point\":2},{\"from\":{\"x\":5,\"y\":29},\"to\":{\"x\":5,\"y\":28},\"point\":2},{\"from\":{\"x\":5,\"y\":30},\"to\":{\"x\":5,\"y\":29},\"point\":2}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"from\":{\"x\":45,\"y\":2},\"to\":{\"x\":46,\"y\":2},\"point\":4},{\"from\":{\"x\":44,\"y\":2},\"to\":{\"x\":45,\"y\":2},\"point\":4},{\"from\":{\"x\":43,\"y\":2},\"to\":{\"x\":44,\"y\":2},\"point\":4},{\"from\":{\"x\":42,\"y\":2},\"to\":{\"x\":43,\"y\":2},\"point\":4},{\"from\":{\"x\":41,\"y\":2},\"to\":{\"x\":42,\"y\":2},\"point\":4},{\"from\":{\"x\":40,\"y\":2},\"to\":{\"x\":41,\"y\":2},\"point\":4},{\"from\":{\"x\":39,\"y\":2},\"to\":{\"x\":40,\"y\":2},\"point\":4},{\"from\":{\"x\":38,\"y\":2},\"to\":{\"x\":39,\"y\":2},\"point\":4},{\"from\":{\"x\":37,\"y\":2},\"to\":{\"x\":38,\"y\":2},\"point\":4},{\"from\":{\"x\":36,\"y\":2},\"to\":{\"x\":37,\"y\":2},\"point\":4},{\"from\":{\"x\":35,\"y\":2},\"to\":{\"x\":36,\"y\":2},\"point\":4},{\"from\":{\"x\":34,\"y\":2},\"to\":{\"x\":35,\"y\":2},\"point\":4},{\"from\":{\"x\":33,\"y\":2},\"to\":{\"x\":34,\"y\":2},\"point\":4},{\"from\":{\"x\":32,\"y\":2},\"to\":{\"x\":33,\"y\":2},\"point\":4},{\"from\":{\"x\":31,\"y\":2},\"to\":{\"x\":32,\"y\":2},\"point\":4},{\"from\":{\"x\":30,\"y\":2},\"to\":{\"x\":31,\"y\":2},\"point\":4},{\"from\":{\"x\":29,\"y\":2},\"to\":{\"x\":30,\"y\":2},\"point\":4},{\"from\":{\"x\":28,\"y\":2},\"to\":{\"x\":29,\"y\":2},\"point\":4},{\"from\":{\"x\":27,\"y\":2},\"to\":{\"x\":28,\"y\":2},\"point\":4},{\"from\":{\"x\":26,\"y\":2},\"to\":{\"x\":27,\"y\":2},\"point\":4},{\"from\":{\"x\":25,\"y\":2},\"to\":{\"x\":26,\"y\":2},\"point\":4},{\"from\":{\"x\":24,\"y\":2},\"to\":{\"x\":25,\"y\":2},\"point\":4},{\"from\":{\"x\":23,\"y\":2},\"to\":{\"x\":24,\"y\":2},\"point\":4},{\"from\":{\"x\":22,\"y\":2},\"to\":{\"x\":23,\"y\":2},\"point\":4},{\"from\":{\"x\":21,\"y\":2},\"to\":{\"x\":22,\"y\":2},\"point\":4},{\"from\":{\"x\":20,\"y\":2},\"to\":{\"x\":21,\"y\":2},\"point\":4},{\"from\":{\"x\":19,\"y\":2},\"to\":{\"x\":20,\"y\":2},\"point\":4},{\"from\":{\"x\":18,\"y\":2},\"to\":{\"x\":19,\"y\":2},\"point\":4},{\"from\":{\"x\":17,\"y\":2},\"to\":{\"x\":18,\"y\":2},\"point\":4},{\"from\":{\"x\":16,\"y\":2},\"to\":{\"x\":17,\"y\":2},\"point\":4},{\"from\":{\"x\":15,\"y\":2},\"to\":{\"x\":16,\"y\":2},\"point\":4},{\"from\":{\"x\":14,\"y\":2},\"to\":{\"x\":15,\"y\":2},\"point\":4},{\"from\":{\"x\":13,\"y\":2},\"to\":{\"x\":14,\"y\":2},\"point\":4},{\"from\":{\"x\":12,\"y\":2},\"to\":{\"x\":13,\"y\":2},\"point\":4},{\"from\":{\"x\":11,\"y\":2},\"to\":{\"x\":12,\"y\":2},\"point\":4},{\"from\":{\"x\":10,\"y\":2},\"to\":{\"x\":11,\"y\":2},\"point\":4},{\"from\":{\"x\":9,\"y\":2},\"to\":{\"x\":10,\"y\":2},\"point\":4},{\"from\":{\"x\":8,\"y\":2},\"to\":{\"x\":9,\"y\":2},\"point\":4},{\"from\":{\"x\":7,\"y\":2},\"to\":{\"x\":8,\"y\":2},\"point\":4},{\"from\":{\"x\":5,\"y\":4},\"to\":{\"x\":7,\"y\":2},\"point\":4}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"from\":{\"x\":46,\"y\":2},\"to\":{\"x\":48,\"y\":4},\"point\":6}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"from\":{\"x\":48,\"y\":13},\"to\":{\"x\":49,\"y\":16},\"point\":5}]";
	Cmd::Exec(command);
	command = "path --add --switch=[{\"cell\":{\"x\":48,\"y\":13},\"point\":2}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"from\":{\"x\":48,\"y\":13},\"to\":{\"x\":49,\"y\":10},\"point\":3}]";
	Cmd::Exec(command);
	command = "path --add --switch=[{\"cell\":{\"x\":48,\"y\":13},\"point\":6}]";
	Cmd::Exec(command);
	
	Train *train = new Train();
	train->direction = Back;
	//train->direction = Forward;
	train->AddCar(new Car(Locomotive));
	//train->AddCar(new Car(Locomotive));
	//train->AddCar(new Car(TankCar));
	//train->AddCar(new Car(TankCar));
	//train->AddCar(new Car(Switcher));
	train->AddCar(new Car(Switcher));
	train->AddCar(new Car(TankCar));
	train->AddCar(new Car(TankCar));
	train->AddCar(new Car(TankCar));

	/*train->AddCar(new Car(TankCar));
	train->AddCar(new Car(TankCar));
	train->AddCar(new Car(Switcher));
	train->AddCar(new Car(Switcher));
	train->AddCar(new Car(TankCar));
	train->AddCar(new Car(TankCar));
	train->AddCar(new Car(TankCar));
	train->AddCar(new Car(TankCar));
	train->AddCar(new Car(TankCar));

	
	
	train->AddCar(new Car(Switcher));
	train->AddCar(new Car(Switcher));
	train->AddCar(new Car(Switcher));
	train->AddCar(new Car(Switcher));
	train->AddCar(new Car(Switcher));
	train->AddCar(new Car(Switcher));
	train->AddCar(new Car(Switcher));
	train->AddCar(new Car(Switcher));
	train->AddCar(new Car(Switcher));
	train->AddCar(new Car(Switcher));
	train->AddCar(new Car(Switcher));
	train->AddCar(new Car(Switcher));*/

	//train->AddCar(new Car(Locomotive));
	train->AddCar(new Car(Locomotive));
	//train->SetPosition(Path::GetPosition({ &Game->cells[40][2], 0, 0 }, 10));
	train->SetPosition( {&Game->cells[40][2], 0, 0 });
	Game->AddTrain(train);
		
	/*
	int d = 1;
	for (int i = 0; i < 1; i++) {
		for (int j = 0; j < 1; j++) {
			x = (j + 1) * 50 - 50;
			y = (i + 1) * 25 - 25;
		}
	}*/
}
