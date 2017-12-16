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
	startLocation = { 5, 5 };
}

void MapLayer::test()
{
	/*Field *Game = Field::getInstance();

	auto renderTexture = RenderTexture::create(100, 100, Texture2D::PixelFormat::RGBA4444);

	renderTexture->setColor(Color3B::BLUE);

	//renderTexture->addChild();

	Sprite *image;
	image = Elements::GetTrackElement({ 10, 10 }, TrackElement::Horizontal);

	int d = 10 * Field::getInstance()->scale;
	Texture2D *texture = Director::getInstance()->getTextureCache()->addImage("rails.png");
	Sprite *item = Sprite::createWithTexture(texture, Rect(d, 2.5 * d, d, d));
	item->setPosition(10 * d - 0.5 * d, 10 * d);

	renderTexture->addChild(item);
	renderTexture->setPosition({100, 100});

	

	Game->trainsLayer->addChild(renderTexture, ZIndexTrainsLabel);*/

	//renderTexture->end();
	//Director::getInstance()->getRenderer()->render();


	//Field::getInstance()->mapLayer->addChild(image, ZIndexRails); //!!!!!!!!!!
	//entry->Resource = image;

	Sprite *sprite;
	sprite = Elements::GetTrackElement({ 10, 10 }, TrackElement::Horizontal);

	//auto sprite = Sprite::create("original.png");
	auto renderTexture = RenderTexture::create(64, 64, Texture2D::PixelFormat::RGBA8888);
	renderTexture->begin();
	sprite->setAnchorPoint(Vec2(0, 0));
	sprite->setPosition(Vec2(0, 0));
	sprite->visit();
	renderTexture->end();
	renderTexture->saveToFile("rendertexture.png", Image::Format::PNG);

	
	int x;
	int y;
	int k = 5;
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < k; j++) {
			x = j * 45;
			y = i * 43;
			testNet(x, y);
		}
	}
}

