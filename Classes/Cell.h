#ifndef __GAME_CELL_H__
#define __GAME_CELL_H__

#include "Elements.h"
//#include <iostream>

namespace GameObjects {

	class Cell;
		
	enum Configuration{
		None,
		Polar,
		Ortogonal
	};

	struct ConnectionConfig{
		Configuration config;
		TrackElement element;
		int point;
		int enter;		
	};
	
	struct Entry {
		Cell *to = 0; 
		TrackElement Element;
		int Point;
		int Enter;
		Sprite *Resource;
	};
	
	class Cell
	{

	public:
		Cell();
		~Cell();

		int x, y;
		Configuration configuration = None;
		Entry *straightConnection[8];
		Entry *divergingConnection[8];

		//bool allowSwitch[8];
		//bool allowEnter[8][16];
		
		static int Related[8];

		void Connect(Cell *cell, int Point, bool Back = false);
		void SetEntry(Cell *cell, int FromPoint, int ToPoint, Configuration Configuration, TrackElement Element, int Enter);
		static ConnectionConfig *GetConnectConfig(int dx, int dy, int Point);
		bool isAllow(int Point, TrackElement Element);

	};
}

#endif /*__GAME_CELL_H__*/
