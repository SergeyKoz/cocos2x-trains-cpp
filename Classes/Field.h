#ifndef __GAME_FIELD_H__
#define __GAME_FIELD_H__

#include "Elements.h"
#include "Cell.h"

namespace GameObjects {

	enum ConstructionMode
	{
		Rails,
		Semafores
	};

	enum TrafficSide
	{
		RightHandTraffic,
		LeftHandTraffic
	};

	enum TouchMode
	{
		Move,
		BuildRails,
		SemaphoreShow
	};

	enum LayerZIndex
	{
		ZIndexRails = 1,
		ZIndexSwitches = 2,
		ZIndexTrains = 3,
		ZIndexSemaphores = 4,
		ZIndexMenu = 5
	};
	
	class Field
	{

	public:
		static Field *getInstance();
		static const int SizeX = 1000;
		static const int SizeY = 500;
		Cell cells[SizeX][SizeY];
		int scale = 2;
		ConstructionMode constuctionMode = Rails;
		TrafficSide trafficSide = RightHandTraffic; //LeftHandTraffic;

		Layer *mapLayer;
		Layer *trainsLayer;		
		Layer *menuLayer;		

	protected:
		Field();
		Field(const Field&);
		Field &operator=(Field&);
		~Field();

	private:
		static Field *p_instance;
	};
}

#endif /*__GAME_FIELD_H__*/