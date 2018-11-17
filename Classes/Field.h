#ifndef __GAME_FIELD_H__
#define __GAME_FIELD_H__

#include "Elements.h"
#include "Cell.h"
#include "Train.h"
#include "RailwayStation.h"

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
		ZIndexBackground = 1,
		ZIndexBackgroundBuildings = 2,
		ZIndexBackgroundRails = 3,		
		ZIndexBuildings = 4,
		ZIndexRails = 5,		
		ZIndexSwitches = 6,
		ZIndexTrains = 7,
		ZIndexSemaphores = 8,
		ZIndexMenu = 9,		
		ZIndexTrainsLabel = 10
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
		Size sector = {20, 20};
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

		vector<RailwayStation> stations;
		void addRailwayStation(RailwayStation station);
		void removeRailwayStation();
		
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