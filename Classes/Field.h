#ifndef __GAME_FIELD_H__
#define __GAME_FIELD_H__

#include "Elements.h"
#include "Cell.h"
#include "Train.h"

namespace GameObjects {

	enum ConstructionMode
	{
		ConstructNone,
		ConstructRails,
		ConstructSemafores,
		ConstructOpen
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
		ZIndexRailsBackground = 2,
		ZIndexSwitches = 3,
		ZIndexTrains = 4,
		ZIndexSemaphores = 5,
		ZIndexMenu = 6,
		ZIndexTrainsLabel = 7,
	};

	enum GameMode
	{
		ModeOn = 1,
		ModeOff = 0,
	};
	
	class Field
	{

	public:
		static Field *getInstance();
		static const int SizeX = 1500;
		static const int SizeY = 750;	
		Size sector = {200, 200};
		Cell cells[SizeX][SizeY];
		int scale = 2;
		ConstructionMode constuctionMode = ConstructionMode::ConstructNone;
		TrafficSide trafficSide = TrafficSide::RightHandTraffic; //LeftHandTraffic;
		GameMode gameMode = GameMode::ModeOff;
		
		Scene *scene;

		Layer *mapLayer;
		Layer *trainsLayer;		
		Layer *menuLayer;

		vector<Train> trains;
		void addTrain(Train train);
		void removeTrain();
		
		void save(string name);
		void open(string name);

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