#ifndef __GAME_CELL_H__
#define __GAME_CELL_H__

#include "Elements.h"
#include "Switch.h"
#include "Semaphore.h"
//#include "Path.h"
//#include <iostream>

namespace GameObjects {

	class Cell;
	struct AccessItem;
		
	enum Configuration {
		Undefined,
		Polar,
		Ortogonal
	};

	struct ConnectionConfig {
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
		vector<AccessItem> accessConfig;
	};
	
	class Cell
	{

	public:
		Cell();
		~Cell();

		int x, y;
		Configuration configuration = Configuration::Undefined;
		Entry *straightConnection[8];
		Entry *divergingConnection[8];
		Switch *switches[8];
		Semaphore *semaphores[8];

		Entry *connection[8];

		byte access;
		byte accessParam;

		static int Related[8];

		static Configuration GetPointConfiguration(int point);

		void Connect(TrackElement element, int Point, bool Back = false);
		void Disconnect(TrackElement element, int Point, bool Back = false);

		void SetSwitch(int Point);
		void RemoveSwitch(int Point);

		void SetSemaphore(int Point);
		void RemoveSemaphore(int Point);

		void SetEntry(Cell *cell, int FromPoint, int ToPoint, Configuration Configuration, TrackElement Element, int Enter);
		void RemoveEntry(Cell *cell, int FromPoint, int ToPoint, Configuration Configuration, TrackElement Element, int Enter);

		Entry *getEntry(int Point);
		Entry *getEntry(int Point, TrackElement element);
	
		//debug
		//DrawNode *debugNode;
		//void writeDebugNode(int x, int y, int a, int c, Color4F color);
	};
}

#endif /*__GAME_CELL_H__*/
