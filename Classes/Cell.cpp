#include "Field.h"
#include "Cell.h"
#include "Switch.h"
#include "Cmd.h"
#include "Path.h"

//#include <bitset>

namespace GameObjects {

	Cell::Cell()
	{
		for (int i = 0; i < 8; i++){
			straightConnection[i] = 0;
			divergingConnection[i] = 0;
			connection[i] = 0;
			switches[i] = 0;
			semaphores[i] = 0;
		}
		access = 0;
		accessParam = 0;
	}

	Cell::~Cell()
	{
	}

	int Cell::Related[8] = { 4, 5, 6, 7, 0, 1, 2, 3};
	
	ConnectionConfig *Cell::GetConnectConfig(int dx, int dy, int Point){ 
		ConnectionConfig *connect = new ConnectionConfig;

		//horizontal		
		if (dx == 1 && dy == 0){
			*connect = {Ortogonal, Horizontal, Cell::Related[Point], 1};
		}
		if (dx == -1 && dy == 0){
			*connect = {Ortogonal, Horizontal, Cell::Related[Point], 0};
		}
		
		//Vertical
		if (dx == 0 && dy == -1){
			*connect = { Ortogonal, Vertical, Cell::Related[Point], 1 };
		}	
		if (dx == 0 && dy == 1){
			*connect = { Ortogonal, Vertical, Cell::Related[Point], 0 };
		}

		//Item45
		if (dx == 1 && dy == 1){
			*connect = { Polar, Item45, Cell::Related[Point], 1 };
		}	
		if (dx == -1 && dy == -1){;
		*connect = { Polar, Item45, Cell::Related[Point], 0 };
		}
	
		//Item135
		if (dx == 1 && dy == -1){
			*connect = { Polar, Item135, Cell::Related[Point], 1 };
		}	
		if (dx == -1 && dy == 1){
			*connect = { Polar, Item135, Cell::Related[Point], 0 };
		}

		//BaseCircleSect0	
		if (dy == 3 && dx == -1 && Point == 2){
			*connect = { Polar, BaseCircleSect0, 7, 1 };
		}	
		if (dy == -3 && dx == 1 && Point == 7){
			*connect = { Ortogonal, BaseCircleSect0, 2, 0 };
		}
	
		//BaseCircleSect1	
		if (dy == 1 && dx == -3 && Point == 3){
			*connect = { Ortogonal, BaseCircleSect1, 0, 1 };
		}	
		if (dy == -1 && dx == 3 && Point == 0){
			*connect = { Polar, BaseCircleSect1, 3, 0 };
		}
	
		//BaseCircleSect2	
		if (dy == -1 && dx == -3 && Point == 4){
			*connect = { Polar, BaseCircleSect2, 1, 1 };
		}	
		if (dy == 1 && dx == 3 && Point == 1){
			*connect = { Ortogonal, BaseCircleSect2, 4, 0 };
		}
	
		//BaseCircleSect3	
		if (dy == -3 && dx == -1 && Point == 5){
			*connect = { Ortogonal, BaseCircleSect3, 2, 1 };
		}	
		if (dy == 3 && dx == 1 && Point == 2){
			*connect = { Polar, BaseCircleSect3, 5, 0 };
		}
	
		//BaseCircleSect4
		if (dy == -3 && dx == 1 && Point == 6){
			*connect = { Polar, BaseCircleSect4, 3, 1 };
		}	
		if (dy == 3 && dx == -1 && Point == 3){
			*connect = { Ortogonal, BaseCircleSect4, 6, 0 };
		}
	
		//BaseCircleSect5
		if (dy == -1 && dx == 3 && Point == 7){
			*connect = { Ortogonal, BaseCircleSect5, 4, 1 };
		}	
		if (dy == 1 && dx == -3 && Point == 4){
			*connect = { Polar, BaseCircleSect5, 7, 0 };
		}
	
		//BaseCircleSect6
		if (dy == 1 && dx == 3 && Point == 0){
			*connect = { Polar, BaseCircleSect6, 5, 1 };
		}	
		if (dy == -1 && dx == -3 && Point == 5){
			*connect = { Ortogonal, BaseCircleSect6, 0, 0 };
		}
	
		//BaseCircleSect7
		if (dy == 3 && dx == 1 && Point == 1){
			*connect = { Ortogonal, BaseCircleSect7, 6, 1 };
		}	
		if (dy == -3 && dx == -1 && Point == 6){
			*connect = { Polar, BaseCircleSect7, 1, 0 };
		}
	
		//SmallCilcleSect0
		if (dy == 2 && dx == -2 && Point == 2){
			*connect = { Ortogonal, SmallCilcleSect0, 0, 1 };
		}	
		if (dy == -2 && dx == 2 && Point == 0){
			*connect = { Ortogonal, SmallCilcleSect0, 2, 0 };
		}
	
		//SmallCilcleSect1
		if (dy == -2 && dx == -2 && Point == 4){
			*connect = { Ortogonal, SmallCilcleSect1, 2, 1 };
		}	
		if (dy == 2 && dx == 2 && Point == 2){
			*connect = { Ortogonal, SmallCilcleSect1, 4, 0 };
		}
	
		//SmallCilcleSect2
		if (dy == -2 && dx == 2 && Point == 6){
			*connect = { Ortogonal, SmallCilcleSect2, 4, 1 };
		}	
		if (dy == 2 && dx == -2 && Point == 4){
			*connect = { Ortogonal, SmallCilcleSect2, 6, 0 };
		}
	
		//SmallCilcleSect3
		if (dy == 2 && dx == 2 && Point == 0){
			*connect = { Ortogonal, SmallCilcleSect3, 6, 1 };
		}	
		if (dy == -2 && dx == -2 && Point == 6){
			*connect = { Ortogonal, SmallCilcleSect3, 0, 0 };
		}
		
		return connect;
	}

