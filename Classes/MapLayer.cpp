#include "MapLayer.h"
#include <math.h>

#include <bitset>

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

	Director::getInstance()->setProjection(Director::Projection::_2D);

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

	//testNet();
	//Cmd::Exec("save default");

	Cmd::Exec("open default");

	/*byte a = 0b00000000;
	byte b = 0b11111111;
	byte c = 0b00001111;
	byte d = 0b11110000;
	byte e = 0b10101010;
	byte f = 0b01010101;

	byte x = c & d;
	std::string str = std::bitset<8>(x).to_string(); // 00001111
	x = b & c;
	str = std::bitset<8>(x).to_string(); // 00001111
	x = e & f;
	str = std::bitset<8>(x).to_string(); // 00000000
	x = 0b111100000 ^ 0b111111000;
	str = std::bitset<9>(x).to_string(); // 00001100
	c = 0b11100000;
	x = c ^ (c & 0b00000111);
	str = std::bitset<8>(x).to_string(); // 00001100
	x = 0b1111 + 0b0000;
	str = std::bitset<4>(x).to_string();
	x = 0b0000 + 0b1111;
	str = std::bitset<4>(x).to_string();
	x = 0b1111 + 0b0011;
	str = std::bitset<4>(x).to_string();*/
}

bool MapLayer::onTouchBegan(Touch* touch, Event* event)
{
	Field *Game = Field::getInstance();
	startLocation = touch->getLocation();
	Vec2 pos = this->getPosition();
	if (Game->constuctionMode == ConstructRails || Game->constuctionMode == ConstructSemafores) {
		Vec2 d = { (-pos.x + startLocation.x) / (Game->scale * 10), (-pos.y + startLocation.y) / (Game->scale * 10) };		
		MapPoint c = { (int)round(d.x), (int)round(d.y) };
		if (Game->constuctionMode == ConstructRails) {
			if (path.Init(c)) {//, p
				CCLOG("Start --%.d,%.d", c.x, c.y);
				touchMode = BuildRails;
			}
		}
		if (Game->constuctionMode == ConstructSemafores) {
			MapIndent i = {c.x - d.x, c.y - d.y};
			if (semaphore.Show(c, i)) {
				touchMode = SemaphoreShow;
			}
		}
	}
	return true;
}

