#include "Field.h"
#include "Cell.h"
#include "Switch.h"
#include "Cmd.h"
#include "Path.h"

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
	
	
	void Cell::Connect(TrackElement element, int Point, bool Back) //from point
	{
		
		int enter = Path::track[element].entry[Point];
		ElementOffset offset = Elements::offset[enter][element];
		Cell *cell = &Field::getInstance()->cells[x + offset.d.x][y + offset.d.y];
		SetEntry(cell, Point, offset.p, Cell::GetPointConfiguration(Point), element, enter);
		if (!Back) {
			cell->Connect(element, offset.p, true);
		}
	}

	void Cell::Disconnect(TrackElement element, int Point, bool Back) //from point
	{
		int enter = Path::track[element].entry[Point];
		ElementOffset offset = Elements::offset[enter][element];
		Cell *cell = &Field::getInstance()->cells[x + offset.d.x][y + offset.d.y];
		RemoveEntry(cell, Point, offset.p, Cell::GetPointConfiguration(Point), element, enter);

		if (!Back) {
			cell->Disconnect(element, offset.p, true);
		}
	}


	void Cell::SetEntry(Cell *cell, int FromPoint, int ToPoint, Configuration Configuration, TrackElement Element, int Enter)
	{
		Entry *entry = new Entry;		
		entry->to = cell;
		entry->Element = Element;
		entry->Point = ToPoint;
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
				/*if (accessItem.access > 0) {
					writeDebugNode(p.x, p.y, accessItem.access, accessItem.c, Color4F::BLUE);
				}*/				
			}
		}

		/*if (Enter == 1) {
			AccessItems accessItems = Path::access[1][Element];
			AccessItem accessItem;
			for (int i = 0; i < accessItems.items.size(); i++) {
				accessItem = accessItems.items[i];				
				// debug
				writeDebugNode(x + accessItem.p.x, y + accessItem.p.y, accessItem.access, accessItem.c, Color4F::RED);
			}
		}*/
		
		if (Enter == 0 && Field::getInstance()->constuctionMode != ConstructionMode::ConstructOpen) {
			Cmd *inst = Cmd::getInstance();
			Sprite *image = Elements::GetTrackElement({ cell->x, cell->y }, Element);
			Field::getInstance()->mapLayer->addChild(image, ZIndexRails);
			inst->history[inst->pointer - 1].elements.push_back(image);			
		}
		configuration = Configuration;
		if (straightConnection[FromPoint] == NULL) { // ToPoint
			straightConnection[FromPoint] = entry;
		} else {
			divergingConnection[FromPoint] = entry;
		}
	}

	void Cell::RemoveEntry(Cell *cell, int FromPoint, int ToPoint, Configuration Configuration, TrackElement Element, int Enter)
	{
		Entry *straightEntry = straightConnection[FromPoint]; //ToPoint
		Entry *divergingEntry = divergingConnection[FromPoint];

		Field *game = Field::getInstance();
		MapPoint p;

		if (Enter == 0) {
			Cmd *cmd = Cmd::getInstance();
			game->mapLayer->removeChild(cmd->history[cmd->pointer].elements.back());
			cmd->history[cmd->pointer].elements.pop_back();
		}

		AccessItem accessItem;
		AccessItems accessItems = Path::access[0][Element];

		if (divergingConnection[FromPoint] != NULL) {
			if (divergingConnection[FromPoint]->Element == Element) {

				//remove access data
				for (int i = 0; i < divergingConnection[FromPoint]->accessConfig.size(); i++) {
					accessItem = divergingConnection[FromPoint]->accessConfig[i];
					p = accessItem.p;		
					game->cells[p.x][p.y].access = game->cells[p.x][p.y].access ^ accessItem.access;
					game->cells[p.x][p.y].accessParam = game->cells[p.x][p.y].accessParam ^ accessItem.c;
				}
				
				delete(divergingConnection[FromPoint]);
				divergingConnection[FromPoint] = 0;
			}			
		} else {
			if (straightConnection[FromPoint]->Element == Element) {
				
				for (int i = 0; i < straightConnection[FromPoint]->accessConfig.size(); i++) {
					accessItem = straightConnection[FromPoint]->accessConfig[i];
					p = accessItem.p;
					game->cells[p.x][p.y].access = game->cells[p.x][p.y].access ^ accessItem.access;
					game->cells[p.x][p.y].accessParam = game->cells[p.x][p.y].accessParam ^ accessItem.c;
				}

				delete(straightConnection[FromPoint]);
				straightConnection[FromPoint] = 0;

				if (straightConnection[Cell::Related[FromPoint]] == 0) {
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
	
	Configuration Cell::GetPointConfiguration(int point)
	{
		return point == 0 || point == 2 || point == 4 || point == 6 ? Configuration::Ortogonal : Configuration::Polar;
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