	void Cell::Connect(Cell *cell, int Point, bool Back) //to point
	{
		int dx = x - cell->x;
		int dy = y - cell->y;
		ConnectionConfig *connect = Cell::GetConnectConfig(dx, dy, Point);
		SetEntry(cell, Point, connect->point, connect->config, connect->element, connect->enter);
		if (!Back){
			cell->Connect(this, connect->point, true);
		}
	}

	void Cell::Disconnect(Cell *cell, int Point, bool Back) //to point
	{
		int dx = x - cell->x;
		int dy = y - cell->y;
		ConnectionConfig *connect = Cell::GetConnectConfig(dx, dy, Point);
		RemoveEntry(cell, Point, connect->point, connect->config, connect->element, connect->enter);
		if (!Back) {
			cell->Disconnect(this, connect->point, true);
		}
	}

	void Cell::SetEntry(Cell *cell, int FromPoint, int ToPoint, Configuration Configuration, TrackElement Element, int Enter)
	{
		Entry *entry = new Entry;
		
		entry->to = cell;
		entry->Element = Element;
		entry->Point = FromPoint;
		entry->Enter = Enter;

		if (Enter == 0) {
			Field *game = Field::getInstance();
			//set access
			AccessItems accessItems = Path::access[0][Element];
			AccessItem accessItem;

			MapPoint p;

			for (int i = 0; i < accessItems.items.size(); i++) {
				accessItem = accessItems.items[i];
				p = { x + accessItem.p.x , y + accessItem.p.y };
				//game->cells[p.x][p.y].access = game->cells[p.x][p.y].access | accessItem.access;
				//game->cells[p.x][p.y].accessParam = game->cells[p.x][p.y].accessParam | accessItem.c;
				accessItem = {(byte)((game->cells[p.x][p.y].access ^ accessItem.access) & accessItem.access), (byte)((game->cells[p.x][p.y].accessParam ^ accessItem.c) & accessItem.c), p};
				if (accessItem.access > 0 || accessItem.c) {
					entry->accessConfig.push_back(accessItem);
					game->cells[p.x][p.y].access = game->cells[p.x][p.y].access | accessItem.access;
					game->cells[p.x][p.y].accessParam = game->cells[p.x][p.y].accessParam | accessItem.c;
				}
				
				// debug
				//if (accessItem.access > 0) {
				//	writeDebugNode(p.x, p.y, accessItem.access, accessItem.c, Color4F::BLUE);
				//}				
			}
		}

		/*if (Enter == 1) {
			AccessItems accessItems = Path::access[1][Element];
			AccessItem accessItem;
			for (int i = 0; i < accessItems.items.size(); i++) {
				accessItem = accessItems.items[i];				
				// debug
				//writeDebugNode(x + accessItem.p.x, y + accessItem.p.y, accessItem.access, accessItem.c, Color4F::RED);
			}
		}*/
		
		if (Enter == 0 && Field::getInstance()->constuctionMode != ConstructionMode::ConstructOpen) {
			Cmd *inst = Cmd::getInstance();
			Sprite *image = Elements::GetTrackElement({ cell->x, cell->y }, Element);
			Field::getInstance()->mapLayer->addChild(image, ZIndexRails);
			inst->history[inst->pointer - 1].elements.push_back(image);			
		}
		configuration = Configuration;
		if (straightConnection[ToPoint] == NULL) {
			straightConnection[ToPoint] = entry;
		} else {
			divergingConnection[ToPoint] = entry;
		}
	}