int MapLayer::getStartPoint(MapPoint c, Vec2 d)
{
	int p = -1;
	Field *Game = Field::getInstance();

	if (Game->cells[c.x][c.y].configuration == GameObjects::Configuration::Undefined) {
		bool f1 = d.y < (2 * d.x);
		bool f2 = d.y < (d.x / 2);
		bool f3 = d.y >(-d.x / 2);
		bool f4 = d.y >(-2 * d.x);
		if (f2 && f3) {
			p = 0;
		} else if (f1 && !f2) {
			p = 1;
		} else if (f4 && !f1) {
			p = 2;
		} else if (!f4 && f3) {
			p = 3;
		} else if (!f4 && !f2) {
			p = 4;
		} else if (f2 && !f1) {
			p = 5;
		} else if (f1 && !f4) {
			p = 6;
		} else if (f4 && !f3) {
			p = 7;
		}		
	}

	if (Game->cells[c.x][c.y].configuration == GameObjects::Configuration::Polar) {
		bool f1 = d.x > 0;
		bool f2 = d.y > 0;		
		if (f1 && f2) {
			p = 1;
		} else if (!f1 && f2) {
			p = 3;
		} else if (!f1 && !f2) {
			p = 5;
		} else if (f1 && !f2) {
			p = 7;
		}
	}

	if (Game->cells[c.x][c.y].configuration == GameObjects::Configuration::Ortogonal) {
		bool f1 = d.y > d.x;
		bool f2 = d.y > - d.x;
		if (!f1 && f2) {
			p = 0;
		} else if (f1 && f2) {
			p = 2;
		} else if (f1 && !f2) {
			p = 4;
		} else if (!f1 && !f2) {
			p = 6;
		}
	}
	return p;
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
			Vec2 d = { (-pos.x + loc.x) / (Game->scale * 10), (-pos.y + loc.y) / (Game->scale * 10) };
			MapPoint c = { (int)round(d.x), (int)round(d.y) };

			if (touchMode == BuildRails) {
				int p = getStartPoint(c, { (d.x - c.x), (d.y - c.y) });
				path.Show(c, p);
			}
			if (touchMode == SemaphoreShow) {				
				MapIndent i = {c.x - d.x, c.y - d.y};
				if (!semaphore.Show(c, i)) {
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

void MapLayer::renderMap()
{	
	Cmd *inst = Cmd::getInstance();
	Field *Game = Field::getInstance();
	int d = 10 * Game->scale;
	Size s = Game->sector;
	Size f = {ceil(Game->SizeX / Game->sector.width),  ceil(Game->SizeY / Game->sector.height)};
	
	sectors = new vector<Sprite*>*[f.width];
	for (int i = 0; i < f.width; ++i) {
		sectors[i] = new vector<Sprite*>[f.height];
	}
	
	for (int i = 0; i < inst->pointer; i++) {
		for (int c = 0; c < inst->history[i].elements.size(); c++) {
			Sprite *element = inst->history[i].elements[c];
			Rect rect = element->getBoundingBox();
			int x = rect.origin.x / (d * s.width);
			int y = rect.origin.y / (d * s.height);
			sectors[x][y].push_back(element);
		}		
	}
	
	Director::getInstance()->getScheduler()->performFunctionInCocosThread([&] {
		renderMapSector(0, 0);
	});
}

void MapLayer::renderMapSector(int px, int py)
{
	Field *Game = Field::getInstance();
	int d = 10 * Game->scale;	
	Size cp = Game->sector;
	if (Game->sector.width * (px + 1) > Game->SizeX) {
		cp.width = Game->SizeX - Game->sector.width * px;
	}
	if (Game->sector.height * (py + 1) > Game->SizeY) {
		cp.height = Game->SizeY - Game->sector.height * py;
	}	
	string file = "map_sector_" + to_string(px) + "_" + to_string(py) + ".png";

	if (sectors[px][py].size() > 0) {
		RenderTexture *renderTexture = RenderTexture::create(cp.width * d, cp.height * d, Texture2D::PixelFormat::RGBA8888);		
		renderTexture->setName(to_string(px) + ":" + to_string(py));
		renderTexture->setScale(1);
		renderTexture->begin();
		for (int i = 0; i < sectors[px][py].size(); i++) {
			Vec2 p = sectors[px][py][i]->getPosition();
			sectors[px][py][i]->setPosition({p.x - px * Game->sector.width * d, p.y - py * Game->sector.height * d });
			sectors[px][py][i]->visit();
			sectors[px][py][i]->setVisible(false);
		}		
		renderTexture->end();
		renderTexture->saveToFile(file, Image::Format::PNG, true, [&](RenderTexture* texture, const std::string& string) {
			vector<std::string> items = Helper::split(texture->getName(), ':');
			int x = std::stoi(items[0]);
			int y = std::stoi(items[1]);
			Field *Game = Field::getInstance();
			Size f = { ceil(Game->SizeX / Game->sector.width),  ceil(Game->SizeY / Game->sector.height) };

			if (x < f.width - 1) {
				x++;
				Director::getInstance()->getScheduler()->performFunctionInCocosThread([&, x, y] {
					renderMapSector(x, y);
				});			
			} else if (y < f.height - 1) {
				y++;
				Director::getInstance()->getScheduler()->performFunctionInCocosThread([&, y] {
					renderMapSector(0, y);
				});			
			} else {				
				onRenderMapEnd();
			}
		});		
	} else {		
		Size f = { ceil(Game->SizeX / Game->sector.width),  ceil(Game->SizeY / Game->sector.height) };
		if (px < f.width - 1) {
			px++;
			Director::getInstance()->getScheduler()->performFunctionInCocosThread([&, px, py] {
				renderMapSector(px, py);
			});
			
		} else if (py < f.height - 1) {
			py++;			
			Director::getInstance()->getScheduler()->performFunctionInCocosThread([&, py] {
				renderMapSector(0, py);
			});
		} else {
			onRenderMapEnd();
		}
	}
}

void MapLayer::onRenderMapEnd()
{
	Cmd *inst = Cmd::getInstance();
	Field *game = Field::getInstance();
	Size cp = game->sector;
	Size f = { ceil(game->SizeX / cp.width),  ceil(game->SizeY / cp.height) };

	showMap();
	
	for (int i = 0; i < inst->pointer; i++) {
		if (inst->history[i].elements.size() > 0) {
			for (int c = 0; c < inst->history[i].elements.size(); c++) {
				inst->history[i].elements[c]->removeFromParentAndCleanup(true);
			}
		}
	}
		
	for (int x = 0; x < f.width; ++x) {		
		delete[] sectors[x];
	}
	delete[] sectors;
	Cmd::clear();
}

void MapLayer::showMap()
{
	Field *game = Field::getInstance();
	Size cp = game->sector;
	Size f = { ceil(game->SizeX / cp.width),  ceil(game->SizeY / cp.height) };
	int d = 10 * game->scale;
	for (int x = 0; x < f.width; ++x) {
		for (int y = 0; y < f.height; ++y) {
			if (game->constuctionMode == ConstructionMode::ConstructOpen || sectors[x][y].size() > 0) {
				string file = "map_sector_" + to_string(x) + "_" + to_string(y) + ".png";
				Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(FileUtils::getInstance()->getWritablePath() + file);
				Sprite *sp = Sprite::createWithTexture(texture, Rect(0, 0, cp.width * d, cp.height * d));
				sp->setPosition(x * game->sector.width * d, y * game->sector.height * d);
				sp->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
				this->addChild(sp, ZIndexRailsBackground);
			}
		}
	}
}

void MapLayer::testNet()
{
	std::chrono::steady_clock::time_point start, end;
	start = std::chrono::steady_clock::now();
	int x;
	int y; 
	int dx = 5, dy = 5;
	
	int train = 1;

	//int dx = 33, dy = 17;
	for (int i = 0; i < dy; i++) {
		for (int j = 0; j < dx; j++) {
			x = j * 45;
			y = i * 43;
			testNetSector(x, y, train);
		}
	}
	
	end = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	CCLOG("%f seconds", elapsed_seconds.count());
}

void MapLayer::testNetSector(int x, int y, int train) {
	Field *Game = Field::getInstance();

	//Game->cells[18 + x][15 + y].Connect(&Game->cells[15 + x][14 + y], 1);
	string command = "path --add --path=[{\"from\":{\"x\":" + p(18, x) + ",\"y\":" + p(15, y) + "},\"to\":{\"x\":" + p(15, x) + ",\"y\":" + p(14, y) + "},\"point\":1}] param1 param2";
	Cmd::Exec(command);
	command = "path --add --path=[{\"from\":{\"x\":" + p(38, x) + ",\"y\":" + p(32, y) + "},\"to\":{\"x\":" + p(39, x) + ",\"y\":" + p(33, y) + "},\"point\":5},{\"from\":{\"x\":" + p(37, x) + ",\"y\":" + p(31, y) + "},\"to\":{\"x\":" + p(38, x) + ",\"y\":" + p(32, y) + "},\"point\":5},{\"from\":{\"x\":" + p(36, x) + ",\"y\":" + p(30, y) + "},\"to\":{\"x\":" + p(37, x) + ",\"y\":" + p(31, y) + "},\"point\":5},{\"from\":{\"x\":" + p(35, x) + ",\"y\":" + p(29, y) + "},\"to\":{\"x\":" + p(36, x) + ",\"y\":" + p(30, y) + "},\"point\":5},{\"from\":{\"x\":" + p(34, x) + ",\"y\":" + p(28, y) + "},\"to\":{\"x\":" + p(35, x) + ",\"y\":" + p(29, y) + "},\"point\":5},{\"from\":{\"x\":" + p(33, x) + ",\"y\":" + p(27, y) + "},\"to\":{\"x\":" + p(34, x) + ",\"y\":" + p(28, y) + "},\"point\":5},{\"from\":{\"x\":" + p(32, x) + ",\"y\":" + p(26, y) + "},\"to\":{\"x\":" + p(33, x) + ",\"y\":" + p(27, y) + "},\"point\":5},{\"from\":{\"x\":" + p(31, x) + ",\"y\":" + p(25, y) + "},\"to\":{\"x\":" + p(32, x) + ",\"y\":" + p(26, y) + "},\"point\":5},{\"from\":{\"x\":" + p(30, x) + ",\"y\":" + p(24, y) + "},\"to\":{\"x\":" + p(31, x) + ",\"y\":" + p(25, y) + "},\"point\":5},{\"from\":{\"x\":" + p(29, x) + ",\"y\":" + p(23, y) + "},\"to\":{\"x\":" + p(30, x) + ",\"y\":" + p(24, y) + "},\"point\":5},{\"from\":{\"x\":" + p(28, x) + ",\"y\":" + p(22, y) + "},\"to\":{\"x\":" + p(29, x) + ",\"y\":" + p(23, y) + "},\"point\":5},{\"from\":{\"x\":" + p(27, x) + ",\"y\":" + p(21, y) + "},\"to\":{\"x\":" + p(28, x) + ",\"y\":" + p(22, y) + "},\"point\":5},{\"from\":{\"x\":" + p(26, x) + ",\"y\":" + p(20, y) + "},\"to\":{\"x\":" + p(27, x) + ",\"y\":" + p(21, y) + "},\"point\":5},{\"from\":{\"x\":" + p(25, x) + ",\"y\":" + p(19, y) + "},\"to\":{\"x\":" + p(26, x) + ",\"y\":" + p(20, y) + "},\"point\":5},{\"from\":{\"x\":" + p(24, x) + ",\"y\":" + p(18, y) + "},\"to\":{\"x\":" + p(25, x) + ",\"y\":" + p(19, y) + "},\"point\":5},{\"from\":{\"x\":" + p(23, x) + ",\"y\":" + p(17, y) + "},\"to\":{\"x\":" + p(24, x) + ",\"y\":" + p(18, y) + "},\"point\":5},{\"from\":{\"x\":" + p(22, x) + ",\"y\":" + p(16, y) + "},\"to\":{\"x\":" + p(23, x) + ",\"y\":" + p(17, y) + "},\"point\":5},{\"from\":{\"x\":" + p(19, x) + ",\"y\":" + p(15, y) + "},\"to\":{\"x\":" + p(22, x) + ",\"y\":" + p(16, y) + "},\"point\":5},{\"from\":{\"x\":" + p(18, x) + ",\"y\":" + p(15, y) + "},\"to\":{\"x\":" + p(19, x) + ",\"y\":" + p(15, y) + "},\"point\":4}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"from\":{\"x\":" + p(43, x) + ",\"y\":" + p(34, y) + "},\"to\":{\"x\":" + p(46, x) + ",\"y\":" + p(33, y) + "},\"point\":3},{\"from\":{\"x\":" + p(42, x) + ",\"y\":" + p(34, y) + "},\"to\":{\"x\":" + p(43, x) + ",\"y\":" + p(34, y) + "},\"point\":4},{\"from\":{\"x\":" + p(39, x) + ",\"y\":" + p(33, y) + "},\"to\":{\"x\":" + p(42, x) + ",\"y\":" + p(34, y) + "},\"point\":4}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"from\":{\"x\":" + p(48, x) + ",\"y\":" + p(28, y) + "},\"to\":{\"x\":" + p(48, x) + ",\"y\":" + p(27, y) + "},\"point\":2},{\"from\":{\"x\":" + p(48, x) + ",\"y\":" + p(29, y) + "},\"to\":{\"x\":" + p(48, x) + ",\"y\":" + p(28, y) + "},\"point\":2},{\"from\":{\"x\":" + p(47, x) + ",\"y\":" + p(32, y) + "},\"to\":{\"x\":" + p(48, x) + ",\"y\":" + p(29, y) + "},\"point\":2},{\"from\":{\"x\":" + p(46, x) + ",\"y\":" + p(33, y) + "},\"to\":{\"x\":" + p(47, x) + ",\"y\":" + p(32, y) + "},\"point\":3}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"from\":{\"x\":" + p(48, x) + ",\"y\":" + p(5, y) + "},\"to\":{\"x\":" + p(48, x) + ",\"y\":" + p(4, y) + "},\"point\":2},{\"from\":{\"x\":" + p(48, x) + ",\"y\":" + p(6, y) + "},\"to\":{\"x\":" + p(48, x) + ",\"y\":" + p(5, y) + "},\"point\":2},{\"from\":{\"x\":" + p(48, x) + ",\"y\":" + p(7, y) + "},\"to\":{\"x\":" + p(48, x) + ",\"y\":" + p(6, y) + "},\"point\":2},{\"from\":{\"x\":" + p(48, x) + ",\"y\":" + p(8, y) + "},\"to\":{\"x\":" + p(48, x) + ",\"y\":" + p(7, y) + "},\"point\":2},{\"from\":{\"x\":" + p(48, x) + ",\"y\":" + p(9, y) + "},\"to\":{\"x\":" + p(48, x) + ",\"y\":" + p(8, y) + "},\"point\":2},{\"from\":{\"x\":" + p(48, x) + ",\"y\":" + p(10, y) + "},\"to\":{\"x\":" + p(48, x) + ",\"y\":" + p(9, y) + "},\"point\":2},{\"from\":{\"x\":" + p(48, x) + ",\"y\":" + p(11, y) + "},\"to\":{\"x\":" + p(48, x) + ",\"y\":" + p(10, y) + "},\"point\":2},{\"from\":{\"x\":" + p(48, x) + ",\"y\":" + p(12, y) + "},\"to\":{\"x\":" + p(48, x) + ",\"y\":" + p(11, y) + "},\"point\":2},{\"from\":{\"x\":" + p(48, x) + ",\"y\":" + p(13, y) + "},\"to\":{\"x\":" + p(48, x) + ",\"y\":" + p(12, y) + "},\"point\":2},{\"from\":{\"x\":" + p(48, x) + ",\"y\":" + p(14, y) + "},\"to\":{\"x\":" + p(48, x) + ",\"y\":" + p(13, y) + "},\"point\":2},{\"from\":{\"x\":" + p(48, x) + ",\"y\":" + p(15, y) + "},\"to\":{\"x\":" + p(48, x) + ",\"y\":" + p(14, y) + "},\"point\":2},{\"from\":{\"x\":" + p(48, x) + ",\"y\":" + p(16, y) + "},\"to\":{\"x\":" + p(48, x) + ",\"y\":" + p(15, y) + "},\"point\":2},{\"from\":{\"x\":" + p(48, x) + ",\"y\":" + p(17, y) + "},\"to\":{\"x\":" + p(48, x) + ",\"y\":" + p(16, y) + "},\"point\":2},{\"from\":{\"x\":" + p(48, x) + ",\"y\":" + p(18, y) + "},\"to\":{\"x\":" + p(48, x) + ",\"y\":" + p(17, y) + "},\"point\":2},{\"from\":{\"x\":" + p(48, x) + ",\"y\":" + p(19, y) + "},\"to\":{\"x\":" + p(48, x) + ",\"y\":" + p(18, y) + "},\"point\":2},{\"from\":{\"x\":" + p(48, x) + ",\"y\":" + p(20, y) + "},\"to\":{\"x\":" + p(48, x) + ",\"y\":" + p(19, y) + "},\"point\":2},{\"from\":{\"x\":" + p(48, x) + ",\"y\":" + p(21, y) + "},\"to\":{\"x\":" + p(48, x) + ",\"y\":" + p(20, y) + "},\"point\":2},{\"from\":{\"x\":" + p(48, x) + ",\"y\":" + p(22, y) + "},\"to\":{\"x\":" + p(48, x) + ",\"y\":" + p(21, y) + "},\"point\":2},{\"from\":{\"x\":" + p(48, x) + ",\"y\":" + p(23, y) + "},\"to\":{\"x\":" + p(48, x) + ",\"y\":" + p(22, y) + "},\"point\":2},{\"from\":{\"x\":" + p(48, x) + ",\"y\":" + p(24, y) + "},\"to\":{\"x\":" + p(48, x) + ",\"y\":" + p(23, y) + "},\"point\":2},{\"from\":{\"x\":" + p(48, x) + ",\"y\":" + p(25, y) + "},\"to\":{\"x\":" + p(48, x) + ",\"y\":" + p(24, y) + "},\"point\":2},{\"from\":{\"x\":" + p(48, x) + ",\"y\":" + p(26, y) + "},\"to\":{\"x\":" + p(48, x) + ",\"y\":" + p(25, y) + "},\"point\":2},{\"from\":{\"x\":" + p(48, x) + ",\"y\":" + p(27, y) + "},\"to\":{\"x\":" + p(48, x) + ",\"y\":" + p(26, y) + "},\"point\":2}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"from\":{\"x\":" + p(48, x) + ",\"y\":" + p(4, y) + "},\"to\":{\"x\":" + p(47, x) + ",\"y\":" + p(7, y) + "},\"point\":7}] --switch=[{\"cell\":{\"x\":" + p(48, x) + ",\"y\":" + p(4, y) + "},\"point\":2}]";
	Cmd::Exec(command);
	//////command = "path --add --switch=[{\"cell\":{\"x\":" + p(48, x) + ",\"y\":" + p(4, y) + "},\"point\":2}]";
	//////Cmd::Exec(command);
	command = "path --add --path=[{\"from\":{\"x\":" + p(42, x) + ",\"y\":" + p(12, y) + "},\"to\":{\"x\":" + p(41, x) + ",\"y\":" + p(13, y) + "},\"point\":7},{\"from\":{\"x\":" + p(43, x) + ",\"y\":" + p(11, y) + "},\"to\":{\"x\":" + p(42, x) + ",\"y\":" + p(12, y) + "},\"point\":7},{\"from\":{\"x\":" + p(44, x) + ",\"y\":" + p(10, y) + "},\"to\":{\"x\":" + p(43, x) + ",\"y\":" + p(11, y) + "},\"point\":7},{\"from\":{\"x\":" + p(45, x) + ",\"y\":" + p(9, y) + "},\"to\":{\"x\":" + p(44, x) + ",\"y\":" + p(10, y) + "},\"point\":7},{\"from\":{\"x\":" + p(46, x) + ",\"y\":" + p(8, y) + "},\"to\":{\"x\":" + p(45, x) + ",\"y\":" + p(9, y) + "},\"point\":7},{\"from\":{\"x\":" + p(47, x) + ",\"y\":" + p(7, y) + "},\"to\":{\"x\":" + p(46, x) + ",\"y\":" + p(8, y) + "},\"point\":7}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"from\":{\"x\":" + p(35, x) + ",\"y\":" + p(15, y) + "},\"to\":{\"x\":" + p(34, x) + ",\"y\":" + p(15, y) + "},\"point\":0},{\"from\":{\"x\":" + p(36, x) + ",\"y\":" + p(15, y) + "},\"to\":{\"x\":" + p(35, x) + ",\"y\":" + p(15, y) + "},\"point\":0},{\"from\":{\"x\":" + p(37, x) + ",\"y\":" + p(15, y) + "},\"to\":{\"x\":" + p(36, x) + ",\"y\":" + p(15, y) + "},\"point\":0},{\"from\":{\"x\":" + p(40, x) + ",\"y\":" + p(14, y) + "},\"to\":{\"x\":" + p(37, x) + ",\"y\":" + p(15, y) + "},\"point\":0},{\"from\":{\"x\":" + p(41, x) + ",\"y\":" + p(13, y) + "},\"to\":{\"x\":" + p(40, x) + ",\"y\":" + p(14, y) + "},\"point\":7}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"from\":{\"x\":" + p(29, x) + ",\"y\":" + p(15, y) + "},\"to\":{\"x\":" + p(28, x) + ",\"y\":" + p(15, y) + "},\"point\":0},{\"from\":{\"x\":" + p(30, x) + ",\"y\":" + p(15, y) + "},\"to\":{\"x\":" + p(29, x) + ",\"y\":" + p(15, y) + "},\"point\":0},{\"from\":{\"x\":" + p(31, x) + ",\"y\":" + p(15, y) + "},\"to\":{\"x\":" + p(30, x) + ",\"y\":" + p(15, y) + "},\"point\":0},{\"from\":{\"x\":" + p(32, x) + ",\"y\":" + p(15, y) + "},\"to\":{\"x\":" + p(31, x) + ",\"y\":" + p(15, y) + "},\"point\":0},{\"from\":{\"x\":" + p(33, x) + ",\"y\":" + p(15, y) + "},\"to\":{\"x\":" + p(32, x) + ",\"y\":" + p(15, y) + "},\"point\":0},{\"from\":{\"x\":" + p(34, x) + ",\"y\":" + p(15, y) + "},\"to\":{\"x\":" + p(33, x) + ",\"y\":" + p(15, y) + "},\"point\":0}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"from\":{\"x\":" + p(20, x) + ",\"y\":" + p(15, y) + "},\"to\":{\"x\":" + p(19, x) + ",\"y\":" + p(15, y) + "},\"point\":0},{\"from\":{\"x\":" + p(21, x) + ",\"y\":" + p(15, y) + "},\"to\":{\"x\":" + p(20, x) + ",\"y\":" + p(15, y) + "},\"point\":0},{\"from\":{\"x\":" + p(22, x) + ",\"y\":" + p(15, y) + "},\"to\":{\"x\":" + p(21, x) + ",\"y\":" + p(15, y) + "},\"point\":0},{\"from\":{\"x\":" + p(23, x) + ",\"y\":" + p(15, y) + "},\"to\":{\"x\":" + p(22, x) + ",\"y\":" + p(15, y) + "},\"point\":0},{\"from\":{\"x\":" + p(24, x) + ",\"y\":" + p(15, y) + "},\"to\":{\"x\":" + p(23, x) + ",\"y\":" + p(15, y) + "},\"point\":0},{\"from\":{\"x\":" + p(25, x) + ",\"y\":" + p(15, y) + "},\"to\":{\"x\":" + p(24, x) + ",\"y\":" + p(15, y) + "},\"point\":0},{\"from\":{\"x\":" + p(26, x) + ",\"y\":" + p(15, y) + "},\"to\":{\"x\":" + p(25, x) + ",\"y\":" + p(15, y) + "},\"point\":0},{\"from\":{\"x\":" + p(27, x) + ",\"y\":" + p(15, y) + "},\"to\":{\"x\":" + p(26, x) + ",\"y\":" + p(15, y) + "},\"point\":0},{\"from\":{\"x\":" + p(28, x) + ",\"y\":" + p(15, y) + "},\"to\":{\"x\":" + p(27, x) + ",\"y\":" + p(15, y) + "},\"point\":0}] --switch=[{\"cell\":{\"x\":" + p(19, x) + ",\"y\":" + p(15, y) + "},\"point\":0}]";
	Cmd::Exec(command);
	//////command = "path --add --switch=[{\"cell\":{\"x\":" + p(19, x) + ",\"y\":" + p(15, y) + "},\"point\":0}]";
	//////Cmd::Exec(command);
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
	command = "path --add --path=[{\"from\":{\"x\":" + p(48, x) + ",\"y\":" + p(13, y) + "},\"to\":{\"x\":" + p(49, x) + ",\"y\":" + p(16, y) + "},\"point\":5}] --switch=[{\"cell\":{\"x\":" + p(48, x) + ",\"y\":" + p(13, y) + "},\"point\":2}]";
	Cmd::Exec(command);
	//command = "path --add --switch=[{\"cell\":{\"x\":" + p(48, x) + ",\"y\":" + p(13, y) + "},\"point\":2}]";
	//Cmd::Exec(command);
	command = "path --add --path=[{\"from\":{\"x\":" + p(48, x) + ",\"y\":" + p(13, y) + "},\"to\":{\"x\":" + p(49, x) + ",\"y\":" + p(10, y) + "},\"point\":3}] --switch=[{\"cell\":{\"x\":" + p(48, x) + ",\"y\":" + p(13, y) + "},\"point\":6}]";
	Cmd::Exec(command);
	//command = "path --add --switch=[{\"cell\":{\"x\":" + p(48, x) + ",\"y\":" + p(13, y) + "},\"point\":6}]";
	//Cmd::Exec(command);
	command = "path --add --path=[{\"from\":{\"x\":" + p(48, x) + ",\"y\":" + p(20, y) + "},\"to\":{\"x\":" + p(49, x) + ",\"y\":" + p(23, y) + "},\"point\":5}] --switch=[{\"cell\":{\"x\":" + p(48, x) + ",\"y\":" + p(20, y) + "},\"point\":2}]";
	Cmd::Exec(command);
	//command = "path --add --switch=[{\"cell\":{\"x\":" + p(48, x) + ",\"y\":" + p(20, y) + "},\"point\":2}]";
	//Cmd::Exec(command);
	command = "path --add --path=[{\"from\":{\"x\":" + p(47, x) + ",\"y\":" + p(2, y) + "},\"to\":{\"x\":" + p(46, x) + ",\"y\":" + p(2, y) + "},\"point\":0},{\"from\":{\"x\":" + p(48, x) + ",\"y\":" + p(2, y) + "},\"to\":{\"x\":" + p(47, x) + ",\"y\":" + p(2, y) + "},\"point\":0}] --switch=[{\"cell\":{\"x\":" + p(46, x) + ",\"y\":" + p(2, y) + "},\"point\":0}]";
	Cmd::Exec(command);
	//command = "path --add --switch=[{\"cell\":{\"x\":" + p(46, x) + ",\"y\":" + p(2, y) + "},\"point\":0}]";
	//Cmd::Exec(command);
	command = "path --add --path=[{\"from\":{\"x\":" + p(6, x) + ",\"y\":" + p(2, y) + "},\"to\":{\"x\":" + p(7, x) + ",\"y\":" + p(2, y) + "},\"point\":4},{\"from\":{\"x\":" + p(5, x) + ",\"y\":" + p(2, y) + "},\"to\":{\"x\":" + p(6, x) + ",\"y\":" + p(2, y) + "},\"point\":4}] --switch=[{\"cell\":{\"x\":" + p(7, x) + ",\"y\":" + p(2, y) + "},\"point\":4}]";
	Cmd::Exec(command);
	//command = "path --add --switch=[{\"cell\":{\"x\":" + p(7, x) + ",\"y\":" + p(2, y) + "},\"point\":4}]";
	//Cmd::Exec(command);
	//Game->cells[7 + x][2 + y].switches[4]->changePosition();

	command = "path --add --path=[{\"from\":{\"x\":" + p(6, x) + ",\"y\":" + p(11, y) + "},\"to\":{\"x\":" + p(5, x) + ",\"y\":" + p(8, y) + "},\"point\":2},{\"from\":{\"x\":" + p(7, x) + ",\"y\":" + p(12, y) + "},\"to\":{\"x\":" + p(6, x) + ",\"y\":" + p(11, y) + "},\"point\":1},{\"from\":{\"x\":" + p(10, x) + ",\"y\":" + p(13, y) + "},\"to\":{\"x\":" + p(7, x) + ",\"y\":" + p(12, y) + "},\"point\":1},{\"from\":{\"x\":" + p(11, x) + ",\"y\":" + p(13, y) + "},\"to\":{\"x\":" + p(10, x) + ",\"y\":" + p(13, y) + "},\"point\":0}] --switch=[{\"cell\":{\"x\":" + p(5, x) + ",\"y\":" + p(8, y) + "},\"point\":2,\"position\":\"Diverging\"}]";
	Cmd::Exec(command);
	//////command = "path --add --switch=[{\"cell\":{\"x\":" + p(5, x) + ",\"y\":" + p(8, y) + "},\"point\":2,\"position\":\"Diverging\"}]";
	//////Cmd::Exec(command);
	command = "path --add --path=[{\"from\":{\"x\":" + p(11, x) + ",\"y\":" + p(13, y) + "},\"to\":{\"x\":" + p(12, x) + ",\"y\":" + p(13, y) + "},\"point\":4}] --switch=[{\"cell\":{\"x\":" + p(12, x) + ",\"y\":" + p(13, y) + "},\"point\":4,\"position\":\"Diverging\"}]";
	Cmd::Exec(command);
	//////command = "path --add --switch=[{\"cell\":{\"x\":" + p(12, x) + ",\"y\":" + p(13, y) + "},\"point\":4,\"position\":\"Diverging\"}]";
	//////Cmd::Exec(command);
	//Game->cells[5 + x][8 + y].switches[2]->changePosition();
	//Game->cells[12 + x][13 + y].switches[4]->changePosition();

	command = "path --add --path=[{\"from\":{\"x\":" + p(5, x) + ",\"y\":" + p(25, y) + "},\"to\":{\"x\":" + p(7, x) + ",\"y\":" + p(23, y) + "},\"point\":4}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"from\":{\"x\":" + p(8, x) + ",\"y\":" + p(23, y) + "},\"to\":{\"x\":" + p(11, x) + ",\"y\":" + p(24, y) + "},\"point\":5},{\"from\":{\"x\":" + p(7, x) + ",\"y\":" + p(23, y) + "},\"to\":{\"x\":" + p(8, x) + ",\"y\":" + p(23, y) + "},\"point\":4}] --switch=[{\"cell\":{\"x\":" + p(11, x) + ",\"y\":" + p(24, y) + "},\"point\":5,\"position\":\"Diverging\"},{\"cell\":{\"x\":" + p(5, x) + ",\"y\":" + p(25, y) + "},\"point\":6,\"position\":\"Diverging\"}]";
	Cmd::Exec(command);
	//////command = "path --add --switch=[{\"cell\":{\"x\":" + p(11, x) + ",\"y\":" + p(24, y) + "},\"point\":5,\"position\":\"Diverging\"},{\"cell\":{\"x\":" + p(5, x) + ",\"y\":" + p(25, y) + "},\"point\":6,\"position\":\"Diverging\"}]";
	//////Cmd::Exec(command);

	command = "path --add --path=[{\"from\":{\"x\":" + p(44, x) + ",\"y\":" + p(27, y) + "},\"to\":{\"x\":" + p(42, x) + ",\"y\":" + p(25, y) + "},\"point\":2},{\"from\":{\"x\":" + p(45, x) + ",\"y\":" + p(27, y) + "},\"to\":{\"x\":" + p(44, x) + ",\"y\":" + p(27, y) + "},\"point\":0},{\"from\":{\"x\":" + p(46, x) + ",\"y\":" + p(27, y) + "},\"to\":{\"x\":" + p(45, x) + ",\"y\":" + p(27, y) + "},\"point\":0},{\"from\":{\"x\":" + p(48, x) + ",\"y\":" + p(25, y) + "},\"to\":{\"x\":" + p(46, x) + ",\"y\":" + p(27, y) + "},\"point\":0}] --switch=[{\"cell\":{\"x\":" + p(48, x) + ",\"y\":" + p(25, y) + "},\"point\":2}]";
	Cmd::Exec(command);
	//////command = "path --add --switch=[{\"cell\":{\"x\":" + p(48, x) + ",\"y\":" + p(25, y) + "},\"point\":2}]";
	//////Cmd::Exec(command);
	command = "path --add --path=[{\"from\":{\"x\":" + p(35, x) + ",\"y\":" + p(23, y) + "},\"to\":{\"x\":" + p(32, x) + ",\"y\":" + p(24, y) + "},\"point\":7},{\"from\":{\"x\":" + p(36, x) + ",\"y\":" + p(23, y) + "},\"to\":{\"x\":" + p(35, x) + ",\"y\":" + p(23, y) + "},\"point\":0},{\"from\":{\"x\":" + p(37, x) + ",\"y\":" + p(23, y) + "},\"to\":{\"x\":" + p(36, x) + ",\"y\":" + p(23, y) + "},\"point\":0},{\"from\":{\"x\":" + p(38, x) + ",\"y\":" + p(23, y) + "},\"to\":{\"x\":" + p(37, x) + ",\"y\":" + p(23, y) + "},\"point\":0},{\"from\":{\"x\":" + p(39, x) + ",\"y\":" + p(23, y) + "},\"to\":{\"x\":" + p(38, x) + ",\"y\":" + p(23, y) + "},\"point\":0},{\"from\":{\"x\":" + p(40, x) + ",\"y\":" + p(23, y) + "},\"to\":{\"x\":" + p(39, x) + ",\"y\":" + p(23, y) + "},\"point\":0},{\"from\":{\"x\":" + p(42, x) + ",\"y\":" + p(25, y) + "},\"to\":{\"x\":" + p(40, x) + ",\"y\":" + p(23, y) + "},\"point\":0}]";
	Cmd::Exec(command);
	//command = "path --add --path=[{\"from\":{\"x\":" + p(35, x) + ",\"y\":" + p(24, y) + "},\"to\":{\"x\":" + p(34, x) + ",\"y\":" + p(25, y) + "},\"point\":7},{\"from\":{\"x\":" + p(38, x) + ",\"y\":" + p(23, y) + "},\"to\":{\"x\":" + p(35, x) + ",\"y\":" + p(24, y) + "},\"point\":7},{\"from\":{\"x\":" + p(39, x) + ",\"y\":" + p(23, y) + "},\"to\":{\"x\":" + p(38, x) + ",\"y\":" + p(23, y) + "},\"point\":0},{\"from\":{\"x\":" + p(48, x) + ",\"y\":" + p(23, y) + "}\,\"to\":{\"x\":" + p(39, x) + ",\"y\":" + p(23, y) + "},\"point\":0},{\"from\":{\"x\":" + p(42, x) + ",\"y\":" + p(25, y) + "},\"to\":{\"x\":" + p(40, x) + ",\"y\":" + p(23, y) + "},\"point\":0}]";
	//Cmd::Exec(command);
		//Game->cells[11 + x][24 + y].switches[5]->changePosition();
	//Game->cells[5 + x][25 + y].switches[6]->changePosition();


	//forward
	/*command = "semaphore --add --cell={\"x\":44,\"y\":2} --point=4";
	Cmd::Exec(command);
	Game->cells[44][2].semaphores[4]->SetPosition(SemaphorePosition::Stop);*/

	command = "semaphore --add --cell={\"x\":" + p(45, x) + ",\"y\":" + p(2, y) + "} --point=4";
	Cmd::Exec(command);
	//Game->cells[45 + x][2 + y].semaphores[4]->SetPosition(SemaphorePosition::Go);

	command = "semaphore --add --cell={\"x\":" + p(41, x) + ",\"y\":" + p(2, y) + "} --point=4";
	Cmd::Exec(command);
	//Game->cells[41 + x][2 + y].semaphores[4]->SetPosition(SemaphorePosition::Go);


	command = "semaphore --add --cell={\"x\":" + p(42, x) + ",\"y\":" + p(34, y) + "} --point=0 --position=Reverse";
	Cmd::Exec(command);
	//Game->cells[42 + x][34 + y].semaphores[0]->SetPosition(SemaphorePosition::Reverse);

	command = "semaphore --add --cell={\"x\":" + p(48, x) + ",\"y\":" + p(9, y) + "} --point=6 --position=Go";
	Cmd::Exec(command);
	//Game->cells[48 + x][9 + y].semaphores[6]->SetPosition(SemaphorePosition::Go);

	//back
	command = "semaphore --add --cell={\"x\":" + p(15, x) + ",\"y\":" + p(2, y) + "} --point=0";
	Cmd::Exec(command);
	//Game->cells[15 + x][2 + y].semaphores[0]->SetPosition(SemaphorePosition::Go);

	command = "semaphore --add --cell={\"x\":" + p(5, x) + ",\"y\":" + p(30, y) + "} --point=6";
	Cmd::Exec(command);
	//Game->cells[5 + x][30 + y].semaphores[6]->SetPosition(SemaphorePosition::Go);

	command = "semaphore --add --cell={\"x\":" + p(6, x) + ",\"y\":" + p(33, y) + "} --point=5 --position=Reverse";
	Cmd::Exec(command);
	//Game->cells[6 + x][33 + y].semaphores[5]->SetPosition(SemaphorePosition::Reverse);

	//command = "semaphore --add --cell={\"x\":" + p(6, x) + ",\"y\":" + p(33, y) + "} --point=5 --position=Reverse";
	//Cmd::Exec(command);
	//Game->cells[6 + x][33 + y].semaphores[5]->SetPosition(SemaphorePosition::Reverse);

	command = "semaphore --add --cell={\"x\":" + p(23, x) + ",\"y\":" + p(17, y) + "} --point=5 --position=Reverse param3 param4";
	Cmd::Exec(command);
	//Game->cells[23 + x][17 + y].semaphores[5]->SetPosition(SemaphorePosition::Reverse);
	
	command = "train --add --id=" + to_string(train++) + " --position={\"cell\":{\"x\":" + p(40, x) + ",\"y\":" + p(2, y) + "},\"point\":0,\"indent\":0} --direction=Forward Locomotive Locomotive TankCar TankCar TankCar Locomotive";
	Cmd::Exec(command);

	command = "train --add --id=" + to_string(train++) + " --position={\"cell\":{\"x\":" + p(5, x) + ",\"y\":" + p(26, y) + "},\"point\":6,\"indent\":0} --direction=Back Switcher TankCar TankCar TankCar Switcher";
	Cmd::Exec(command);

	/*Train *train = new Train();
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
	Game->AddTrain(train);*/

	/*Train *train2 = new Train();
	train2->direction = Back;
	train2->AddCar(new Car(Locomotive));
	//train2->AddCar(new Car(Switcher));
	train2->AddCar(new Car(TankCar));
	train2->AddCar(new Car(TankCar));
	train2->AddCar(new Car(TankCar));
	train2->SetPosition({ &Game->cells[5 + x][26 + y], 6, 0 });
	Game->AddTrain(train2);*/
}

string MapLayer::p(int p, int d)
{
	return to_string(p + d);
}
