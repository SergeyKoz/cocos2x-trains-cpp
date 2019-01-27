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

	//testNet(); Cmd::Exec("save default");

	Cmd::Exec("open default");

	/*int program[24][12] = {
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },

		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },

		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
	};
	Field::getInstance()->cells[23][17].semaphores[5]->setProgram(program);*/
			
	/*byte a = 0b00000000;
	byte b = 0b11111111;
	byte c = 0b00001111;
	byte d = 0b11110000;
	byte e = 0b10101010;
	byte f = 0b01010101;
	byte x = c & d;
	std::string str = std::bitset<8>(x).to_string(); //0b00001111 & 0b11110000 = 00000000
	x = b & c;
	str = std::bitset<8>(x).to_string(); // 0b11111111 & 0b00001111 = 00001111
	x = e & f;
	str = std::bitset<8>(x).to_string(); // 0b10101010 & 0b01010101 = 00000000
	x = 0b111100000 ^ 0b111111000;
	str = std::bitset<9>(x).to_string(); // 00001100
	x = 0b111111000 ^ 0b111100000;
	str = std::bitset<9>(x).to_string(); // 00001100
	x = 0b11110000 ^ 0b11100101; // 00010101
	str = std::bitset<8>(x).to_string();
	x = 0b00010101 & 0b11100101; // 00000101
	str = std::bitset<8>(x).to_string();
	byte _c = 0b11110000;
	byte _d = 0b11100101;
	x = (_c ^ _d) & _d; // 00000101
	str = std::bitset<8>(x).to_string();
	x = 0b11110000 ^ 0b00000101; // 0b11110101
	str = std::bitset<8>(x).to_string();
	x = 0b11110000 - 0b11100101; // 0b11100101
	str = std::bitset<8>(x).to_string();
	x = 0b11110000 ^ 0b00110011;
	str = std::bitset<9>(x).to_string(); 
	x = x ^ 0b00110011;
	str = std::bitset<9>(x).to_string(); // 00110000
	c = 0b11100111;
	x = c ^ 0b00000111;	
	str = std::bitset<8>(x).to_string(); // 00001100
	x = 0b1111 + 0b0000;
	str = std::bitset<4>(x).to_string();
	x = 0b0000 + 0b1111;
	str = std::bitset<4>(x).to_string();
	x = 0b1001 | 0b1011;
	str = std::bitset<4>(x).to_string();
	x = 0b1001 ^ 0b1011;
	str = std::bitset<8>(x).to_string();
	x = 0b1011 ^ 0b1001;
	str = std::bitset<8>(x).to_string();

	x = 0b10 | 0b0;
	str = std::bitset<4>(x).to_string();

	x = 0b10 | 0b1;
	str = std::bitset<4>(x).to_string();

	x = 0b0 | 0b10;
	str = std::bitset<4>(x).to_string();

	x = 0b1 | 0b10;
	str = std::bitset<4>(x).to_string();*/
}

/*void MapLayer::debugBoard(Sprite *Crossover, Color4F color)
{
	this->addChild(Crossover, ZIndexRails);

	Rect s = Crossover->boundingBox();

	DrawNode *rectNode = DrawNode::create();
	rectNode->drawRect(Vec2(s.origin.x, s.origin.y), Vec2(s.origin.x + s.size.width, s.origin.y + s.size.height), color);
	//this->addChild(rectNode);

}*/