	void Cell::RemoveEntry(Cell *cell, int FromPoint, int ToPoint, Configuration Configuration, TrackElement Element, int Enter)
	{
		Entry *straightEntry = straightConnection[ToPoint];
		Entry *divergingEntry = divergingConnection[ToPoint];

		Field *game = Field::getInstance();
		MapPoint p;

		if (Enter == 0) {
			Cmd *cmd = Cmd::getInstance();
			game->mapLayer->removeChild(cmd->history[cmd->pointer].elements.back());
			cmd->history[cmd->pointer].elements.pop_back();
		}

		AccessItem accessItem;
		AccessItems accessItems = Path::access[0][Element];

		if (divergingConnection[ToPoint] != NULL) {
			if (divergingConnection[ToPoint]->Element == Element) {

				//remove access data
				for (int i = 0; i < divergingConnection[ToPoint]->accessConfig.size(); i++) {
					accessItem = divergingConnection[ToPoint]->accessConfig[i];
					p = accessItem.p;		
					game->cells[p.x][p.y].access = game->cells[p.x][p.y].access ^ accessItem.access;
					game->cells[p.x][p.y].accessParam = game->cells[p.x][p.y].accessParam ^ accessItem.c;
				}
				
				delete(divergingConnection[ToPoint]);
				divergingConnection[ToPoint] = 0;
			}			
		} else {
			if (straightConnection[ToPoint]->Element == Element) {
				
				for (int i = 0; i < straightConnection[ToPoint]->accessConfig.size(); i++) {
					accessItem = straightConnection[ToPoint]->accessConfig[i];
					p = accessItem.p;
					game->cells[p.x][p.y].access = game->cells[p.x][p.y].access ^ accessItem.access;
					game->cells[p.x][p.y].accessParam = game->cells[p.x][p.y].accessParam ^ accessItem.c;
				}

				delete(straightConnection[ToPoint]);
				straightConnection[ToPoint] = 0;

				if (straightConnection[Cell::Related[ToPoint]] == 0) {
					configuration = Configuration::Undefined;
				}
			}
		}
	}

	Entry *Cell::getEntry(int Point) {		
		return this->switches[Point] == 0 || (this->switches[Point] > 0 && this->switches[Point]->Position == SwitchPosition::Straight) ? this->straightConnection[Point] : this->divergingConnection[Point];
	}

	Entry *Cell::getEntry(int Point, TrackElement element) {
		return this->switches[Point] == 0 || (this->switches[Point] > 0 && this->straightConnection[Point]->Element == element) ? this->straightConnection[Point] : this->divergingConnection[Point];
	}

	void Cell::SetSwitch(int Point)
	{
		this->switches[Point] = new Switch(this, Point);
	}

	void Cell::RemoveSwitch(int Point)
	{
		this->switches[Point]->remove();
		delete(this->switches[Point]);
		this->switches[Point] = 0;
	}

	void Cell::SetSemaphore(int Point)
	{
		this->semaphores[Point] = new Semaphore(this, Point);
	}

	void Cell::RemoveSemaphore(int Point)
	{
		this->semaphores[Point]->remove();
		delete(this->semaphores[Point]);
		this->semaphores[Point] = 0;
	}
	
	/*void Cell::writeDebugNode(int x, int y, int a, int c, Color4F color) {
		Field *game = Field::getInstance();

		float _dx, _dy, _dx1, _dx2, _dy1, _dy2;
		_dx = (float)(x * 20);
		_dy = (float)(y * 20);
		
		if ((a & 0b00000001) == 1) {
			debugNode = DrawNode::create();
			game->mapLayer->addChild(debugNode, ZIndexRails);
			debugNode->drawDot({ _dx, _dy }, 3, color);
		}

		if ((a & 0b00000010) == 2) {
			debugNode = DrawNode::create();
			game->mapLayer->addChild(debugNode, ZIndexRails);
			debugNode->drawDot({ _dx + 7, _dy }, 3, color);
		}

		if ((a & 0b00000100) == 4) {
			debugNode = DrawNode::create();
			game->mapLayer->addChild(debugNode, ZIndexRails);
			debugNode->drawDot({ _dx + 14, _dy }, 3, color);
		}

		if ((a & 0b00001000) == 8) {
			debugNode = DrawNode::create();
			game->mapLayer->addChild(debugNode, ZIndexRails);
			debugNode->drawDot({ _dx + 14, _dy + 7 }, 3, color);
		}

		if ((a & 0b00010000) == 16) {
			debugNode = DrawNode::create();
			game->mapLayer->addChild(debugNode, ZIndexRails);
			debugNode->drawDot({ _dx + 14, _dy + 14 }, 3, color);
		}

		if ((a & 0b00100000) == 32) {
			debugNode = DrawNode::create();
			game->mapLayer->addChild(debugNode, ZIndexRails);
			debugNode->drawDot({ _dx + 7, _dy + 14 }, 3, color);
		}

		if ((a & 0b01000000) == 64) {
			debugNode = DrawNode::create();
			game->mapLayer->addChild(debugNode, ZIndexRails);
			debugNode->drawDot({ _dx, _dy + 14 }, 3, color);
		}

		if ((a & 0b10000000) == 128) {
			debugNode = DrawNode::create();
			game->mapLayer->addChild(debugNode, ZIndexRails);
			debugNode->drawDot({ _dx, _dy + 7 }, 3, color);
		}

		if ((c & 0b1) == 1) {
			debugNode = DrawNode::create();
			game->mapLayer->addChild(debugNode, ZIndexRails);
			debugNode->drawDot({ _dx + 7, _dy + 7 }, 3, color);
		}		
	}*/
}