void MapLayer::testNet(int x, int y) {
	Field *Game = Field::getInstance();

	//Game->cells[18 + x][15 + y].Connect(&Game->cells[15 + x][14 + y], 1);
	string command = "path --add --path=[{\"from\":{\"x\":" + p(18, x) + ",\"y\":" + p(15, y) + "},\"to\":{\"x\":" + p(15, x) + ",\"y\":" + p(14, y) + "},\"point\":1}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"from\":{\"x\":" + p(38, x) + ",\"y\":" + p(32, y) + "},\"to\":{\"x\":" + p(39, x) + ",\"y\":" + p(33, y) + "},\"point\":5},{\"from\":{\"x\":" + p(37, x) + ",\"y\":" + p(31, y) + "},\"to\":{\"x\":" + p(38, x) + ",\"y\":" + p(32, y) + "},\"point\":5},{\"from\":{\"x\":" + p(36, x) + ",\"y\":" + p(30, y) + "},\"to\":{\"x\":" + p(37, x) + ",\"y\":" + p(31, y) + "},\"point\":5},{\"from\":{\"x\":" + p(35, x) + ",\"y\":" + p(29, y) + "},\"to\":{\"x\":" + p(36, x) + ",\"y\":" + p(30, y) + "},\"point\":5},{\"from\":{\"x\":" + p(34, x) + ",\"y\":" + p(28, y) + "},\"to\":{\"x\":" + p(35, x) + ",\"y\":" + p(29, y) + "},\"point\":5},{\"from\":{\"x\":" + p(33, x) + ",\"y\":" + p(27, y) + "},\"to\":{\"x\":" + p(34, x) + ",\"y\":" + p(28, y) + "},\"point\":5},{\"from\":{\"x\":" + p(32, x) + ",\"y\":" + p(26, y) + "},\"to\":{\"x\":" + p(33, x) + ",\"y\":" + p(27, y) + "},\"point\":5},{\"from\":{\"x\":" + p(31, x) + ",\"y\":" + p(25, y) + "},\"to\":{\"x\":" + p(32, x) + ",\"y\":" + p(26, y) + "},\"point\":5},{\"from\":{\"x\":" + p(30, x) + ",\"y\":" + p(24, y) + "},\"to\":{\"x\":" + p(31, x) + ",\"y\":" + p(25, y) + "},\"point\":5},{\"from\":{\"x\":" + p(29, x) + ",\"y\":" + p(23, y) + "},\"to\":{\"x\":" + p(30, x) + ",\"y\":" + p(24, y) + "},\"point\":5},{\"from\":{\"x\":" + p(28, x) + ",\"y\":" + p(22, y) + "},\"to\":{\"x\":" + p(29, x) + ",\"y\":" + p(23, y) + "},\"point\":5},{\"from\":{\"x\":" + p(27, x) + ",\"y\":" + p(21, y) + "},\"to\":{\"x\":" + p(28, x) + ",\"y\":" + p(22, y) + "},\"point\":5},{\"from\":{\"x\":" + p(26, x) + ",\"y\":" + p(20, y) + "},\"to\":{\"x\":" + p(27, x) + ",\"y\":" + p(21, y) + "},\"point\":5},{\"from\":{\"x\":" + p(25, x) + ",\"y\":" + p(19, y) + "},\"to\":{\"x\":" + p(26, x) + ",\"y\":" + p(20, y) + "},\"point\":5},{\"from\":{\"x\":" + p(24, x) + ",\"y\":" + p(18, y) + "},\"to\":{\"x\":" + p(25, x) + ",\"y\":" + p(19, y) + "},\"point\":5},{\"from\":{\"x\":" + p(23, x) + ",\"y\":" + p(17, y) + "},\"to\":{\"x\":" + p(24, x) + ",\"y\":" + p(18, y) + "},\"point\":5},{\"from\":{\"x\":" + p(22, x) + ",\"y\":" + p(16, y) + "},\"to\":{\"x\":" + p(23, x) + ",\"y\":" + p(17, y) + "},\"point\":5},{\"from\":{\"x\":" + p(19, x) + ",\"y\":" + p(15, y) + "},\"to\":{\"x\":" + p(22, x) + ",\"y\":" + p(16, y) + "},\"point\":5},{\"from\":{\"x\":" + p(18, x) + ",\"y\":" + p(15, y) + "},\"to\":{\"x\":" + p(19, x) + ",\"y\":" + p(15, y) + "},\"point\":4}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"from\":{\"x\":" + p(43, x) + ",\"y\":" + p(34, y) + "},\"to\":{\"x\":" + p(46, x) + ",\"y\":" + p(33, y) + "},\"point\":3},{\"from\":{\"x\":" + p(42, x) + ",\"y\":" + p(34, y) + "},\"to\":{\"x\":" + p(43, x) + ",\"y\":" + p(34, y) + "},\"point\":4},{\"from\":{\"x\":" + p(39, x) + ",\"y\":" + p(33, y) + "},\"to\":{\"x\":" + p(42, x) + ",\"y\":" + p(34, y) + "},\"point\":4}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"from\":{\"x\":" + p(48, x) + ",\"y\":" + p(28, y) + "},\"to\":{\"x\":" + p(48, x) + ",\"y\":" + p(27, y) + "},\"point\":2},{\"from\":{\"x\":" + p(48, x) + ",\"y\":" + p(29, y) + "},\"to\":{\"x\":" + p(48, x) + ",\"y\":" + p(28, y) + "},\"point\":2},{\"from\":{\"x\":" + p(47, x) + ",\"y\":" + p(32, y) + "},\"to\":{\"x\":" + p(48, x) + ",\"y\":" + p(29, y) + "},\"point\":2},{\"from\":{\"x\":" + p(46, x) + ",\"y\":" + p(33, y) + "},\"to\":{\"x\":" + p(47, x) + ",\"y\":" + p(32, y) + "},\"point\":3}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"from\":{\"x\":" + p(48, x) + ",\"y\":" + p(5, y) + "},\"to\":{\"x\":" + p(48, x) + ",\"y\":" + p(4, y) + "},\"point\":2},{\"from\":{\"x\":" + p(48, x) + ",\"y\":" + p(6, y) + "},\"to\":{\"x\":" + p(48, x) + ",\"y\":" + p(5, y) + "},\"point\":2},{\"from\":{\"x\":" + p(48, x) + ",\"y\":" + p(7, y) + "},\"to\":{\"x\":" + p(48, x) + ",\"y\":" + p(6, y) + "},\"point\":2},{\"from\":{\"x\":" + p(48, x) + ",\"y\":" + p(8, y) + "},\"to\":{\"x\":" + p(48, x) + ",\"y\":" + p(7, y) + "},\"point\":2},{\"from\":{\"x\":" + p(48, x) + ",\"y\":" + p(9, y) + "},\"to\":{\"x\":" + p(48, x) + ",\"y\":" + p(8, y) + "},\"point\":2},{\"from\":{\"x\":" + p(48, x) + ",\"y\":" + p(10, y) + "},\"to\":{\"x\":" + p(48, x) + ",\"y\":" + p(9, y) + "},\"point\":2},{\"from\":{\"x\":" + p(48, x) + ",\"y\":" + p(11, y) + "},\"to\":{\"x\":" + p(48, x) + ",\"y\":" + p(10, y) + "},\"point\":2},{\"from\":{\"x\":" + p(48, x) + ",\"y\":" + p(12, y) + "},\"to\":{\"x\":" + p(48, x) + ",\"y\":" + p(11, y) + "},\"point\":2},{\"from\":{\"x\":" + p(48, x) + ",\"y\":" + p(13, y) + "},\"to\":{\"x\":" + p(48, x) + ",\"y\":" + p(12, y) + "},\"point\":2},{\"from\":{\"x\":" + p(48, x) + ",\"y\":" + p(14, y) + "},\"to\":{\"x\":" + p(48, x) + ",\"y\":" + p(13, y) + "},\"point\":2},{\"from\":{\"x\":" + p(48, x) + ",\"y\":" + p(15, y) + "},\"to\":{\"x\":" + p(48, x) + ",\"y\":" + p(14, y) + "},\"point\":2},{\"from\":{\"x\":" + p(48, x) + ",\"y\":" + p(16, y) + "},\"to\":{\"x\":" + p(48, x) + ",\"y\":" + p(15, y) + "},\"point\":2},{\"from\":{\"x\":" + p(48, x) + ",\"y\":" + p(17, y) + "},\"to\":{\"x\":" + p(48, x) + ",\"y\":" + p(16, y) + "},\"point\":2},{\"from\":{\"x\":" + p(48, x) + ",\"y\":" + p(18, y) + "},\"to\":{\"x\":" + p(48, x) + ",\"y\":" + p(17, y) + "},\"point\":2},{\"from\":{\"x\":" + p(48, x) + ",\"y\":" + p(19, y) + "},\"to\":{\"x\":" + p(48, x) + ",\"y\":" + p(18, y) + "},\"point\":2},{\"from\":{\"x\":" + p(48, x) + ",\"y\":" + p(20, y) + "},\"to\":{\"x\":" + p(48, x) + ",\"y\":" + p(19, y) + "},\"point\":2},{\"from\":{\"x\":" + p(48, x) + ",\"y\":" + p(21, y) + "},\"to\":{\"x\":" + p(48, x) + ",\"y\":" + p(20, y) + "},\"point\":2},{\"from\":{\"x\":" + p(48, x) + ",\"y\":" + p(22, y) + "},\"to\":{\"x\":" + p(48, x) + ",\"y\":" + p(21, y) + "},\"point\":2},{\"from\":{\"x\":" + p(48, x) + ",\"y\":" + p(23, y) + "},\"to\":{\"x\":" + p(48, x) + ",\"y\":" + p(22, y) + "},\"point\":2},{\"from\":{\"x\":" + p(48, x) + ",\"y\":" + p(24, y) + "},\"to\":{\"x\":" + p(48, x) + ",\"y\":" + p(23, y) + "},\"point\":2},{\"from\":{\"x\":" + p(48, x) + ",\"y\":" + p(25, y) + "},\"to\":{\"x\":" + p(48, x) + ",\"y\":" + p(24, y) + "},\"point\":2},{\"from\":{\"x\":" + p(48, x) + ",\"y\":" + p(26, y) + "},\"to\":{\"x\":" + p(48, x) + ",\"y\":" + p(25, y) + "},\"point\":2},{\"from\":{\"x\":" + p(48, x) + ",\"y\":" + p(27, y) + "},\"to\":{\"x\":" + p(48, x) + ",\"y\":" + p(26, y) + "},\"point\":2}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"from\":{\"x\":" + p(48, x) + ",\"y\":" + p(4, y) + "},\"to\":{\"x\":" + p(47, x) + ",\"y\":" + p(7, y) + "},\"point\":7}]";
	Cmd::Exec(command);
	command = "path --add --switch=[{\"cell\":{\"x\":" + p(48, x) + ",\"y\":" + p(4, y) + "},\"point\":2}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"from\":{\"x\":" + p(42, x) + ",\"y\":" + p(12, y) + "},\"to\":{\"x\":" + p(41, x) + ",\"y\":" + p(13, y) + "},\"point\":7},{\"from\":{\"x\":" + p(43, x) + ",\"y\":" + p(11, y) + "},\"to\":{\"x\":" + p(42, x) + ",\"y\":" + p(12, y) + "},\"point\":7},{\"from\":{\"x\":" + p(44, x) + ",\"y\":" + p(10, y) + "},\"to\":{\"x\":" + p(43, x) + ",\"y\":" + p(11, y) + "},\"point\":7},{\"from\":{\"x\":" + p(45, x) + ",\"y\":" + p(9, y) + "},\"to\":{\"x\":" + p(44, x) + ",\"y\":" + p(10, y) + "},\"point\":7},{\"from\":{\"x\":" + p(46, x) + ",\"y\":" + p(8, y) + "},\"to\":{\"x\":" + p(45, x) + ",\"y\":" + p(9, y) + "},\"point\":7},{\"from\":{\"x\":" + p(47, x) + ",\"y\":" + p(7, y) + "},\"to\":{\"x\":" + p(46, x) + ",\"y\":" + p(8, y) + "},\"point\":7}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"from\":{\"x\":" + p(35, x) + ",\"y\":" + p(15, y) + "},\"to\":{\"x\":" + p(34, x) + ",\"y\":" + p(15, y) + "},\"point\":0},{\"from\":{\"x\":" + p(36, x) + ",\"y\":" + p(15, y) + "},\"to\":{\"x\":" + p(35, x) + ",\"y\":" + p(15, y) + "},\"point\":0},{\"from\":{\"x\":" + p(37, x) + ",\"y\":" + p(15, y) + "},\"to\":{\"x\":" + p(36, x) + ",\"y\":" + p(15, y) + "},\"point\":0},{\"from\":{\"x\":" + p(40, x) + ",\"y\":" + p(14, y) + "},\"to\":{\"x\":" + p(37, x) + ",\"y\":" + p(15, y) + "},\"point\":0},{\"from\":{\"x\":" + p(41, x) + ",\"y\":" + p(13, y) + "},\"to\":{\"x\":" + p(40, x) + ",\"y\":" + p(14, y) + "},\"point\":7}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"from\":{\"x\":" + p(29, x) + ",\"y\":" + p(15, y) + "},\"to\":{\"x\":" + p(28, x) + ",\"y\":" + p(15, y) + "},\"point\":0},{\"from\":{\"x\":" + p(30, x) + ",\"y\":" + p(15, y) + "},\"to\":{\"x\":" + p(29, x) + ",\"y\":" + p(15, y) + "},\"point\":0},{\"from\":{\"x\":" + p(31, x) + ",\"y\":" + p(15, y) + "},\"to\":{\"x\":" + p(30, x) + ",\"y\":" + p(15, y) + "},\"point\":0},{\"from\":{\"x\":" + p(32, x) + ",\"y\":" + p(15, y) + "},\"to\":{\"x\":" + p(31, x) + ",\"y\":" + p(15, y) + "},\"point\":0},{\"from\":{\"x\":" + p(33, x) + ",\"y\":" + p(15, y) + "},\"to\":{\"x\":" + p(32, x) + ",\"y\":" + p(15, y) + "},\"point\":0},{\"from\":{\"x\":" + p(34, x) + ",\"y\":" + p(15, y) + "},\"to\":{\"x\":" + p(33, x) + ",\"y\":" + p(15, y) + "},\"point\":0}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"from\":{\"x\":" + p(20, x) + ",\"y\":" + p(15, y) + "},\"to\":{\"x\":" + p(19, x) + ",\"y\":" + p(15, y) + "},\"point\":0},{\"from\":{\"x\":" + p(21, x) + ",\"y\":" + p(15, y) + "},\"to\":{\"x\":" + p(20, x) + ",\"y\":" + p(15, y) + "},\"point\":0},{\"from\":{\"x\":" + p(22, x) + ",\"y\":" + p(15, y) + "},\"to\":{\"x\":" + p(21, x) + ",\"y\":" + p(15, y) + "},\"point\":0},{\"from\":{\"x\":" + p(23, x) + ",\"y\":" + p(15, y) + "},\"to\":{\"x\":" + p(22, x) + ",\"y\":" + p(15, y) + "},\"point\":0},{\"from\":{\"x\":" + p(24, x) + ",\"y\":" + p(15, y) + "},\"to\":{\"x\":" + p(23, x) + ",\"y\":" + p(15, y) + "},\"point\":0},{\"from\":{\"x\":" + p(25, x) + ",\"y\":" + p(15, y) + "},\"to\":{\"x\":" + p(24, x) + ",\"y\":" + p(15, y) + "},\"point\":0},{\"from\":{\"x\":" + p(26, x) + ",\"y\":" + p(15, y) + "},\"to\":{\"x\":" + p(25, x) + ",\"y\":" + p(15, y) + "},\"point\":0},{\"from\":{\"x\":" + p(27, x) + ",\"y\":" + p(15, y) + "},\"to\":{\"x\":" + p(26, x) + ",\"y\":" + p(15, y) + "},\"point\":0},{\"from\":{\"x\":" + p(28, x) + ",\"y\":" + p(15, y) + "},\"to\":{\"x\":" + p(27, x) + ",\"y\":" + p(15, y) + "},\"point\":0}]";
	Cmd::Exec(command);
	command = "path --add --switch=[{\"cell\":{\"x\":" + p(19, x) + ",\"y\":" + p(15, y) + "},\"point\":0}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"from\":{\"x\":" + p(9, x) + ",\"y\":" + p(14, y) + "},\"to\":{\"x\":" + p(8, x) + ",\"y\":" + p(15, y) + "},\"point\":7},{\"from\":{\"x\":" + p(12, x) + ",\"y\":" + p(13, y) + "},\"to\":{\"x\":" + p(9, x) + ",\"y\":" + p(14, y) + "},\"point\":7},{\"from\":{\"x\":" + p(15, x) + ",\"y\":" + p(14, y) + "},\"to\":{\"x\":" + p(12, x) + ",\"y\":" + p(13, y) + "},\"point\":0}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"from\":{\"x\":" + p(8, x) + ",\"y\":" + p(15, y) + "},\"to\":{\"x\":" + p(7, x) + ",\"y\":" + p(18, y) + "},\"point\":6}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"from\":{\"x\":" + p(20, x) + ",\"y\":" + p(33, y) + "},\"to\":{\"x\":" + p(21, x) + ",\"y\":" + p(34, y) + "},\"point\":5},{\"from\":{\"x\":" + p(19, x) + ",\"y\":" + p(32, y) + "},\"to\":{\"x\":" + p(20, x) + ",\"y\":" + p(33, y) + "},\"point\":5},{\"from\":{\"x\":" + p(18, x) + ",\"y\":" + p(31, y) + "},\"to\":{\"x\":" + p(19, x) + ",\"y\":" + p(32, y) + "},\"point\":5},{\"from\":{\"x\":" + p(17, x) + ",\"y\":" + p(30, y) + "},\"to\":{\"x\":" + p(18, x) + ",\"y\":" + p(31, y) + "},\"point\":5},{\"from\":{\"x\":" + p(16, x) + ",\"y\":" + p(29, y) + "},\"to\":{\"x\":" + p(17, x) + ",\"y\":" + p(30, y) + "},\"point\":5},{\"from\":{\"x\":" + p(15, x) + ",\"y\":" + p(28, y) + "},\"to\":{\"x\":" + p(16, x) + ",\"y\":" + p(29, y) + "},\"point\":5},{\"from\":{\"x\":" + p(14, x) + ",\"y\":" + p(27, y) + "},\"to\":{\"x\":" + p(15, x) + ",\"y\":" + p(28, y) + "},\"point\":5},{\"from\":{\"x\":" + p(13, x) + ",\"y\":" + p(26, y) + "},\"to\":{\"x\":" + p(14, x) + ",\"y\":" + p(27, y) + "},\"point\":5},{\"from\":{\"x\":" + p(12, x) + ",\"y\":" + p(25, y) + "},\"to\":{\"x\":" + p(13, x) + ",\"y\":" + p(26, y) + "},\"point\":5},{\"from\":{\"x\":" + p(11, x) + ",\"y\":" + p(24, y) + "},\"to\":{\"x\":" + p(12, x) + ",\"y\":" + p(25, y) + "},\"point\":5},{\"from\":{\"x\":" + p(10, x) + ",\"y\":" + p(23, y) + "},\"to\":{\"x\":" + p(11, x) + ",\"y\":" + p(24, y) + "},\"point\":5},{\"from\":{\"x\":" + p(9, x) + ",\"y\":" + p(22, y) + "},\"to\":{\"x\":" + p(10, x) + ",\"y\":" + p(23, y) + "},\"point\":5},{\"from\":{\"x\":" + p(8, x) + ",\"y\":" + p(21, y) + "},\"to\":{\"x\":" + p(9, x) + ",\"y\":" + p(22, y) + "},\"point\":5},{\"from\":{\"x\":" + p(7, x) + ",\"y\":" + p(18, y) + "},\"to\":{\"x\":" + p(8, x) + ",\"y\":" + p(21, y) + "},\"point\":5}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"from\":{\"x\":" + p(22, x) + ",\"y\":" + p(37, y) + "},\"to\":{\"x\":" + p(21, x) + ",\"y\":" + p(40, y) + "},\"point\":7},{\"from\":{\"x\":" + p(21, x) + ",\"y\":" + p(34, y) + "},\"to\":{\"x\":" + p(22, x) + ",\"y\":" + p(37, y) + "},\"point\":6}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"from\":{\"x\":" + p(20, x) + ",\"y\":" + p(41, y) + "},\"to\":{\"x\":" + p(17, x) + ",\"y\":" + p(42, y) + "},\"point\":0},{\"from\":{\"x\":" + p(21, x) + ",\"y\":" + p(40, y) + "},\"to\":{\"x\":" + p(20, x) + ",\"y\":" + p(41, y) + "},\"point\":7}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"from\":{\"x\":" + p(6, x) + ",\"y\":" + p(33, y) + "},\"to\":{\"x\":" + p(5, x) + ",\"y\":" + p(30, y) + "},\"point\":2},{\"from\":{\"x\":" + p(7, x) + ",\"y\":" + p(34, y) + "},\"to\":{\"x\":" + p(6, x) + ",\"y\":" + p(33, y) + "},\"point\":1},{\"from\":{\"x\":" + p(8, x) + ",\"y\":" + p(35, y) + "},\"to\":{\"x\":" + p(7, x) + ",\"y\":" + p(34, y) + "},\"point\":1},{\"from\":{\"x\":" + p(9, x) + ",\"y\":" + p(36, y) + "},\"to\":{\"x\":" + p(8, x) + ",\"y\":" + p(35, y) + "},\"point\":1},{\"from\":{\"x\":" + p(10, x) + ",\"y\":" + p(37, y) + "},\"to\":{\"x\":" + p(9, x) + ",\"y\":" + p(36, y) + "},\"point\":1},{\"from\":{\"x\":" + p(11, x) + ",\"y\":" + p(38, y) + "},\"to\":{\"x\":" + p(10, x) + ",\"y\":" + p(37, y) + "},\"point\":1},{\"from\":{\"x\":" + p(12, x) + ",\"y\":" + p(39, y) + "},\"to\":{\"x\":" + p(11, x) + ",\"y\":" + p(38, y) + "},\"point\":1},{\"from\":{\"x\":" + p(13, x) + ",\"y\":" + p(40, y) + "},\"to\":{\"x\":" + p(12, x) + ",\"y\":" + p(39, y) + "},\"point\":1},{\"from\":{\"x\":" + p(14, x) + ",\"y\":" + p(41, y) + "},\"to\":{\"x\":" + p(13, x) + ",\"y\":" + p(40, y) + "},\"point\":1},{\"from\":{\"x\":" + p(17, x) + ",\"y\":" + p(42, y) + "},\"to\":{\"x\":" + p(14, x) + ",\"y\":" + p(41, y) + "},\"point\":1}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"from\":{\"x\":" + p(5, x) + ",\"y\":" + p(5, y) + "},\"to\":{\"x\":" + p(5, x) + ",\"y\":" + p(4, y) + "},\"point\":2},{\"from\":{\"x\":" + p(5, x) + ",\"y\":" + p(6, y) + "},\"to\":{\"x\":" + p(5, x) + ",\"y\":" + p(5, y) + "},\"point\":2},{\"from\":{\"x\":" + p(5, x) + ",\"y\":" + p(7, y) + "},\"to\":{\"x\":" + p(5, x) + ",\"y\":" + p(6, y) + "},\"point\":2},{\"from\":{\"x\":" + p(5, x) + ",\"y\":" + p(8, y) + "},\"to\":{\"x\":" + p(5, x) + ",\"y\":" + p(7, y) + "},\"point\":2},{\"from\":{\"x\":" + p(5, x) + ",\"y\":" + p(9, y) + "},\"to\":{\"x\":" + p(5, x) + ",\"y\":" + p(8, y) + "},\"point\":2},{\"from\":{\"x\":" + p(5, x) + ",\"y\":" + p(10, y) + "},\"to\":{\"x\":" + p(5, x) + ",\"y\":" + p(9, y) + "},\"point\":2},{\"from\":{\"x\":" + p(5, x) + ",\"y\":" + p(11, y) + "},\"to\":{\"x\":" + p(5, x) + ",\"y\":" + p(10, y) + "},\"point\":2},{\"from\":{\"x\":" + p(5, x) + ",\"y\":" + p(12, y) + "},\"to\":{\"x\":" + p(5, x) + ",\"y\":" + p(11, y) + "},\"point\":2},{\"from\":{\"x\":" + p(5, x) + ",\"y\":" + p(13, y) + "},\"to\":{\"x\":" + p(5, x) + ",\"y\":" + p(12, y) + "},\"point\":2},{\"from\":{\"x\":" + p(5, x) + ",\"y\":" + p(14, y) + "},\"to\":{\"x\":" + p(5, x) + ",\"y\":" + p(13, y) + "},\"point\":2},{\"from\":{\"x\":" + p(5, x) + ",\"y\":" + p(15, y) + "},\"to\":{\"x\":" + p(5, x) + ",\"y\":" + p(14, y) + "},\"point\":2},{\"from\":{\"x\":" + p(5, x) + ",\"y\":" + p(16, y) + "},\"to\":{\"x\":" + p(5, x) + ",\"y\":" + p(15, y) + "},\"point\":2},{\"from\":{\"x\":" + p(5, x) + ",\"y\":" + p(17, y) + "},\"to\":{\"x\":" + p(5, x) + ",\"y\":" + p(16, y) + "},\"point\":2},{\"from\":{\"x\":" + p(5, x) + ",\"y\":" + p(18, y) + "},\"to\":{\"x\":" + p(5, x) + ",\"y\":" + p(17, y) + "},\"point\":2},{\"from\":{\"x\":" + p(5, x) + ",\"y\":" + p(19, y) + "},\"to\":{\"x\":" + p(5, x) + ",\"y\":" + p(18, y) + "},\"point\":2},{\"from\":{\"x\":" + p(5, x) + ",\"y\":" + p(20, y) + "},\"to\":{\"x\":" + p(5, x) + ",\"y\":" + p(19, y) + "},\"point\":2},{\"from\":{\"x\":" + p(5, x) + ",\"y\":" + p(21, y) + "},\"to\":{\"x\":" + p(5, x) + ",\"y\":" + p(20, y) + "},\"point\":2},{\"from\":{\"x\":" + p(5, x) + ",\"y\":" + p(22, y) + "},\"to\":{\"x\":" + p(5, x) + ",\"y\":" + p(21, y) + "},\"point\":2},{\"from\":{\"x\":" + p(5, x) + ",\"y\":" + p(23, y) + "},\"to\":{\"x\":" + p(5, x) + ",\"y\":" + p(22, y) + "},\"point\":2},{\"from\":{\"x\":" + p(5, x) + ",\"y\":" + p(24, y) + "},\"to\":{\"x\":" + p(5, x) + ",\"y\":" + p(23, y) + "},\"point\":2},{\"from\":{\"x\":" + p(5, x) + ",\"y\":" + p(25, y) + "},\"to\":{\"x\":" + p(5, x) + ",\"y\":" + p(24, y) + "},\"point\":2},{\"from\":{\"x\":" + p(5, x) + ",\"y\":" + p(26, y) + "},\"to\":{\"x\":" + p(5, x) + ",\"y\":" + p(25, y) + "},\"point\":2},{\"from\":{\"x\":" + p(5, x) + ",\"y\":" + p(27, y) + "},\"to\":{\"x\":" + p(5, x) + ",\"y\":" + p(26, y) + "},\"point\":2},{\"from\":{\"x\":" + p(5, x) + ",\"y\":" + p(28, y) + "},\"to\":{\"x\":" + p(5, x) + ",\"y\":" + p(27, y) + "},\"point\":2},{\"from\":{\"x\":" + p(5, x) + ",\"y\":" + p(29, y) + "},\"to\":{\"x\":" + p(5, x) + ",\"y\":" + p(28, y) + "},\"point\":2},{\"from\":{\"x\":" + p(5, x) + ",\"y\":" + p(30, y) + "},\"to\":{\"x\":" + p(5, x) + ",\"y\":" + p(29, y) + "},\"point\":2}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"from\":{\"x\":" + p(45, x) + ",\"y\":" + p(2, y) + "},\"to\":{\"x\":" + p(46, x) + ",\"y\":" + p(2, y) + "},\"point\":4},{\"from\":{\"x\":" + p(44, x) + ",\"y\":" + p(2, y) + "},\"to\":{\"x\":" + p(45, x) + ",\"y\":" + p(2, y) + "},\"point\":4},{\"from\":{\"x\":" + p(43, x) + ",\"y\":" + p(2, y) + "},\"to\":{\"x\":" + p(44, x) + ",\"y\":" + p(2, y) + "},\"point\":4},{\"from\":{\"x\":" + p(42, x) + ",\"y\":" + p(2, y) + "},\"to\":{\"x\":" + p(43, x) + ",\"y\":" + p(2, y) + "},\"point\":4},{\"from\":{\"x\":" + p(41, x) + ",\"y\":" + p(2, y) + "},\"to\":{\"x\":" + p(42, x) + ",\"y\":" + p(2, y) + "},\"point\":4},{\"from\":{\"x\":" + p(40, x) + ",\"y\":" + p(2, y) + "},\"to\":{\"x\":" + p(41, x) + ",\"y\":" + p(2, y) + "},\"point\":4},{\"from\":{\"x\":" + p(39, x) + ",\"y\":" + p(2, y) + "},\"to\":{\"x\":" + p(40, x) + ",\"y\":" + p(2, y) + "},\"point\":4},{\"from\":{\"x\":" + p(38, x) + ",\"y\":" + p(2, y) + "},\"to\":{\"x\":" + p(39, x) + ",\"y\":" + p(2, y) + "},\"point\":4},{\"from\":{\"x\":" + p(37, x) + ",\"y\":" + p(2, y) + "},\"to\":{\"x\":" + p(38, x) + ",\"y\":" + p(2, y) + "},\"point\":4},{\"from\":{\"x\":" + p(36, x) + ",\"y\":" + p(2, y) + "},\"to\":{\"x\":" + p(37, x) + ",\"y\":" + p(2, y) + "},\"point\":4},{\"from\":{\"x\":" + p(35, x) + ",\"y\":" + p(2, y) + "},\"to\":{\"x\":" + p(36, x) + ",\"y\":" + p(2, y) + "},\"point\":4},{\"from\":{\"x\":" + p(34, x) + ",\"y\":" + p(2, y) + "},\"to\":{\"x\":" + p(35, x) + ",\"y\":" + p(2, y) + "},\"point\":4},{\"from\":{\"x\":" + p(33, x) + ",\"y\":" + p(2, y) + "},\"to\":{\"x\":" + p(34, x) + ",\"y\":" + p(2, y) + "},\"point\":4},{\"from\":{\"x\":" + p(32, x) + ",\"y\":" + p(2, y) + "},\"to\":{\"x\":" + p(33, x) + ",\"y\":" + p(2, y) + "},\"point\":4},{\"from\":{\"x\":" + p(31, x) + ",\"y\":" + p(2, y) + "},\"to\":{\"x\":" + p(32, x) + ",\"y\":" + p(2, y) + "},\"point\":4},{\"from\":{\"x\":" + p(30, x) + ",\"y\":" + p(2, y) + "},\"to\":{\"x\":" + p(31, x) + ",\"y\":" + p(2, y) + "},\"point\":4},{\"from\":{\"x\":" + p(29, x) + ",\"y\":" + p(2, y) + "},\"to\":{\"x\":" + p(30, x) + ",\"y\":" + p(2, y) + "},\"point\":4},{\"from\":{\"x\":" + p(28, x) + ",\"y\":" + p(2, y) + "},\"to\":{\"x\":" + p(29, x) + ",\"y\":" + p(2, y) + "},\"point\":4},{\"from\":{\"x\":" + p(27, x) + ",\"y\":" + p(2, y) + "},\"to\":{\"x\":" + p(28, x) + ",\"y\":" + p(2, y) + "},\"point\":4},{\"from\":{\"x\":" + p(26, x) + ",\"y\":" + p(2, y) + "},\"to\":{\"x\":" + p(27, x) + ",\"y\":" + p(2, y) + "},\"point\":4},{\"from\":{\"x\":" + p(25, x) + ",\"y\":" + p(2, y) + "},\"to\":{\"x\":" + p(26, x) + ",\"y\":" + p(2, y) + "},\"point\":4},{\"from\":{\"x\":" + p(24, x) + ",\"y\":" + p(2, y) + "},\"to\":{\"x\":" + p(25, x) + ",\"y\":" + p(2, y) + "},\"point\":4},{\"from\":{\"x\":" + p(23, x) + ",\"y\":" + p(2, y) + "},\"to\":{\"x\":" + p(24, x) + ",\"y\":" + p(2, y) + "},\"point\":4},{\"from\":{\"x\":" + p(22, x) + ",\"y\":" + p(2, y) + "},\"to\":{\"x\":" + p(23, x) + ",\"y\":" + p(2, y) + "},\"point\":4},{\"from\":{\"x\":" + p(21, x) + ",\"y\":" + p(2, y) + "},\"to\":{\"x\":" + p(22, x) + ",\"y\":" + p(2, y) + "},\"point\":4},{\"from\":{\"x\":" + p(20, x) + ",\"y\":" + p(2, y) + "},\"to\":{\"x\":" + p(21, x) + ",\"y\":" + p(2, y) + "},\"point\":4},{\"from\":{\"x\":" + p(19, x) + ",\"y\":" + p(2, y) + "},\"to\":{\"x\":" + p(20, x) + ",\"y\":" + p(2, y) + "},\"point\":4},{\"from\":{\"x\":" + p(18, x) + ",\"y\":" + p(2, y) + "},\"to\":{\"x\":" + p(19, x) + ",\"y\":" + p(2, y) + "},\"point\":4},{\"from\":{\"x\":" + p(17, x) + ",\"y\":" + p(2, y) + "},\"to\":{\"x\":" + p(18, x) + ",\"y\":" + p(2, y) + "},\"point\":4},{\"from\":{\"x\":" + p(16, x) + ",\"y\":" + p(2, y) + "},\"to\":{\"x\":" + p(17, x) + ",\"y\":" + p(2, y) + "},\"point\":4},{\"from\":{\"x\":" + p(15, x) + ",\"y\":" + p(2, y) + "},\"to\":{\"x\":" + p(16, x) + ",\"y\":" + p(2, y) + "},\"point\":4},{\"from\":{\"x\":" + p(14, x) + ",\"y\":" + p(2, y) + "},\"to\":{\"x\":" + p(15, x) + ",\"y\":" + p(2, y) + "},\"point\":4},{\"from\":{\"x\":" + p(13, x) + ",\"y\":" + p(2, y) + "},\"to\":{\"x\":" + p(14, x) + ",\"y\":" + p(2, y) + "},\"point\":4},{\"from\":{\"x\":" + p(12, x) + ",\"y\":" + p(2, y) + "},\"to\":{\"x\":" + p(13, x) + ",\"y\":" + p(2, y) + "},\"point\":4},{\"from\":{\"x\":" + p(11, x) + ",\"y\":" + p(2, y) + "},\"to\":{\"x\":" + p(12, x) + ",\"y\":" + p(2, y) + "},\"point\":4},{\"from\":{\"x\":" + p(10, x) + ",\"y\":" + p(2, y) + "},\"to\":{\"x\":" + p(11, x) + ",\"y\":" + p(2, y) + "},\"point\":4},{\"from\":{\"x\":" + p(9, x) + ",\"y\":" + p(2, y) + "},\"to\":{\"x\":" + p(10, x) + ",\"y\":" + p(2, y) + "},\"point\":4},{\"from\":{\"x\":" + p(8, x) + ",\"y\":" + p(2, y) + "},\"to\":{\"x\":" + p(9, x) + ",\"y\":" + p(2, y) + "},\"point\":4},{\"from\":{\"x\":" + p(7, x) + ",\"y\":" + p(2, y) + "},\"to\":{\"x\":" + p(8, x) + ",\"y\":" + p(2, y) + "},\"point\":4},{\"from\":{\"x\":" + p(5, x) + ",\"y\":" + p(4, y) + "},\"to\":{\"x\":" + p(7, x) + ",\"y\":" + p(2, y) + "},\"point\":4}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"from\":{\"x\":" + p(46, x) + ",\"y\":" + p(2, y) + "},\"to\":{\"x\":" + p(48, x) + ",\"y\":" + p(4, y) + "},\"point\":6}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"from\":{\"x\":" + p(48, x) + ",\"y\":" + p(13, y) + "},\"to\":{\"x\":" + p(49, x) + ",\"y\":" + p(16, y) + "},\"point\":5}]";
	Cmd::Exec(command);
	command = "path --add --switch=[{\"cell\":{\"x\":" + p(48, x) + ",\"y\":" + p(13, y) + "},\"point\":2}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"from\":{\"x\":" + p(48, x) + ",\"y\":" + p(13, y) + "},\"to\":{\"x\":" + p(49, x) + ",\"y\":" + p(10, y) + "},\"point\":3}]";
	Cmd::Exec(command);
	command = "path --add --switch=[{\"cell\":{\"x\":" + p(48, x) + ",\"y\":" + p(13, y) + "},\"point\":6}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"from\":{\"x\":" + p(48, x) + ",\"y\":" + p(20, y) + "},\"to\":{\"x\":" + p(49, x) + ",\"y\":" + p(23, y) + "},\"point\":5}]";
	Cmd::Exec(command);
	command = "path --add --switch=[{\"cell\":{\"x\":" + p(48, x) + ",\"y\":" + p(20, y) + "},\"point\":2}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"from\":{\"x\":" + p(47, x) + ",\"y\":" + p(2, y) + "},\"to\":{\"x\":" + p(46, x) + ",\"y\":" + p(2, y) + "},\"point\":0},{\"from\":{\"x\":" + p(48, x) + ",\"y\":" + p(2, y) + "},\"to\":{\"x\":" + p(47, x) + ",\"y\":" + p(2, y) + "},\"point\":0}]";
	Cmd::Exec(command);
	command = "path --add --switch=[{\"cell\":{\"x\":" + p(46, x) + ",\"y\":" + p(2, y) + "},\"point\":0}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"from\":{\"x\":" + p(6, x) + ",\"y\":" + p(2, y) + "},\"to\":{\"x\":" + p(7, x) + ",\"y\":" + p(2, y) + "},\"point\":4},{\"from\":{\"x\":" + p(5, x) + ",\"y\":" + p(2, y) + "},\"to\":{\"x\":" + p(6, x) + ",\"y\":" + p(2, y) + "},\"point\":4}]";
	Cmd::Exec(command);
	command = "path --add --switch=[{\"cell\":{\"x\":" + p(7, x) + ",\"y\":" + p(2, y) + "},\"point\":4}]";
	Cmd::Exec(command);
	//Game->cells[7 + x][2 + y].switches[4]->changePosition();

	command = "path --add --path=[{\"from\":{\"x\":" + p(6, x) + ",\"y\":" + p(11, y) + "},\"to\":{\"x\":" + p(5, x) + ",\"y\":" + p(8, y) + "},\"point\":2},{\"from\":{\"x\":" + p(7, x) + ",\"y\":" + p(12, y) + "},\"to\":{\"x\":" + p(6, x) + ",\"y\":" + p(11, y) + "},\"point\":1},{\"from\":{\"x\":" + p(10, x) + ",\"y\":" + p(13, y) + "},\"to\":{\"x\":" + p(7, x) + ",\"y\":" + p(12, y) + "},\"point\":1},{\"from\":{\"x\":" + p(11, x) + ",\"y\":" + p(13, y) + "},\"to\":{\"x\":" + p(10, x) + ",\"y\":" + p(13, y) + "},\"point\":0}]";
	Cmd::Exec(command);
	command = "path --add --switch=[{\"cell\":{\"x\":" + p(5, x) + ",\"y\":" + p(8, y) + "},\"point\":2}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"from\":{\"x\":" + p(11, x) + ",\"y\":" + p(13, y) + "},\"to\":{\"x\":" + p(12, x) + ",\"y\":" + p(13, y) + "},\"point\":4}]";
	Cmd::Exec(command);
	command = "path --add --switch=[{\"cell\":{\"x\":" + p(12, x) + ",\"y\":" + p(13, y) + "},\"point\":4}]";
	Cmd::Exec(command);
	Game->cells[5 + x][8 + y].switches[2]->changePosition();
	Game->cells[12 + x][13 + y].switches[4]->changePosition();

	command = "path --add --path=[{\"from\":{\"x\":" + p(5, x) + ",\"y\":" + p(25, y) + "},\"to\":{\"x\":" + p(7, x) + ",\"y\":" + p(23, y) + "},\"point\":4}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"from\":{\"x\":" + p(8, x) + ",\"y\":" + p(23, y) + "},\"to\":{\"x\":" + p(11, x) + ",\"y\":" + p(24, y) + "},\"point\":5},{\"from\":{\"x\":" + p(7, x) + ",\"y\":" + p(23, y) + "},\"to\":{\"x\":" + p(8, x) + ",\"y\":" + p(23, y) + "},\"point\":4}]";
	Cmd::Exec(command);
	command = "path --add --switch=[{\"cell\":{\"x\":" + p(11, x) + ",\"y\":" + p(24, y) + "},\"point\":5},{\"cell\":{\"x\":" + p(5, x) + ",\"y\":" + p(25, y) + "},\"point\":6}]";
	Cmd::Exec(command);

	Game->cells[11 + x][24 + y].switches[5]->changePosition();
	Game->cells[5 + x][25 + y].switches[6]->changePosition();


	//forward
	/*command = "semaphore --add --cell={\"x\":44,\"y\":2} --point=4";
	Cmd::Exec(command);
	Game->cells[44][2].semaphores[4]->SetPosition(SemaphorePosition::Stop);*/

	command = "semaphore --add --cell={\"x\":" + p(45, x) + ",\"y\":" + p(2, y) + "} --point=4";
	Cmd::Exec(command);
	Game->cells[45 + x][2 + y].semaphores[4]->SetPosition(SemaphorePosition::Go);

	command = "semaphore --add --cell={\"x\":" + p(41, x) + ",\"y\":" + p(2, y) + "} --point=4";
	Cmd::Exec(command);
	Game->cells[41 + x][2 + y].semaphores[4]->SetPosition(SemaphorePosition::Go);


	command = "semaphore --add --cell={\"x\":" + p(42, x) + ",\"y\":" + p(34, y) + "} --point=0";
	Cmd::Exec(command);
	Game->cells[42 + x][34 + y].semaphores[0]->SetPosition(SemaphorePosition::Reverse);

	command = "semaphore --add --cell={\"x\":" + p(48, x) + ",\"y\":" + p(9, y) + "} --point=6";
	Cmd::Exec(command);
	Game->cells[48 + x][9 + y].semaphores[6]->SetPosition(SemaphorePosition::Go);

	//back
	command = "semaphore --add --cell={\"x\":" + p(15, x) + ",\"y\":" + p(2, y) + "} --point=0";
	Cmd::Exec(command);
	Game->cells[15 + x][2 + y].semaphores[0]->SetPosition(SemaphorePosition::Go);

	command = "semaphore --add --cell={\"x\":" + p(5, x) + ",\"y\":" + p(30, y) + "} --point=6";
	Cmd::Exec(command);
	Game->cells[5 + x][30 + y].semaphores[6]->SetPosition(SemaphorePosition::Go);

	command = "semaphore --add --cell={\"x\":" + p(6, x) + ",\"y\":" + p(33, y) + "} --point=5";
	Cmd::Exec(command);
	Game->cells[6 + x][33 + y].semaphores[5]->SetPosition(SemaphorePosition::Reverse);

	command = "semaphore --add --cell={\"x\":" + p(6, x) + ",\"y\":" + p(33, y) + "} --point=5";
	Cmd::Exec(command);
	Game->cells[6 + x][33 + y].semaphores[5]->SetPosition(SemaphorePosition::Reverse);

	command = "semaphore --add --cell={\"x\":" + p(23, x) + ",\"y\":" + p(17, y) + "} --point=5";
	Cmd::Exec(command);
	Game->cells[23 + x][17 + y].semaphores[5]->SetPosition(SemaphorePosition::Reverse);

	Train *train = new Train();
	//train->direction = Back;
	train->direction = Forward;
	train->AddCar(new Car(Locomotive));
	train->AddCar(new Car(Locomotive));
	//train->AddCar(new Car(Switcher));
	train->AddCar(new Car(TankCar));
	train->AddCar(new Car(TankCar));
	train->AddCar(new Car(TankCar));
	train->AddCar(new Car(Locomotive));
	//train->SetPosition(Path::GetPosition({ &Game->cells[40][2], 0, 0 }, 10));
	train->SetPosition({ &Game->cells[40 + x][2 + y], 0, 0 });
	Game->AddTrain(train);

	Train *train2 = new Train();
	train2->direction = Back;
	train2->AddCar(new Car(Locomotive));
	//train2->AddCar(new Car(Switcher));
	train2->AddCar(new Car(TankCar));
	train2->AddCar(new Car(TankCar));
	train2->AddCar(new Car(TankCar));
	train2->SetPosition({ &Game->cells[5 + x][26 + y], 6, 0 });
	Game->AddTrain(train2);
}

string MapLayer::p(int p, int d)
{
	return to_string(p + d);
}