bool MapLayer::onTouchBegan(Touch* touch, Event* event)
{
	Field *Game = Field::getInstance();
	startLocation = touch->getLocation();
	Vec2 pos = this->getPosition();
	if (Game->constuctionMode == ConstructRails || Game->constuctionMode == ConstructSemafores) {
		Vec2 d = { (-pos.x + startLocation.x) / (Game->scale * 10), (-pos.y + startLocation.y) / (Game->scale * 10) };		
		MapPoint c = { (int)round(d.x), (int)round(d.y) };
		CCLOG("Start --%.d,%.d", c.x, c.y);
		if (Game->constuctionMode == ConstructRails) {
			if (path.Init(c)) {				
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
	
	sectors = new vector<Sprite*>**[3];
	for (int i = 0; i < 3; ++i) {
		sectors[i] = new vector<Sprite*>*[f.width];
		for (int c = 0; c < f.width; ++c) {
			sectors[i][c] = new vector<Sprite*>[f.height];
		}
	}
	
	
	for (int i = 0; i < inst->pointer; i++) {
		for (int c = 0; c < inst->history[i].elements.size(); c++) {
			CommandsElement *element = &inst->history[i].elements[c];			
			Rect rect = element->image->getBoundingBox();
			int x = rect.origin.x / (d * s.width);
			int y = rect.origin.y / (d * s.height);
			sectors[element->ZIndex][x][y].push_back(element->image);
			int _x = (rect.origin.x + rect.size.width) / (d * s.width);
			int _y = (rect.origin.y + rect.size.height) / (d * s.height);
			if (_x > x) {
				sectors[element->ZIndex][_x][y].push_back(element->image);
			}
			if (_y > y) {
				sectors[element->ZIndex][x][_y].push_back(element->image);
			}
			if (_y > y && _x > x) {
				sectors[element->ZIndex][_x][_y].push_back(element->image);
			}
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
	
	if (sectors[0][px][py].size() > 0 || sectors[1][px][py].size() > 0 || sectors[2][px][py].size() > 0) {
		RenderTexture *renderTexture = RenderTexture::create(cp.width * d, cp.height * d, Texture2D::PixelFormat::RGBA8888);		
		renderTexture->setName(to_string(px) + ":" + to_string(py));
		renderTexture->setScale(1);
		renderTexture->begin();		
		for (int z = 0; z < 3; ++z) {
			for (int i = 0; i < sectors[z][px][py].size(); i++) {
				Vec2 p = sectors[z][px][py][i]->getPosition();
				sectors[z][px][py][i]->setVisible(true);
				sectors[z][px][py][i]->setPosition({ p.x - px * Game->sector.width * d, p.y - py * Game->sector.height * d });
				sectors[z][px][py][i]->visit();
				sectors[z][px][py][i]->setVisible(false);
				sectors[z][px][py][i]->setPosition(p);
			}
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
				inst->history[i].elements[c].image->removeFromParentAndCleanup(true);
			}
		}
	}
	for (int z = 0; z < 3; ++z) {
		for (int x = 0; x < f.width; ++x) {
			delete[] sectors[z][x];
		}
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
			if (game->constuctionMode == ConstructionMode::ConstructOpen || (sectors[0][x][y].size() > 0 || sectors[1][x][y].size() > 0 || sectors[2][x][y].size() > 0)) {
				string file = "map_sector_" + to_string(x) + "_" + to_string(y) + ".png";
				Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(FileUtils::getInstance()->getWritablePath() + file);
				Sprite *sp = Sprite::createWithTexture(texture, Rect(0, 0, cp.width * d, cp.height * d));
				sp->setPosition(x * game->sector.width * d, y * game->sector.height * d);
				sp->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
				this->addChild(sp, ZIndexBackground);
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
	int dx = 2, dy = 1;
	
	int train = 1;
	int station = 1;

	//int dx = 33, dy = 17;
	for (int i = 0; i < dy; i++) {
		for (int j = 0; j < dx; j++) {
			x = j * 45;
			y = i * 43;
			testNetSector(x, y, train, station);
		}
	}
	/*string command;
	command = "station --add --id=" + to_string(station++) + " --cell={\"x\":107,\"y\":5} --angle=270"; //180
	Cmd::Exec(command);
	command = "station --add --id=" + to_string(station++) + " --cell={\"x\":112,\"y\":15} --angle=270";
	Cmd::Exec(command);
	command = "station --add --id=" + to_string(station++) + " --cell={\"x\":117,\"y\":25} --angle=270";
	Cmd::Exec(command);
	command = "station --add --id=" + to_string(station++) + " --cell={\"x\":122,\"y\":35} --angle=270";
	Cmd::Exec(command);
	command = "station --add --id=" + to_string(station++) + " --cell={\"x\":127,\"y\":45} --angle=270";
	Cmd::Exec(command);
	command = "station --add --id=" + to_string(station++) + " --cell={\"x\":132,\"y\":55} --angle=270";
	Cmd::Exec(command);
	command = "station --add --id=" + to_string(station++) + " --cell={\"x\":137,\"y\":65} --angle=270";
	Cmd::Exec(command);*/
	
	end = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	CCLOG("%f seconds", elapsed_seconds.count());
}

void MapLayer::testNetSector(int x, int y, int train, int station) {
	Field *Game = Field::getInstance();

	string command;
	//Game->cells[18 + x][15 + y].Connect(&Game->cells[15 + x][14 + y], 1);	
	command = "path --add --path=[{\"cell\":{\"x\":" + p(15, x) + ",\"y\":" + p(13, y) + "},\"element\":\"BaseCircleSect2\",\"point\":1}] param1 param2"; Cmd::Exec(command);
	command = "path --add --path=[{\"cell\":{\"x\":" + p(39, x) + ",\"y\":" + p(33, y) + "},\"element\":\"Item45\",\"point\":5},{\"cell\":{\"x\":" + p(38, x) + ",\"y\":" + p(32, y) + "},\"element\":\"Item45\",\"point\":5},{\"cell\":{\"x\":" + p(37, x) + ",\"y\":" + p(31, y) + "},\"element\":\"Item45\",\"point\":5},{\"cell\":{\"x\":" + p(36, x) + ",\"y\":" + p(30, y) + "},\"element\":\"Item45\",\"point\":5},{\"cell\":{\"x\":" + p(35, x) + ",\"y\":" + p(29, y) + "},\"element\":\"Item45\",\"point\":5},{\"cell\":{\"x\":" + p(34, x) + ",\"y\":" + p(28, y) + "},\"element\":\"Item45\",\"point\":5},{\"cell\":{\"x\":" + p(33, x) + ",\"y\":" + p(27, y) + "},\"element\":\"Item45\",\"point\":5},{\"cell\":{\"x\":" + p(32, x) + ",\"y\":" + p(26, y) + "},\"element\":\"Item45\",\"point\":5},{\"cell\":{\"x\":" + p(31, x) + ",\"y\":" + p(25, y) + "},\"element\":\"Item45\",\"point\":5},{\"cell\":{\"x\":" + p(30, x) + ",\"y\":" + p(24, y) + "},\"element\":\"Item45\",\"point\":5},{\"cell\":{\"x\":" + p(29, x) + ",\"y\":" + p(23, y) + "},\"element\":\"Item45\",\"point\":5},{\"cell\":{\"x\":" + p(28, x) + ",\"y\":" + p(22, y) + "},\"element\":\"Item45\",\"point\":5},{\"cell\":{\"x\":" + p(27, x) + ",\"y\":" + p(21, y) + "},\"element\":\"Item45\",\"point\":5},{\"cell\":{\"x\":" + p(26, x) + ",\"y\":" + p(20, y) + "},\"element\":\"Item45\",\"point\":5},{\"cell\":{\"x\":" + p(25, x) + ",\"y\":" + p(19, y) + "},\"element\":\"Item45\",\"point\":5},{\"cell\":{\"x\":" + p(24, x) + ",\"y\":" + p(18, y) + "},\"element\":\"Item45\",\"point\":5},{\"cell\":{\"x\":" + p(23, x) + ",\"y\":" + p(17, y) + "},\"element\":\"Item45\",\"point\":5},{\"cell\":{\"x\":" + p(22, x) + ",\"y\":" + p(16, y) + "},\"element\":\"Item45\",\"point\":5},{\"cell\":{\"x\":" + p(18, x) + ",\"y\":" + p(14, y) + "},\"element\":\"BaseCircleSect6\",\"point\":0}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"cell\":{\"x\":" + p(46, x) + ",\"y\":" + p(33, y) + "},\"element\":\"BaseCircleSect1\",\"point\":3},{\"cell\":{\"x\":" + p(43, x) + ",\"y\":" + p(34, y) + "},\"element\":\"Horizontal\",\"point\":4},{\"cell\":{\"x\":" + p(42, x) + ",\"y\":" + p(34, y) + "},\"element\":\"BaseCircleSect2\",\"point\":4}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"cell\":{\"x\":" + p(48, x) + ",\"y\":" + p(27, y) + "},\"element\":\"Vertical\",\"point\":2},{\"cell\":{\"x\":" + p(48, x) + ",\"y\":" + p(28, y) + "},\"element\":\"Vertical\",\"point\":2},{\"cell\":{\"x\":" + p(48, x) + ",\"y\":" + p(29, y) + "},\"element\":\"BaseCircleSect0\",\"point\":2},{\"cell\":{\"x\":" + p(47, x) + ",\"y\":" + p(32, y) + "},\"element\":\"Item135\",\"point\":3}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"cell\":{\"x\":" + p(48, x) + ",\"y\":" + p(3, y) + "},\"element\":\"Vertical\",\"point\":2},{\"cell\":{\"x\":" + p(48, x) + ",\"y\":" + p(4, y) + "},\"element\":\"Vertical\",\"point\":2},{\"cell\":{\"x\":" + p(48, x) + ",\"y\":" + p(5, y) + "},\"element\":\"Vertical\",\"point\":2},{\"cell\":{\"x\":" + p(48, x) + ",\"y\":" + p(6, y) + "},\"element\":\"Vertical\",\"point\":2},{\"cell\":{\"x\":" + p(48, x) + ",\"y\":" + p(7, y) + "},\"element\":\"Vertical\",\"point\":2},{\"cell\":{\"x\":" + p(48, x) + ",\"y\":" + p(8, y) + "},\"element\":\"Vertical\",\"point\":2},{\"cell\":{\"x\":" + p(48, x) + ",\"y\":" + p(9, y) + "},\"element\":\"Vertical\",\"point\":2},{\"cell\":{\"x\":" + p(48, x) + ",\"y\":" + p(10, y) + "},\"element\":\"Vertical\",\"point\":2},{\"cell\":{\"x\":" + p(48, x) + ",\"y\":" + p(11, y) + "},\"element\":\"Vertical\",\"point\":2},{\"cell\":{\"x\":" + p(48, x) + ",\"y\":" + p(12, y) + "},\"element\":\"Vertical\",\"point\":2},{\"cell\":{\"x\":" + p(48, x) + ",\"y\":" + p(13, y) + "},\"element\":\"Vertical\",\"point\":2},{\"cell\":{\"x\":" + p(48, x) + ",\"y\":" + p(14, y) + "},\"element\":\"Vertical\",\"point\":2},{\"cell\":{\"x\":" + p(48, x) + ",\"y\":" + p(15, y) + "},\"element\":\"Vertical\",\"point\":2},{\"cell\":{\"x\":" + p(48, x) + ",\"y\":" + p(16, y) + "},\"element\":\"Vertical\",\"point\":2},{\"cell\":{\"x\":" + p(48, x) + ",\"y\":" + p(17, y) + "},\"element\":\"Vertical\",\"point\":2},{\"cell\":{\"x\":" + p(48, x) + ",\"y\":" + p(18, y) + "},\"element\":\"Vertical\",\"point\":2},{\"cell\":{\"x\":" + p(48, x) + ",\"y\":" + p(19, y) + "},\"element\":\"Vertical\",\"point\":2},{\"cell\":{\"x\":" + p(48, x) + ",\"y\":" + p(20, y) + "},\"element\":\"Vertical\",\"point\":2},{\"cell\":{\"x\":" + p(48, x) + ",\"y\":" + p(21, y) + "},\"element\":\"Vertical\",\"point\":2},{\"cell\":{\"x\":" + p(48, x) + ",\"y\":" + p(22, y) + "},\"element\":\"Vertical\",\"point\":2},{\"cell\":{\"x\":" + p(48, x) + ",\"y\":" + p(23, y) + "},\"element\":\"Vertical\",\"point\":2},{\"cell\":{\"x\":" + p(48, x) + ",\"y\":" + p(24, y) + "},\"element\":\"Vertical\",\"point\":2},{\"cell\":{\"x\":" + p(48, x) + ",\"y\":" + p(25, y) + "},\"element\":\"Vertical\",\"point\":2},{\"cell\":{\"x\":" + p(48, x) + ",\"y\":" + p(26, y) + "},\"element\":\"Vertical\",\"point\":2}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"cell\":{\"x\":" + p(47, x) + ",\"y\":" + p(7, y) + "},\"element\":\"BaseCircleSect0\",\"point\":7}] --switch=[{\"cell\":{\"x\":" + p(48, x) + ",\"y\":" + p(4, y) + "},\"point\":2}]";//
	Cmd::Exec(command);
	command = "path --add --path=[{\"cell\":{\"x\":" + p(41, x) + ",\"y\":" + p(13, y) + "},\"element\":\"Item135\",\"point\":7},{\"cell\":{\"x\":" + p(42, x) + ",\"y\":" + p(12, y) + "},\"element\":\"Item135\",\"point\":7},{\"cell\":{\"x\":" + p(43, x) + ",\"y\":" + p(11, y) + "},\"element\":\"Item135\",\"point\":7},{\"cell\":{\"x\":" + p(44, x) + ",\"y\":" + p(10, y) + "},\"element\":\"Item135\",\"point\":7},{\"cell\":{\"x\":" + p(45, x) + ",\"y\":" + p(9, y) + "},\"element\":\"Item135\",\"point\":7},{\"cell\":{\"x\":" + p(46, x) + ",\"y\":" + p(8, y) + "},\"element\":\"Item135\",\"point\":7}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"cell\":{\"x\":" + p(34, x) + ",\"y\":" + p(14, y) + "},\"element\":\"Horizontal\",\"point\":0},{\"cell\":{\"x\":" + p(35, x) + ",\"y\":" + p(14, y) + "},\"element\":\"Horizontal\",\"point\":0},{\"cell\":{\"x\":" + p(36, x) + ",\"y\":" + p(14, y) + "},\"element\":\"Horizontal\",\"point\":0},{\"cell\":{\"x\":" + p(37, x) + ",\"y\":" + p(14, y) + "},\"element\":\"Horizontal\",\"point\":0},{\"cell\":{\"x\":" + p(41, x) + ",\"y\":" + p(13, y) + "},\"element\":\"BaseCircleSect1\",\"point\":3}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"cell\":{\"x\":" + p(28, x) + ",\"y\":" + p(14, y) + "},\"element\":\"Horizontal\",\"point\":0},{\"cell\":{\"x\":" + p(29, x) + ",\"y\":" + p(14, y) + "},\"element\":\"Horizontal\",\"point\":0},{\"cell\":{\"x\":" + p(30, x) + ",\"y\":" + p(14, y) + "},\"element\":\"Horizontal\",\"point\":0},{\"cell\":{\"x\":" + p(31, x) + ",\"y\":" + p(14, y) + "},\"element\":\"Horizontal\",\"point\":0},{\"cell\":{\"x\":" + p(32, x) + ",\"y\":" + p(14, y) + "},\"element\":\"Horizontal\",\"point\":0},{\"cell\":{\"x\":" + p(33, x) + ",\"y\":" + p(14, y) + "},\"element\":\"Horizontal\",\"point\":0}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"cell\":{\"x\":" + p(18, x) + ",\"y\":" + p(14, y) + "},\"element\":\"Horizontal\",\"point\":0},{\"cell\":{\"x\":" + p(19, x) + ",\"y\":" + p(14, y) + "},\"element\":\"Horizontal\",\"point\":0},{\"cell\":{\"x\":" + p(20, x) + ",\"y\":" + p(14, y) + "},\"element\":\"Horizontal\",\"point\":0},{\"cell\":{\"x\":" + p(21, x) + ",\"y\":" + p(14, y) + "},\"element\":\"Horizontal\",\"point\":0},{\"cell\":{\"x\":" + p(22, x) + ",\"y\":" + p(14, y) + "},\"element\":\"Horizontal\",\"point\":0},{\"cell\":{\"x\":" + p(23, x) + ",\"y\":" + p(14, y) + "},\"element\":\"Horizontal\",\"point\":0},{\"cell\":{\"x\":" + p(24, x) + ",\"y\":" + p(14, y) + "},\"element\":\"Horizontal\",\"point\":0},{\"cell\":{\"x\":" + p(25, x) + ",\"y\":" + p(14, y) + "},\"element\":\"Horizontal\",\"point\":0},{\"cell\":{\"x\":" + p(26, x) + ",\"y\":" + p(14, y) + "},\"element\":\"Horizontal\",\"point\":0},{\"cell\":{\"x\":" + p(27, x) + ",\"y\":" + p(14, y) + "},\"element\":\"Horizontal\",\"point\":0}] --switch=[{\"cell\":{\"x\":" + p(18, x) + ",\"y\":" + p(14, y) + "},\"point\":0}]";//
	Cmd::Exec(command);
	command = "path --add --path=[{\"cell\":{\"x\":" + p(8, x) + ",\"y\":" + p(14, y) + "},\"element\":\"Item135\",\"point\":7},{\"cell\":{\"x\":" + p(9, x) + ",\"y\":" + p(13, y) + "},\"element\":\"BaseCircleSect5\",\"point\":7},{\"cell\":{\"x\":" + p(12, x) + ",\"y\":" + p(12, y) + "},\"element\":\"BaseCircleSect6\",\"point\":0}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"cell\":{\"x\":" + p(7, x) + ",\"y\":" + p(17, y) + "},\"element\":\"BaseCircleSect4\",\"point\":6}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"cell\":{\"x\":" + p(21, x) + ",\"y\":" + p(33, y) + "},\"element\":\"Item45\",\"point\":5},{\"cell\":{\"x\":" + p(20, x) + ",\"y\":" + p(32, y) + "},\"element\":\"Item45\",\"point\":5},{\"cell\":{\"x\":" + p(19, x) + ",\"y\":" + p(31, y) + "},\"element\":\"Item45\",\"point\":5},{\"cell\":{\"x\":" + p(18, x) + ",\"y\":" + p(30, y) + "},\"element\":\"Item45\",\"point\":5},{\"cell\":{\"x\":" + p(17, x) + ",\"y\":" + p(29, y) + "},\"element\":\"Item45\",\"point\":5},{\"cell\":{\"x\":" + p(16, x) + ",\"y\":" + p(28, y) + "},\"element\":\"Item45\",\"point\":5},{\"cell\":{\"x\":" + p(15, x) + ",\"y\":" + p(27, y) + "},\"element\":\"Item45\",\"point\":5},{\"cell\":{\"x\":" + p(14, x) + ",\"y\":" + p(26, y) + "},\"element\":\"Item45\",\"point\":5},{\"cell\":{\"x\":" + p(13, x) + ",\"y\":" + p(25, y) + "},\"element\":\"Item45\",\"point\":5},{\"cell\":{\"x\":" + p(12, x) + ",\"y\":" + p(24, y) + "},\"element\":\"Item45\",\"point\":5},{\"cell\":{\"x\":" + p(11, x) + ",\"y\":" + p(23, y) + "},\"element\":\"Item45\",\"point\":5},{\"cell\":{\"x\":" + p(10, x) + ",\"y\":" + p(22, y) + "},\"element\":\"Item45\",\"point\":5},{\"cell\":{\"x\":" + p(9, x) + ",\"y\":" + p(21, y) + "},\"element\":\"Item45\",\"point\":5},{\"cell\":{\"x\":" + p(8, x) + ",\"y\":" + p(20, y) + "},\"element\":\"BaseCircleSect3\",\"point\":5}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"cell\":{\"x\":" + p(21, x) + ",\"y\":" + p(39, y) + "},\"element\":\"BaseCircleSect0\",\"point\":7},{\"cell\":{\"x\":" + p(22, x) + ",\"y\":" + p(36, y) + "},\"element\":\"BaseCircleSect7\",\"point\":6}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"cell\":{\"x\":" + p(17, x) + ",\"y\":" + p(41, y) + "},\"element\":\"BaseCircleSect1\",\"point\":0},{\"cell\":{\"x\":" + p(20, x) + ",\"y\":" + p(40, y) + "},\"element\":\"Item135\",\"point\":7}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"cell\":{\"x\":" + p(5, x) + ",\"y\":" + p(29, y) + "},\"element\":\"BaseCircleSect3\",\"point\":2},{\"cell\":{\"x\":" + p(6, x) + ",\"y\":" + p(32, y) + "},\"element\":\"Item45\",\"point\":1},{\"cell\":{\"x\":" + p(7, x) + ",\"y\":" + p(33, y) + "},\"element\":\"Item45\",\"point\":1},{\"cell\":{\"x\":" + p(8, x) + ",\"y\":" + p(34, y) + "},\"element\":\"Item45\",\"point\":1},{\"cell\":{\"x\":" + p(9, x) + ",\"y\":" + p(35, y) + "},\"element\":\"Item45\",\"point\":1},{\"cell\":{\"x\":" + p(10, x) + ",\"y\":" + p(36, y) + "},\"element\":\"Item45\",\"point\":1},{\"cell\":{\"x\":" + p(11, x) + ",\"y\":" + p(37, y) + "},\"element\":\"Item45\",\"point\":1},{\"cell\":{\"x\":" + p(12, x) + ",\"y\":" + p(38, y) + "},\"element\":\"Item45\",\"point\":1},{\"cell\":{\"x\":" + p(13, x) + ",\"y\":" + p(39, y) + "},\"element\":\"Item45\",\"point\":1},{\"cell\":{\"x\":" + p(14, x) + ",\"y\":" + p(40, y) + "},\"element\":\"BaseCircleSect2\",\"point\":1}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"cell\":{\"x\":" + p(5, x) + ",\"y\":" + p(3, y) + "},\"element\":\"Vertical\",\"point\":2},{\"cell\":{\"x\":" + p(5, x) + ",\"y\":" + p(4, y) + "},\"element\":\"Vertical\",\"point\":2},{\"cell\":{\"x\":" + p(5, x) + ",\"y\":" + p(5, y) + "},\"element\":\"Vertical\",\"point\":2},{\"cell\":{\"x\":" + p(5, x) + ",\"y\":" + p(6, y) + "},\"element\":\"Vertical\",\"point\":2},{\"cell\":{\"x\":" + p(5, x) + ",\"y\":" + p(7, y) + "},\"element\":\"Vertical\",\"point\":2},{\"cell\":{\"x\":" + p(5, x) + ",\"y\":" + p(8, y) + "},\"element\":\"Vertical\",\"point\":2},{\"cell\":{\"x\":" + p(5, x) + ",\"y\":" + p(9, y) + "},\"element\":\"Vertical\",\"point\":2},{\"cell\":{\"x\":" + p(5, x) + ",\"y\":" + p(10, y) + "},\"element\":\"Vertical\",\"point\":2},{\"cell\":{\"x\":" + p(5, x) + ",\"y\":" + p(11, y) + "},\"element\":\"Vertical\",\"point\":2},{\"cell\":{\"x\":" + p(5, x) + ",\"y\":" + p(12, y) + "},\"element\":\"Vertical\",\"point\":2},{\"cell\":{\"x\":" + p(5, x) + ",\"y\":" + p(13, y) + "},\"element\":\"Vertical\",\"point\":2},{\"cell\":{\"x\":" + p(5, x) + ",\"y\":" + p(14, y) + "},\"element\":\"Vertical\",\"point\":2},{\"cell\":{\"x\":" + p(5, x) + ",\"y\":" + p(15, y) + "},\"element\":\"Vertical\",\"point\":2},{\"cell\":{\"x\":" + p(5, x) + ",\"y\":" + p(16, y) + "},\"element\":\"Vertical\",\"point\":2},{\"cell\":{\"x\":" + p(5, x) + ",\"y\":" + p(17, y) + "},\"element\":\"Vertical\",\"point\":2},{\"cell\":{\"x\":" + p(5, x) + ",\"y\":" + p(18, y) + "},\"element\":\"Vertical\",\"point\":2},{\"cell\":{\"x\":" + p(5, x) + ",\"y\":" + p(19, y) + "},\"element\":\"Vertical\",\"point\":2},{\"cell\":{\"x\":" + p(5, x) + ",\"y\":" + p(20, y) + "},\"element\":\"Vertical\",\"point\":2},{\"cell\":{\"x\":" + p(5, x) + ",\"y\":" + p(21, y) + "},\"element\":\"Vertical\",\"point\":2},{\"cell\":{\"x\":" + p(5, x) + ",\"y\":" + p(22, y) + "},\"element\":\"Vertical\",\"point\":2},{\"cell\":{\"x\":" + p(5, x) + ",\"y\":" + p(23, y) + "},\"element\":\"Vertical\",\"point\":2},{\"cell\":{\"x\":" + p(5, x) + ",\"y\":" + p(24, y) + "},\"element\":\"Vertical\",\"point\":2},{\"cell\":{\"x\":" + p(5, x) + ",\"y\":" + p(25, y) + "},\"element\":\"Vertical\",\"point\":2},{\"cell\":{\"x\":" + p(5, x) + ",\"y\":" + p(26, y) + "},\"element\":\"Vertical\",\"point\":2},{\"cell\":{\"x\":" + p(5, x) + ",\"y\":" + p(27, y) + "},\"element\":\"Vertical\",\"point\":2},{\"cell\":{\"x\":" + p(5, x) + ",\"y\":" + p(28, y) + "},\"element\":\"Vertical\",\"point\":2}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"cell\":{\"x\":" + p(46, x) + ",\"y\":" + p(1, y) + "},\"element\":\"Horizontal\",\"point\":4},{\"cell\":{\"x\":" + p(45, x) + ",\"y\":" + p(1, y) + "},\"element\":\"Horizontal\",\"point\":4},{\"cell\":{\"x\":" + p(44, x) + ",\"y\":" + p(1, y) + "},\"element\":\"Horizontal\",\"point\":4},{\"cell\":{\"x\":" + p(43, x) + ",\"y\":" + p(1, y) + "},\"element\":\"Horizontal\",\"point\":4},{\"cell\":{\"x\":" + p(42, x) + ",\"y\":" + p(1, y) + "},\"element\":\"Horizontal\",\"point\":4},{\"cell\":{\"x\":" + p(41, x) + ",\"y\":" + p(1, y) + "},\"element\":\"Horizontal\",\"point\":4},{\"cell\":{\"x\":" + p(40, x) + ",\"y\":" + p(1, y) + "},\"element\":\"Horizontal\",\"point\":4},{\"cell\":{\"x\":" + p(39, x) + ",\"y\":" + p(1, y) + "},\"element\":\"Horizontal\",\"point\":4},{\"cell\":{\"x\":" + p(38, x) + ",\"y\":" + p(1, y) + "},\"element\":\"Horizontal\",\"point\":4},{\"cell\":{\"x\":" + p(37, x) + ",\"y\":" + p(1, y) + "},\"element\":\"Horizontal\",\"point\":4},{\"cell\":{\"x\":" + p(36, x) + ",\"y\":" + p(1, y) + "},\"element\":\"Horizontal\",\"point\":4},{\"cell\":{\"x\":" + p(35, x) + ",\"y\":" + p(1, y) + "},\"element\":\"Horizontal\",\"point\":4},{\"cell\":{\"x\":" + p(34, x) + ",\"y\":" + p(1, y) + "},\"element\":\"Horizontal\",\"point\":4},{\"cell\":{\"x\":" + p(33, x) + ",\"y\":" + p(1, y) + "},\"element\":\"Horizontal\",\"point\":4},{\"cell\":{\"x\":" + p(32, x) + ",\"y\":" + p(1, y) + "},\"element\":\"Horizontal\",\"point\":4},{\"cell\":{\"x\":" + p(31, x) + ",\"y\":" + p(1, y) + "},\"element\":\"Horizontal\",\"point\":4},{\"cell\":{\"x\":" + p(30, x) + ",\"y\":" + p(1, y) + "},\"element\":\"Horizontal\",\"point\":4},{\"cell\":{\"x\":" + p(29, x) + ",\"y\":" + p(1, y) + "},\"element\":\"Horizontal\",\"point\":4},{\"cell\":{\"x\":" + p(28, x) + ",\"y\":" + p(1, y) + "},\"element\":\"Horizontal\",\"point\":4},{\"cell\":{\"x\":" + p(27, x) + ",\"y\":" + p(1, y) + "},\"element\":\"Horizontal\",\"point\":4},{\"cell\":{\"x\":" + p(26, x) + ",\"y\":" + p(1, y) + "},\"element\":\"Horizontal\",\"point\":4},{\"cell\":{\"x\":" + p(25, x) + ",\"y\":" + p(1, y) + "},\"element\":\"Horizontal\",\"point\":4},{\"cell\":{\"x\":" + p(24, x) + ",\"y\":" + p(1, y) + "},\"element\":\"Horizontal\",\"point\":4},{\"cell\":{\"x\":" + p(23, x) + ",\"y\":" + p(1, y) + "},\"element\":\"Horizontal\",\"point\":4},{\"cell\":{\"x\":" + p(22, x) + ",\"y\":" + p(1, y) + "},\"element\":\"Horizontal\",\"point\":4},{\"cell\":{\"x\":" + p(21, x) + ",\"y\":" + p(1, y) + "},\"element\":\"Horizontal\",\"point\":4},{\"cell\":{\"x\":" + p(20, x) + ",\"y\":" + p(1, y) + "},\"element\":\"Horizontal\",\"point\":4},{\"cell\":{\"x\":" + p(19, x) + ",\"y\":" + p(1, y) + "},\"element\":\"Horizontal\",\"point\":4},{\"cell\":{\"x\":" + p(18, x) + ",\"y\":" + p(1, y) + "},\"element\":\"Horizontal\",\"point\":4},{\"cell\":{\"x\":" + p(17, x) + ",\"y\":" + p(1, y) + "},\"element\":\"Horizontal\",\"point\":4},{\"cell\":{\"x\":" + p(16, x) + ",\"y\":" + p(1, y) + "},\"element\":\"Horizontal\",\"point\":4},{\"cell\":{\"x\":" + p(15, x) + ",\"y\":" + p(1, y) + "},\"element\":\"Horizontal\",\"point\":4},{\"cell\":{\"x\":" + p(14, x) + ",\"y\":" + p(1, y) + "},\"element\":\"Horizontal\",\"point\":4},{\"cell\":{\"x\":" + p(13, x) + ",\"y\":" + p(1, y) + "},\"element\":\"Horizontal\",\"point\":4},{\"cell\":{\"x\":" + p(12, x) + ",\"y\":" + p(1, y) + "},\"element\":\"Horizontal\",\"point\":4},{\"cell\":{\"x\":" + p(11, x) + ",\"y\":" + p(1, y) + "},\"element\":\"Horizontal\",\"point\":4},{\"cell\":{\"x\":" + p(10, x) + ",\"y\":" + p(1, y) + "},\"element\":\"Horizontal\",\"point\":4},{\"cell\":{\"x\":" + p(9, x) + ",\"y\":" + p(1, y) + "},\"element\":\"Horizontal\",\"point\":4},{\"cell\":{\"x\":" + p(8, x) + ",\"y\":" + p(1, y) + "},\"element\":\"Horizontal\",\"point\":4},{\"cell\":{\"x\":" + p(7, x) + ",\"y\":" + p(1, y) + "},\"element\":\"SmallCilcleSect2\",\"point\":4}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"cell\":{\"x\":" + p(48, x) + ",\"y\":" + p(3, y) + "},\"element\":\"SmallCilcleSect3\",\"point\":6}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"cell\":{\"x\":" + p(46, x) + ",\"y\":" + p(1, y) + "},\"element\":\"Horizontal\",\"point\":0},{\"cell\":{\"x\":" + p(47, x) + ",\"y\":" + p(1, y) + "},\"element\":\"Horizontal\",\"point\":0}] --switch=[{\"cell\":{\"x\":" + p(46, x) + ",\"y\":" + p(1, y) + "},\"point\":0}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"cell\":{\"x\":" + p(7, x) + ",\"y\":" + p(1, y) + "},\"element\":\"Horizontal\",\"point\":4},{\"cell\":{\"x\":" + p(6, x) + ",\"y\":" + p(1, y) + "},\"element\":\"Horizontal\",\"point\":4}] --switch=[{\"cell\":{\"x\":" + p(7, x) + ",\"y\":" + p(1, y) + "},\"point\":4}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"cell\":{\"x\":" + p(5, x) + ",\"y\":" + p(7, y) + "},\"element\":\"BaseCircleSect3\",\"point\":2},{\"cell\":{\"x\":" + p(6, x) + ",\"y\":" + p(10, y) + "},\"element\":\"Item45\",\"point\":1},{\"cell\":{\"x\":" + p(7, x) + ",\"y\":" + p(11, y) + "},\"element\":\"BaseCircleSect2\",\"point\":1},{\"cell\":{\"x\":" + p(10, x) + ",\"y\":" + p(12, y) + "},\"element\":\"Horizontal\",\"point\":0}] --switch=[{\"cell\":{\"x\":" + p(5, x) + ",\"y\":" + p(7, y) + "},\"point\":2,\"position\":\"Diverging\"}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"cell\":{\"x\":" + p(12, x) + ",\"y\":" + p(12, y) + "},\"element\":\"Horizontal\",\"point\":4}] --switch=[{\"cell\":{\"x\":" + p(12, x) + ",\"y\":" + p(12, y) + "},\"point\":4,\"position\":\"Diverging\"}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"cell\":{\"x\":" + p(7, x) + ",\"y\":" + p(22, y) + "},\"element\":\"SmallCilcleSect2\",\"point\":4}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"cell\":{\"x\":" + p(11, x) + ",\"y\":" + p(23, y) + "},\"element\":\"BaseCircleSect6\",\"point\":5},{\"cell\":{\"x\":" + p(8, x) + ",\"y\":" + p(22, y) + "},\"element\":\"Horizontal\",\"point\":4}] --switch=[{\"cell\":{\"x\":" + p(11, x) + ",\"y\":" + p(23, y) + "},\"point\":5,\"position\":\"Diverging\"},{\"cell\":{\"x\":" + p(5, x) + ",\"y\":" + p(24, y) + "},\"point\":6,\"position\":\"Diverging\"}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"cell\":{\"x\":" + p(42, x) + ",\"y\":" + p(25, y) + "},\"element\":\"SmallCilcleSect1\",\"point\":2},{\"cell\":{\"x\":" + p(44, x) + ",\"y\":" + p(27, y) + "},\"element\":\"Horizontal\",\"point\":0},{\"cell\":{\"x\":" + p(45, x) + ",\"y\":" + p(27, y) + "},\"element\":\"Horizontal\",\"point\":0},{\"cell\":{\"x\":" + p(46, x) + ",\"y\":" + p(27, y) + "},\"element\":\"SmallCilcleSect0\",\"point\":0}] --switch=[{\"cell\":{\"x\":" + p(48, x) + ",\"y\":" + p(25, y) + "},\"point\":2}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"cell\":{\"x\":" + p(32, x) + ",\"y\":" + p(24, y) + "},\"element\":\"BaseCircleSect5\",\"point\":7},{\"cell\":{\"x\":" + p(35, x) + ",\"y\":" + p(23, y) + "},\"element\":\"Horizontal\",\"point\":0},{\"cell\":{\"x\":" + p(36, x) + ",\"y\":" + p(23, y) + "},\"element\":\"Horizontal\",\"point\":0},{\"cell\":{\"x\":" + p(37, x) + ",\"y\":" + p(23, y) + "},\"element\":\"Horizontal\",\"point\":0},{\"cell\":{\"x\":" + p(38, x) + ",\"y\":" + p(23, y) + "},\"element\":\"Horizontal\",\"point\":0},{\"cell\":{\"x\":" + p(39, x) + ",\"y\":" + p(23, y) + "},\"element\":\"Horizontal\",\"point\":0},{\"cell\":{\"x\":" + p(40, x) + ",\"y\":" + p(23, y) + "},\"element\":\"SmallCilcleSect3\",\"point\":0}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"cell\":{\"x\":" + p(6, x) + ",\"y\":" + p(16, y) + "},\"element\":\"Item135\",\"point\":7},{\"cell\":{\"x\":" + p(7, x) + ",\"y\":" + p(15, y) + "},\"element\":\"Item135\",\"point\":7}] --switch=[{\"cell\":{\"x\":" + p(8, x) + ",\"y\":" + p(14, y) + "},\"point\":3}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"cell\":{\"x\":" + p(5, x) + ",\"y\":" + p(19, y) + "},\"element\":\"BaseCircleSect4\",\"point\":6}] --switch=[{\"cell\":{\"x\":" + p(5, x) + ",\"y\":" + p(19, y) + "},\"point\":6}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"cell\":{\"x\":" + p(48, x) + ",\"y\":" + p(24, y) + "},\"element\":\"Crossover20\",\"point\":6},{\"cell\":{\"x\":" + p(47, x) + ",\"y\":" + p(21, y) + "},\"element\":\"Vertical\",\"point\":6},{\"cell\":{\"x\":" + p(47, x) + ",\"y\":" + p(20, y) + "},\"element\":\"Vertical\",\"point\":6},{\"cell\":{\"x\":" + p(47, x) + ",\"y\":" + p(19, y) + "},\"element\":\"Vertical\",\"point\":6},{\"cell\":{\"x\":" + p(47, x) + ",\"y\":" + p(18, y) + "},\"element\":\"Vertical\",\"point\":6},{\"cell\":{\"x\":" + p(47, x) + ",\"y\":" + p(17, y) + "},\"element\":\"Vertical\",\"point\":6},{\"cell\":{\"x\":" + p(47, x) + ",\"y\":" + p(16, y) + "},\"element\":\"Vertical\",\"point\":6},{\"cell\":{\"x\":" + p(47, x) + ",\"y\":" + p(15, y) + "},\"element\":\"Vertical\",\"point\":6},{\"cell\":{\"x\":" + p(47, x) + ",\"y\":" + p(14, y) + "},\"element\":\"Vertical\",\"point\":6},{\"cell\":{\"x\":" + p(47, x) + ",\"y\":" + p(13, y) + "},\"element\":\"Vertical\",\"point\":6},{\"cell\":{\"x\":" + p(47, x) + ",\"y\":" + p(12, y) + "},\"element\":\"Vertical\",\"point\":6},{\"cell\":{\"x\":" + p(47, x) + ",\"y\":" + p(11, y) + "},\"element\":\"Crossover21\",\"point\":6}] --switch=[{\"cell\":{\"x\":" + p(48, x) + ",\"y\":" + p(24, y) + "},\"point\":6},{\"cell\":{\"x\":" + p(48, x) + ",\"y\":" + p(8, y) + "},\"point\":2}]";// 
	Cmd::Exec(command);
	command = "path --add --path=[{\"cell\":{\"x\":" + p(48, x) + ",\"y\":" + p(29, y) + "},\"element\":\"Crossover21\",\"point\":6},{\"cell\":{\"x\":" + p(49, x) + ",\"y\":" + p(26, y) + "},\"element\":\"Vertical\",\"point\":6},{\"cell\":{\"x\":" + p(49, x) + ",\"y\":" + p(25, y) + "},\"element\":\"Vertical\",\"point\":6},{\"cell\":{\"x\":" + p(49, x) + ",\"y\":" + p(24, y) + "},\"element\":\"Vertical\",\"point\":6},{\"cell\":{\"x\":" + p(49, x) + ",\"y\":" + p(23, y) + "},\"element\":\"Vertical\",\"point\":6},{\"cell\":{\"x\":" + p(49, x) + ",\"y\":" + p(22, y) + "},\"element\":\"Vertical\",\"point\":6},{\"cell\":{\"x\":" + p(49, x) + ",\"y\":" + p(21, y) + "},\"element\":\"Vertical\",\"point\":6},{\"cell\":{\"x\":" + p(49, x) + ",\"y\":" + p(20, y) + "},\"element\":\"Vertical\",\"point\":6},{\"cell\":{\"x\":" + p(49, x) + ",\"y\":" + p(19, y) + "},\"element\":\"Vertical\",\"point\":6},{\"cell\":{\"x\":" + p(49, x) + ",\"y\":" + p(18, y) + "},\"element\":\"Vertical\",\"point\":6},{\"cell\":{\"x\":" + p(49, x) + ",\"y\":" + p(17, y) + "},\"element\":\"Vertical\",\"point\":6},{\"cell\":{\"x\":" + p(49, x) + ",\"y\":" + p(16, y) + "},\"element\":\"Vertical\",\"point\":6},{\"cell\":{\"x\":" + p(49, x) + ",\"y\":" + p(15, y) + "},\"element\":\"Vertical\",\"point\":6},{\"cell\":{\"x\":" + p(49, x) + ",\"y\":" + p(14, y) + "},\"element\":\"Crossover20\",\"point\":6}] --switch=[{\"cell\":{\"x\":" + p(48, x) + ",\"y\":" + p(29, y) + "},\"point\":6},{\"cell\":{\"x\":" + p(48, x) + ",\"y\":" + p(11, y) + "},\"point\":2}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"cell\":{\"x\":" + p(38, x) + ",\"y\":" + p(14, y) + "},\"element\":\"Crossover00\",\"point\":4},{\"cell\":{\"x\":" + p(35, x) + ",\"y\":" + p(15, y) + "},\"element\":\"Horizontal\",\"point\":4},{\"cell\":{\"x\":" + p(34, x) + ",\"y\":" + p(15, y) + "},\"element\":\"Horizontal\",\"point\":4},{\"cell\":{\"x\":" + p(33, x) + ",\"y\":" + p(15, y) + "},\"element\":\"Horizontal\",\"point\":4},{\"cell\":{\"x\":" + p(32, x) + ",\"y\":" + p(15, y) + "},\"element\":\"Horizontal\",\"point\":4},{\"cell\":{\"x\":" + p(31, x) + ",\"y\":" + p(15, y) + "},\"element\":\"Horizontal\",\"point\":4},{\"cell\":{\"x\":" + p(30, x) + ",\"y\":" + p(15, y) + "},\"element\":\"Horizontal\",\"point\":4},{\"cell\":{\"x\":" + p(29, x) + ",\"y\":15},\"element\":\"Horizontal\",\"point\":4},{\"cell\":{\"x\":" + p(28, x) + ",\"y\":" + p(15, y) + "},\"element\":\"Horizontal\",\"point\":4},{\"cell\":{\"x\":" + p(27, x) + ",\"y\":" + p(15, y) + "},\"element\":\"Horizontal\",\"point\":4},{\"cell\":{\"x\":" + p(26, x) + ",\"y\":" + p(15, y) + "},\"element\":\"Horizontal\",\"point\":4},{\"cell\":{\"x\":" + p(25, x) + ",\"y\":" + p(15, y) + "},\"element\":\"Horizontal\",\"point\":4},{\"cell\":{\"x\":" + p(24, x) + ",\"y\":" + p(15, y) + "},\"element\":\"Crossover01\",\"point\":4}] --switch=[{\"cell\":{\"x\":" + p(38, x) + ",\"y\":" + p(14, y) + "},\"point\":4},{\"cell\":{\"x\":" + p(21, x) + ",\"y\":" + p(14, y) + "},\"point\":0}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"cell\":{\"x\":" + p(36, x) + ",\"y\":" + p(14, y) + "},\"element\":\"Crossover01\",\"point\":4},{\"cell\":{\"x\":" + p(33, x) + ",\"y\":" + p(13, y) + "},\"element\":\"Horizontal\",\"point\":4},{\"cell\":{\"x\":" + p(32, x) + ",\"y\":" + p(13, y) + "},\"element\":\"Horizontal\",\"point\":4},{\"cell\":{\"x\":" + p(31, x) + ",\"y\":" + p(13, y) + "},\"element\":\"Horizontal\",\"point\":4},{\"cell\":{\"x\":" + p(30, x) + ",\"y\":" + p(13, y) + "},\"element\":\"Horizontal\",\"point\":4},{\"cell\":{\"x\":" + p(29, x) + ",\"y\":" + p(13, y) + "},\"element\":\"Horizontal\",\"point\":4},{\"cell\":{\"x\":" + p(28, x) + ",\"y\":" + p(13, y) + "},\"element\":\"Horizontal\",\"point\":4},{\"cell\":{\"x\":" + p(27, x) + ",\"y\":" + p(13, y) + "},\"element\":\"Horizontal\",\"point\":4},{\"cell\":{\"x\":" + p(26, x) + ",\"y\":" + p(13, y) + "},\"element\":\"Crossover00\",\"point\":4}] --switch=[{\"cell\":{\"x\":" + p(36, x) + ",\"y\":14},\"point\":4},{\"cell\":{\"x\":" + p(23, x) + ",\"y\":" + p(14, y) + "},\"point\":0}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"cell\":{\"x\":" + p(21, x) + ",\"y\":" + p(15, y) + "},\"element\":\"Crossover10\",\"point\":1},{\"cell\":{\"x\":" + p(23, x) + ",\"y\":" + p(16, y) + "},\"element\":\"Item45\",\"point\":1},{\"cell\":{\"x\":" + p(24, x) + ",\"y\":" + p(17, y) + "},\"element\":\"Item45\",\"point\":1},{\"cell\":{\"x\":" + p(25, x) + ",\"y\":" + p(18, y) + "},\"element\":\"Item45\",\"point\":1},{\"cell\":{\"x\":" + p(26, x) + ",\"y\":" + p(19, y) + "},\"element\":\"Item45\",\"point\":1},{\"cell\":{\"x\":" + p(27, x) + ",\"y\":" + p(20, y) + "},\"element\":\"Item45\",\"point\":1},{\"cell\":{\"x\":" + p(28, x) + ",\"y\":" + p(21, y) + "},\"element\":\"Item45\",\"point\":1},{\"cell\":{\"x\":" + p(29, x) + ",\"y\":" + p(22, y) + "},\"element\":\"Item45\",\"point\":1},{\"cell\":{\"x\":" + p(30, x) + ",\"y\":" + p(23, y) + "},\"element\":\"Item45\",\"point\":1},{\"cell\":{\"x\":" + p(31, x) + ",\"y\":" + p(24, y) + "},\"element\":\"Item45\",\"point\":1},{\"cell\":{\"x\":" + p(32, x) + ",\"y\":" + p(25, y) + "},\"element\":\"Item45\",\"point\":1},{\"cell\":{\"x\":" + p(33, x) + ",\"y\":" + p(26, y) + "},\"element\":\"Item45\",\"point\":1},{\"cell\":{\"x\":" + p(34, x) + ",\"y\":" + p(27, y) + "},\"element\":\"Item45\",\"point\":1},{\"cell\":{\"x\":" + p(35, x) + ",\"y\":" + p(28, y) + "},\"element\":\"Item45\",\"point\":1},{\"cell\":{\"x\":" + p(36, x) + ",\"y\":" + p(29, y) + "},\"element\":\"Item45\",\"point\":1},{\"cell\":{\"x\":" + p(37, x) + ",\"y\":" + p(30, y) + "},\"element\":\"Item45\",\"point\":1},{\"cell\":{\"x\":" + p(38, x) + ",\"y\":" + p(31, y) + "},\"element\":\"Crossover11\",\"point\":1}] --switch=[{\"cell\":{\"x\":" + p(21, x) + ",\"y\":" + p(15, y) + "},\"point\":1},{\"cell\":{\"x\":" + p(39, x) + ",\"y\":" + p(33, y) + "},\"point\":5}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"cell\":{\"x\":" + p(36, x) + ",\"y\":" + p(20, y) + "},\"element\":\"Item135\",\"point\":7},{\"cell\":{\"x\":" + p(37, x) + ",\"y\":" + p(19, y) + "},\"element\":\"Item135\",\"point\":7},{\"cell\":{\"x\":" + p(38, x) + ",\"y\":" + p(18, y) + "},\"element\":\"Item135\",\"point\":7},{\"cell\":{\"x\":" + p(39, x) + ",\"y\":" + p(17, y) + "},\"element\":\"Item135\",\"point\":7},{\"cell\":{\"x\":" + p(40, x) + ",\"y\":" + p(16, y) + "},\"element\":\"Item135\",\"point\":7},{\"cell\":{\"x\":" + p(41, x) + ",\"y\":" + p(15, y) + "},\"element\":\"Item135\",\"point\":7},{\"cell\":{\"x\":" + p(42, x) + ",\"y\":" + p(14, y) + "},\"element\":\"Item135\",\"point\":7},{\"cell\":{\"x\":" + p(43, x) + ",\"y\":" + p(13, y) + "},\"element\":\"Item135\",\"point\":7},{\"cell\":{\"x\":" + p(44, x) + ",\"y\":" + p(12, y) + "},\"element\":\"Item135\",\"point\":7},{\"cell\":{\"x\":" + p(45, x) + ",\"y\":" + p(11, y) + "},\"element\":\"Item135\",\"point\":7},{\"cell\":{\"x\":" + p(46, x) + ",\"y\":" + p(10, y) + "},\"element\":\"Item135\",\"point\":7},{\"cell\":{\"x\":" + p(47, x) + ",\"y\":" + p(9, y) + "},\"element\":\"BaseCircleSect0\",\"point\":7}] --switch=[{\"cell\":{\"x\":" + p(48, x) + ",\"y\":" + p(6, y) + "},\"point\":2}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"cell\":{\"x\":" + p(28, x) + ",\"y\":" + p(21, y) + "},\"element\":\"BaseCircleSect2\",\"point\":1},{\"cell\":{\"x\":" + p(31, x) + ",\"y\":" + p(22, y) + "},\"element\":\"Horizontal\",\"point\":0},{\"cell\":{\"x\":" + p(32, x) + ",\"y\":" + p(22, y) + "},\"element\":\"BaseCircleSect1\",\"point\":0},{\"cell\":{\"x\":" + p(35, x) + ",\"y\":" + p(21, y) + "},\"element\":\"Item135\",\"point\":7}] --switch=[{\"cell\":{\"x\":" + p(28, x) + ",\"y\":" + p(21, y) + "},\"point\":1}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"cell\":{\"x\":" + p(46, x) + ",\"y\":" + p(10, y) + "},\"element\":\"Crossover31\",\"point\":3},{\"cell\":{\"x\":" + p(44, x) + ",\"y\":" + p(11, y) + "},\"element\":\"Item135\",\"point\":3},{\"cell\":{\"x\":" + p(43, x) + ",\"y\":" + p(12, y) + "},\"element\":\"Item135\",\"point\":3},{\"cell\":{\"x\":" + p(42, x) + ",\"y\":" + p(13, y) + "},\"element\":\"Item135\",\"point\":3},{\"cell\":{\"x\":" + p(41, x) + ",\"y\":" + p(14, y) + "},\"element\":\"Item135\",\"point\":3},{\"cell\":{\"x\":" + p(40, x) + ",\"y\":" + p(15, y) + "},\"element\":\"Item135\",\"point\":3},{\"cell\":{\"x\":" + p(39, x) + ",\"y\":" + p(16, y) + "},\"element\":\"Item135\",\"point\":3},{\"cell\":{\"x\":" + p(38, x) + ",\"y\":" + p(17, y) + "},\"element\":\"Item135\",\"point\":3},{\"cell\":{\"x\":" + p(37, x) + ",\"y\":" + p(18, y) + "},\"element\":\"Item135\",\"point\":3},{\"cell\":{\"x\":" + p(36, x) + ",\"y\":" + p(19, y) + "},\"element\":\"Crossover30\",\"point\":3}] --switch=[{\"cell\":{\"x\":" + p(46, x) + ",\"y\":" + p(10, y) + "},\"point\":3},{\"cell\":{\"x\":" + p(35, x) + ",\"y\":" + p(21, y) + "},\"point\":7}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"cell\":{\"x\":" + p(22, x) + ",\"y\":" + p(16, y) + "},\"element\":\"Crossover11\",\"point\":1},{\"cell\":{\"x\":" + p(23, x) + ",\"y\":" + p(18, y) + "},\"element\":\"Item45\",\"point\":1},{\"cell\":{\"x\":" + p(24, x) + ",\"y\":" + p(19, y) + "},\"element\":\"Item45\",\"point\":1},{\"cell\":{\"x\":" + p(25, x) + ",\"y\":" + p(20, y) + "},\"element\":\"Item45\",\"point\":1},{\"cell\":{\"x\":" + p(26, x) + ",\"y\":" + p(21, y) + "},\"element\":\"Item45\",\"point\":1},{\"cell\":{\"x\":" + p(27, x) + ",\"y\":" + p(22, y) + "},\"element\":\"Item45\",\"point\":1},{\"cell\":{\"x\":" + p(28, x) + ",\"y\":" + p(23, y) + "},\"element\":\"Item45\",\"point\":1},{\"cell\":{\"x\":" + p(29, x) + ",\"y\":" + p(24, y) + "},\"element\":\"Item45\",\"point\":1},{\"cell\":{\"x\":" + p(30, x) + ",\"y\":" + p(25, y) + "},\"element\":\"Item45\",\"point\":1},{\"cell\":{\"x\":" + p(31, x) + ",\"y\":" + p(26, y) + "},\"element\":\"Item45\",\"point\":1},{\"cell\":{\"x\":" + p(32, x) + ",\"y\":" + p(27, y) + "},\"element\":\"Item45\",\"point\":1},{\"cell\":{\"x\":" + p(33, x) + ",\"y\":" + p(28, y) + "},\"element\":\"Item45\",\"point\":1},{\"cell\":{\"x\":" + p(34, x) + ",\"y\":" + p(29, y) + "},\"element\":\"Item45\",\"point\":1},{\"cell\":{\"x\":" + p(35, x) + ",\"y\":" + p(30, y) + "},\"element\":\"Item45\",\"point\":1},{\"cell\":{\"x\":" + p(36, x) + ",\"y\":" + p(31, y) + "},\"element\":\"Crossover10\",\"point\":1}] --switch=[{\"cell\":{\"x\":" + p(22, x) + ",\"y\":" + p(16, y) + "},\"point\":1},{\"cell\":{\"x\":" + p(38, x) + ",\"y\":" + p(32, y) + "},\"point\":5}]";
	Cmd::Exec(command);
	command = "path --add --path=[{\"cell\":{\"x\":" + p(45, x) + ",\"y\":" + p(11, y) + "},\"element\":\"Crossover30\",\"point\":3},{\"cell\":{\"x\":" + p(44, x) + ",\"y\":" + p(13, y) + "},\"element\":\"Item135\",\"point\":3},{\"cell\":{\"x\":" + p(43, x) + ",\"y\":" + p(14, y) + "},\"element\":\"Item135\",\"point\":3},{\"cell\":{\"x\":" + p(42, x) + ",\"y\":" + p(15, y) + "},\"element\":\"Item135\",\"point\":3},{\"cell\":{\"x\":" + p(41, x) + ",\"y\":" + p(16, y) + "},\"element\":\"Item135\",\"point\":3},{\"cell\":{\"x\":" + p(40, x) + ",\"y\":" + p(17, y) + "},\"element\":\"Item135\",\"point\":3},{\"cell\":{\"x\":" + p(39, x) + ",\"y\":" + p(18, y) + "},\"element\":\"Item135\",\"point\":3},{\"cell\":{\"x\":" + p(38, x) + ",\"y\":" + p(19, y) + "},\"element\":\"Crossover31\",\"point\":3}] --switch=[{\"cell\":{\"x\":" + p(45, x) + ",\"y\":" + p(11, y) + "},\"point\":3},{\"cell\":{\"x\":" + p(36, x) + ",\"y\":" + p(20, y) + "},\"point\":7}]";
	Cmd::Exec(command);
	command = "semaphore --add --cell={\"x\":" + p(45, x) + ",\"y\":" + p(1, y) + "} --point=4 --program=[[0,1,2,0,1,2,0,1,2,0,1,2],[0,1,2,0,1,2,0,1,2,0,1,2],[0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0]]";
	Cmd::Exec(command);
	command = "semaphore --add --cell={\"x\":" + p(41, x) + ",\"y\":" + p(1, y) + "} --point=4 --program=[[2,1,0,2,1,0,2,1,0,2,1,0],[2,1,0,2,1,0,2,1,0,2,1,0],[0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0]]";
	Cmd::Exec(command);
	
	command = "semaphore --add --cell={\"x\":" + p(42, x) + ",\"y\":" + p(34, y) + "} --point=0"; // --position=Reverse
	Cmd::Exec(command);
	command = "semaphore --add --cell={\"x\":" + p(48, x) + ",\"y\":" + p(9, y) + "} --point=6"; // --position=Go
	Cmd::Exec(command);
	//back
	command = "semaphore --add --cell={\"x\":" + p(15, x) + ",\"y\":" + p(1, y) + "} --point=0 --program=[[1,2,0,1,2,0,1,2,0,1,2,0],[1,2,0,1,2,0,1,2,0,1,2,0],[0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0]]";
	Cmd::Exec(command);
	command = "semaphore --add --cell={\"x\":" + p(5, x) + ",\"y\":" + p(30, y) + "} --point=6";
	Cmd::Exec(command);
	command = "semaphore --add --cell={\"x\":" + p(6, x) + ",\"y\":" + p(32, y) + "} --point=5"; // --position=Reverse
	Cmd::Exec(command);
	command = "semaphore --add --cell={\"x\":" + p(23, x) + ",\"y\":" + p(17, y) + "} --point=5 param3 param4"; // --position=Reverse
	Cmd::Exec(command);
	command = "path --add --path=[{\"cell\":{\"x\":" + p(35, x) + ",\"y\":" + p(23, y) + "},\"element\":\"Crossover01\",\"point\":4}] --switch=[{\"cell\":{\"x\":" + p(35, x) + ",\"y\":" + p(23, y) + "},\"point\":4},{\"cell\":{\"x\":" + p(32, x) + ",\"y\":" + p(22, y) + "},\"point\":0}]";
	Cmd::Exec(command);
	
	command = "train --add --id=" + to_string(train++) + " --position={\"cell\":{\"x\":" + p(40, x) + ",\"y\":" + p(1, y) + "},\"point\":0,\"indent\":0,\"element\":\"Horizontal\"} --direction=Forward Locomotive Locomotive TankCar TankCar TankCar Locomotive";
	Cmd::Exec(command);
	command = "train --add --id=" + to_string(train++) + " --position={\"cell\":{\"x\":" + p(5, x) + ",\"y\":" + p(25, y) + "},\"point\":6,\"indent\":0,\"element\":\"Verical\"} --direction=Back Switcher TankCar TankCar TankCar Switcher";
	Cmd::Exec(command);
	command = "station --add --id=" + to_string(station++) + " --cell={\"x\":" + p(10, x) + ",\"y\":" + p(1, y) + "} --angle=270"; Cmd::Exec(command);	
	command = "station --add --id=" + to_string(station++) + " --cell={\"x\":" + p(30, x) + ",\"y\":" + p(5, y) + "} --angle=90"; Cmd::Exec(command);	
	command = "station --add --id=" + to_string(station++) + " --cell={\"x\":" + p(25, x) + ",\"y\":" + p(25, y) + "} --angle=180"; Cmd::Exec(command);	
	command = "station --add --id=" + to_string(station++) + " --cell={\"x\":" + p(15, x) + ",\"y\":" + p(17, y) + "} --angle=0"; Cmd::Exec(command);
	
	
	command = "path --add --path=[{\"cell\":{\"x\":" + p(21, x) + ",\"y\":" + p(33, y) + "},\"element\":\"BaseCircleSect3\",\"point\":5},{\"cell\":{\"x\":" + p(20, x) + ",\"y\":" + p(30, y) + "},\"element\":\"Vertical\",\"point\":6},{\"cell\":{\"x\":" + p(20, x) + ",\"y\":" + p(29, y) + "},\"element\":\"Vertical\",\"point\":6},{\"cell\":{\"x\":" + p(20, x) + ",\"y\":" + p(28, y) + "},\"element\":\"Vertical\",\"point\":6}] --switch=[{\"cell\":{\"x\":" + p(21, x) + ",\"y\":" + p(33, y) + "},\"point\":5}]"; Cmd::Exec(command);
	command = "path --add --path=[{\"cell\":{\"x\":" + p(20, x) + ",\"y\":" + p(30, y) + "},\"element\":\"Crossover20\",\"point\":6}] --switch=[{\"cell\":{\"x\":" + p(20, x) + ",\"y\":" + p(30, y) + "},\"point\":6}]"; Cmd::Exec(command);
	command = "path --add --path=[{\"cell\":{\"x\":" + p(7, x) + ",\"y\":" + p(17, y) + "},\"element\":\"SmallCilcleSect2\",\"point\":6},{\"cell\":{\"x\":" + p(9, x) + ",\"y\":" + p(15, y) + "},\"element\":\"Horizontal\",\"point\":0},{\"cell\":{\"x\":" + p(10, x) + ",\"y\":" + p(15, y) + "},\"element\":\"Horizontal\",\"point\":0},{\"cell\":{\"x\":" + p(11, x) + ",\"y\":" + p(15, y) + "},\"element\":\"Horizontal\",\"point\":0},{\"cell\":{\"x\":" + p(12, x) + ",\"y\":" + p(15, y) + "},\"element\":\"Horizontal\",\"point\":0},{\"cell\":{\"x\":" + p(13, x) + ",\"y\":" + p(15, y) + "},\"element\":\"Horizontal\",\"point\":0},{\"cell\":{\"x\":" + p(14, x) + ",\"y\":" + p(15, y) + "},\"element\":\"Horizontal\",\"point\":0},{\"cell\":{\"x\":" + p(15, x) + ",\"y\":" + p(15, y) + "},\"element\":\"Horizontal\",\"point\":0},{\"cell\":{\"x\":" + p(16, x) + ",\"y\":" + p(15, y) + "},\"element\":\"Horizontal\",\"point\":0},{\"cell\":{\"x\":" + p(17, x) + ",\"y\":" + p(15, y) + "},\"element\":\"SmallCilcleSect3\",\"point\":0}] --switch=[{\"cell\":{\"x\":" + p(7, x) + ",\"y\":" + p(17, y) + "},\"point\":6}]"; Cmd::Exec(command);
	command = "path --add --path=[{\"cell\":{\"x\":" + p(17, x) + ",\"y\":" + p(15, y) + "},\"element\":\"Horizontal\",\"point\":0},{\"cell\":{\"x\":" + p(18, x) + ",\"y\":" + p(15, y) + "},\"element\":\"SmallCilcleSect3\",\"point\":0}] --switch=[{\"cell\":{\"x\":" + p(17, x) + ",\"y\":" + p(15, y) + "},\"point\":0}]"; Cmd::Exec(command);
	command = "path --add --path=[{\"cell\":{\"x\":" + p(24, x) + ",\"y\":" + p(11, y) + "},\"element\":\"SmallCilcleSect1\",\"point\":4},{\"cell\":{\"x\":" + p(22, x) + ",\"y\":" + p(9, y) + "},\"element\":\"Vertical\",\"point\":6},{\"cell\":{\"x\":" + p(22, x) + ",\"y\":" + p(8, y) + "},\"element\":\"Vertical\",\"point\":6},{\"cell\":{\"x\":" + p(22, x) + ",\"y\":" + p(7, y) + "},\"element\":\"Vertical\",\"point\":6},{\"cell\":{\"x\":" + p(22, x) + ",\"y\":" + p(6, y) + "},\"element\":\"Vertical\",\"point\":6},{\"cell\":{\"x\":" + p(22, x) + ",\"y\":" + p(5, y) + "},\"element\":\"SmallCilcleSect3\",\"point\":6}]"; Cmd::Exec(command);
	command = "path --add --path=[{\"cell\":{\"x\":" + p(30, x) + ",\"y\":" + p(11, y) + "},\"element\":\"Horizontal\",\"point\":4},{\"cell\":{\"x\":" + p(29, x) + ",\"y\":" + p(11, y) + "},\"element\":\"Horizontal\",\"point\":4},{\"cell\":{\"x\":" + p(28, x) + ",\"y\":" + p(11, y) + "},\"element\":\"Horizontal\",\"point\":4},{\"cell\":{\"x\":" + p(27, x) + ",\"y\":" + p(11, y) + "},\"element\":\"Horizontal\",\"point\":4},{\"cell\":{\"x\":" + p(26, x) + ",\"y\":" + p(11, y) + "},\"element\":\"Horizontal\",\"point\":4},{\"cell\":{\"x\":" + p(25, x) + ",\"y\":" + p(11, y) + "},\"element\":\"Horizontal\",\"point\":4}]"; Cmd::Exec(command);
	command = "path --add --path=[{\"cell\":{\"x\":" + p(23, x) + ",\"y\":" + p(8, y) + "},\"element\":\"SmallCilcleSect1\",\"point\":2},{\"cell\":{\"x\":" + p(25, x) + ",\"y\":" + p(10, y) + "},\"element\":\"Horizontal\",\"point\":0},{\"cell\":{\"x\":" + p(26, x) + ",\"y\":" + p(10, y) + "},\"element\":\"Horizontal\",\"point\":0},{\"cell\":{\"x\":" + p(27, x) + ",\"y\":" + p(10, y) + "},\"element\":\"Horizontal\",\"point\":0},{\"cell\":{\"x\":" + p(28, x) + ",\"y\":" + p(10, y) + "},\"element\":\"Horizontal\",\"point\":0},{\"cell\":{\"x\":" + p(29, x) + ",\"y\":" + p(10, y) + "},\"element\":\"Horizontal\",\"point\":0}]"; Cmd::Exec(command);
	command = "path --add --path=[{\"cell\":{\"x\":" + p(23, x) + ",\"y\":" + p(7, y) + "},\"element\":\"Vertical\",\"point\":6},{\"cell\":{\"x\":" + p(23, x) + ",\"y\":" + p(6, y) + "},\"element\":\"Vertical\",\"point\":6},{\"cell\":{\"x\":" + p(23, x) + ",\"y\":" + p(5, y) + "},\"element\":\"Vertical\",\"point\":6},{\"cell\":{\"x\":" + p(23, x) + ",\"y\":" + p(4, y) + "},\"element\":\"SmallCilcleSect3\",\"point\":6},{\"cell\":{\"x\":" + p(21, x) + ",\"y\":" + p(2, y) + "},\"element\":\"Horizontal\",\"point\":4}]"; Cmd::Exec(command);
	command = "path --add --path=[{\"cell\":{\"x\":" + p(23, x) + ",\"y\":" + p(8, y) + "},\"element\":\"Vertical\",\"point\":6}]"; Cmd::Exec(command);
	command = "path --add --path=[{\"cell\":{\"x\":" + p(47, x) + ",\"y\":" + p(7, y) + "},\"element\":\"Crossover31\",\"point\":3},{\"cell\":{\"x\":" + p(45, x) + ",\"y\":" + p(8, y) + "},\"element\":\"Item135\",\"point\":3},{\"cell\":{\"x\":" + p(44, x) + ",\"y\":" + p(9, y) + "},\"element\":\"Item135\",\"point\":3},{\"cell\":{\"x\":" + p(43, x) + ",\"y\":" + p(10, y) + "},\"element\":\"BaseCircleSect1\",\"point\":3}] --switch=[{\"cell\":{\"x\":" + p(47, x) + ",\"y\":" + p(7, y) + "},\"point\":3}]"; Cmd::Exec(command);
	command = "path --add --path=[{\"cell\":{\"x\":" + p(44, x) + ",\"y\":" + p(9, y) + "},\"element\":\"BaseCircleSect1\",\"point\":3},{\"cell\":{\"x\":" + p(41, x) + ",\"y\":" + p(10, y) + "},\"element\":\"Horizontal\",\"point\":4}] --switch=[{\"cell\":{\"x\":" + p(44, x) + ",\"y\":" + p(9, y) + "},\"point\":3}]"; Cmd::Exec(command);
	command = "path --add --path=[{\"cell\":{\"x\":" + p(7, x) + ",\"y\":" + p(1, y) + "},\"element\":\"Crossover01\",\"point\":0}] --switch=[{\"cell\":{\"x\":" + p(7, x) + ",\"y\":" + p(1, y) + "},\"point\":0}]"; Cmd::Exec(command);
	command = "path --add --path=[{\"cell\":{\"x\":" + p(5, x) + ",\"y\":" + p(5, y) + "},\"element\":\"SmallCilcleSect2\",\"point\":6},{\"cell\":{\"x\":" + p(7, x) + ",\"y\":" + p(3, y) + "},\"element\":\"Horizontal\",\"point\":0},{\"cell\":{\"x\":" + p(8, x) + ",\"y\":" + p(3, y) + "},\"element\":\"Horizontal\",\"point\":0},{\"cell\":{\"x\":" + p(9, x) + ",\"y\":" + p(3, y) + "},\"element\":\"Horizontal\",\"point\":0}] --switch=[{\"cell\":{\"x\":" + p(5, x) + ",\"y\":" + p(5, y) + "},\"point\":6}]"; Cmd::Exec(command);
	command = "path --add --path=[{\"cell\":{\"x\":" + p(17, x) + ",\"y\":" + p(41, y) + "},\"element\":\"Horizontal\",\"point\":0},{\"cell\":{\"x\":" + p(18, x) + ",\"y\":" + p(41, y) + "},\"element\":\"Horizontal\",\"point\":0},{\"cell\":{\"x\":" + p(19, x) + ",\"y\":" + p(41, y) + "},\"element\":\"BaseCircleSect1\",\"point\":0},{\"cell\":{\"x\":" + p(22, x) + ",\"y\":" + p(40, y) + "},\"element\":\"Item135\",\"point\":7},{\"cell\":{\"x\":" + p(23, x) + ",\"y\":" + p(39, y) + "},\"element\":\"Item135\",\"point\":7},{\"cell\":{\"x\":" + p(24, x) + ",\"y\":" + p(38, y) + "},\"element\":\"BaseCircleSect0\",\"point\":7}] --switch=[{\"cell\":{\"x\":" + p(17, x) + ",\"y\":" + p(41, y) + "},\"point\":0}]"; Cmd::Exec(command);
	command = "path --add --path=[{\"cell\":{\"x\":" + p(34, x) + ",\"y\":" + p(29, y) + "},\"element\":\"BaseCircleSect7\",\"point\":1},{\"cell\":{\"x\":" + p(35, x) + ",\"y\":" + p(32, y) + "},\"element\":\"BaseCircleSect0\",\"point\":2},{\"cell\":{\"x\":" + p(34, x) + ",\"y\":" + p(35, y) + "},\"element\":\"Item135\",\"point\":3},{\"cell\":{\"x\":" + p(33, x) + ",\"y\":" + p(36, y) + "},\"element\":\"BaseCircleSect1\",\"point\":3},{\"cell\":{\"x\":" + p(30, x) + ",\"y\":" + p(37, y) + "},\"element\":\"Horizontal\",\"point\":4},{\"cell\":{\"x\":" + p(29, x) + ",\"y\":" + p(37, y) + "},\"element\":\"Horizontal\",\"point\":4},{\"cell\":{\"x\":" + p(28, x) + ",\"y\":" + p(37, y) + "},\"element\":\"SmallCilcleSect1\",\"point\":4}] --switch=[{\"cell\":{\"x\":" + p(34, x) + ",\"y\":" + p(29, y) + "},\"point\":1}]"; Cmd::Exec(command);
	command = "path --add --path=[{\"cell\":{\"x\":" + p(24, x) + ",\"y\":" + p(19, y) + "},\"element\":\"BaseCircleSect7\",\"point\":1},{\"cell\":{\"x\":" + p(25, x) + ",\"y\":" + p(22, y) + "},\"element\":\"Vertical\",\"point\":2},{\"cell\":{\"x\":" + p(25, x) + ",\"y\":" + p(23, y) + "},\"element\":\"Vertical\",\"point\":2},{\"cell\":{\"x\":" + p(25, x) + ",\"y\":" + p(24, y) + "},\"element\":\"Vertical\",\"point\":2}] --switch=[{\"cell\":{\"x\":" + p(24, x) + ",\"y\":" + p(19, y) + "},\"point\":1}]"; Cmd::Exec(command);
	command = "path --add --path=[{\"cell\":{\"x\":" + p(25, x) + ",\"y\":" + p(22, y) + "},\"element\":\"Crossover20\",\"point\":2}] --switch=[{\"cell\":{\"x\":" + p(25, x) + ",\"y\":" + p(22, y) + "},\"point\":2}]"; Cmd::Exec(command);

	command = "path --add --path=[{\"cell\":{\"x\":" + p(29, x) + ",\"y\":" + p(6, y) + "},\"element\":\"SmallCilcleSect3\",\"point\":6},{\"cell\":{\"x\":" + p(27, x) + ",\"y\":" + p(4, y) + "},\"element\":\"SmallCilcleSect2\",\"point\":4}]"; Cmd::Exec(command);
	command = "path --add --path=[{\"cell\":{\"x\":" + p(25, x) + ",\"y\":" + p(6, y) + "},\"element\":\"SmallCilcleSect1\",\"point\":2},{\"cell\":{\"x\":" + p(27, x) + ",\"y\":" + p(8, y) + "},\"element\":\"SmallCilcleSect0\",\"point\":0}]"; Cmd::Exec(command);
}

string MapLayer::p(int p, int d)
{
	return to_string(p + d);
}
