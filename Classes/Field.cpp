#include "Cell.h"
#include "Field.h"

namespace GameObjects {

	Field *Field::p_instance = 0;

	Field *Field::getInstance() {
		if (p_instance == 0) {
			p_instance = new Field;
		}
		return p_instance;
	}

	Field::Field()
	{	
		for (int x = 0; x < SizeX; x++){
			for (int y = 0; y < SizeY; y++){
				cells[x][y].x = x;
				cells[x][y].y = y;				
			}
		}
	}

	Field::~Field()
	{
	}

	void Field::AddTrain(Train *train)
	{
		this->trains.insert(trains.end(), *train);
	}
	
}
