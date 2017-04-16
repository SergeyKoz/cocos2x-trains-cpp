#ifndef __GAME_SWITCH_H__
#define __GAME_SWITCH_H__

#include "cocos2d.h"
#include "Elements.h"

using namespace std;

namespace GameObjects {

	class Cell;

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
	};
}

#endif /*__GAME_SWITCH_H__*/

