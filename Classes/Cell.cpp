#include "Field.h"
#include "Cell.h"
#include "Switch.h"
#include "Cmd.h"

namespace GameObjects {

	Cell::Cell()
	{
		for (int i = 0; i < 8; i++){
			straightConnection[i] = 0;
			divergingConnection[i] = 0;
			switches[i] = 0;
			semaphores[i] = 0;

			/*allowSwitch[i] = true;
			allowEnter[i][Vertical] = true;
			allowEnter[i][Horizontal] = true;
			allowEnter[i][Item45] = true;
			allowEnter[i][Item135] = true;
			allowEnter[i][BaseCircleSect0] = true;
			allowEnter[i][BaseCircleSect1] = true;
			allowEnter[i][BaseCircleSect2] = true;
			allowEnter[i][BaseCircleSect3] = true;
			allowEnter[i][BaseCircleSect4] = true;
			allowEnter[i][BaseCircleSect5] = true;
			allowEnter[i][BaseCircleSect6] = true;
			allowEnter[i][BaseCircleSect7] = true;
			allowEnter[i][SmallCilcleSect0] = true;
			allowEnter[i][SmallCilcleSect1] = true;
			allowEnter[i][SmallCilcleSect2] = true;
			allowEnter[i][SmallCilcleSect3] = true;*/
		}
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

		if (Enter == 0) {
			Cmd *inst = Cmd::getInstance();
			Field::getInstance()->mapLayer->removeChild(inst->history[inst->pointer].elements.back());			
			inst->history[inst->pointer].elements.pop_back();
		}

		if (divergingConnection[ToPoint] != NULL) {
			if (divergingConnection[ToPoint]->Element == Element) {
				delete(divergingConnection[ToPoint]);
				divergingConnection[ToPoint] = 0;
			}			
		} else {
			if (straightConnection[ToPoint]->Element == Element) {
				delete(straightConnection[ToPoint]);
				straightConnection[ToPoint] = 0;
			}
		}
	}

	Entry *Cell::getEntry(int Point) {		
		return this->switches[Point] == 0 || (this->switches[Point] > 0 && this->switches[Point]->Position == SwitchPosition::Straight) ? this->straightConnection[Point] : this->divergingConnection[Point];
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
	
	bool Cell::isAllow(int Point, TrackElement Element){
		// TODO: the check logic point
		return true;
	}
}
