#ifndef __GAME_CELL_H__
#define __GAME_CELL_H__

#include "Elements.h"
#include "Switch.h"
#include "Semaphore.h"
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
		Switch *switches[8];
		Semaphore *semaphores[8];

		byte access;
		byte accessParam;

		//bool allowSwitch[8];
		//bool allowEnter[8][16];
		
		static int Related[8];

		void Connect(Cell *cell, int Point, bool Back = false);
		void Disconnect(Cell *cell, int Point, bool Back = false);

		void SetSwitch(int Point);
		void RemoveSwitch(int Point);

		void SetSemaphore(int Point);
		void RemoveSemaphore(int Point);

		void SetEntry(Cell *cell, int FromPoint, int ToPoint, Configuration Configuration, TrackElement Element, int Enter);
		void RemoveEntry(Cell *cell, int FromPoint, int ToPoint, Configuration Configuration, TrackElement Element, int Enter);

		Entry *getEntry(int Point);

		static ConnectionConfig *GetConnectConfig(int dx, int dy, int Point);
		
		//debug
		DrawNode *debugNode;

		void writeDebugNode(int x, int y, int a, int c, Color4F color);
	};
}

#endif /*__GAME_CELL_H__*/
