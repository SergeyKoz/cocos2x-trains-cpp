#ifndef __GAME_SWITCH_H__
#define __GAME_SWITCH_H__

#include "cocos2d.h"
#include "Elements.h"
#include "Train.h"

using namespace std;

namespace GameObjects {

	class Cell;
	class Train;

	enum SwitchPosition
	{
		Straight = 0,
		Diverging = 1
	};

	struct SwitchItem {
		SwitchElement type;
		Sprite *element;
	};

	class Switch
	{

	public:		
		Switch(Cell *cell, int Point);
		~Switch();
	
		SwitchPosition Position;
		Cell *cell;
		SwitchItem *positions[2];

		void changePosition();
		void setPosition(SwitchPosition position);
		void remove();

		vector<Train*> lookTrains;
		void listenLook(Train *train);
		void removeLook(Train *train);

		vector<Train*> overTrains;
		void listenOver(Train *train);
		void removeOver(Train *train);
	};
}

#endif /*__GAME_SWITCH_H__*/

