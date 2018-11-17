#ifndef __GAME_RAILWAY_STATION_H__
#define __GAME_RAILWAY_STATION_H__

#include "Elements.h"

namespace GameObjects {

	class RailwayStation
	{
	public:
		RailwayStation();
		~RailwayStation();

		Sprite *resource;

		int id;
		int angle = 0;
		MapPoint position;

		void setPosition(MapPoint position, int angle);
		void remove();
	private:
		//vector<Train> trains;
	};
}
#endif /*__GAME_RAILWAY_STATION_H__*/
