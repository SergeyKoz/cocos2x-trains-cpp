#ifndef __GAME_PATH_H__
#define __GAME_PATH_H__

#include <vector>
#include "Field.h"

using namespace std;

namespace GameObjects {

	/*struct MapPoint {
		int x;
		int y;
	};*/

	struct MapSize {
		int width;
		int height;
	};

	struct Area
	{		
		int Width = 4;
		MapPoint s;
		MapPoint e;
		MapPoint d;		
		float dt;		
		float sin;
		float cos;
		Cell *sc;
	};

	struct GraphItem{
		bool isArea = false;
		bool isBorder = false;
		bool isInside = false;
		MapPoint p;
		int d[8];
		bool f[8];
		Cell *In[8];
		int Out[8];
	};

	struct PathItem{
		TrackElement elementType;
		Sprite *element;
		int enter;
		Cell *current;
		Cell *next;
		int point;
	};

	struct TrackItem {
		int SpeedLimit;
		vector<Vec2> items;
	};
	
	class Path
	{

	public:
		Path();
		~Path();

		static const MapPoint closer[20];
		static const TrackItem track[16];
		Area Area;		
		GraphItem **Graph;
		vector<GraphItem*> GraphItems;
		vector<PathItem*> PathItems;
		vector<MapPoint> BorderItems;
		vector<MapPoint> InsideItems;
		MapSize size;
		MapPoint origin;

		bool Init(MapPoint Point);
		void Show(MapPoint Point);
		void Find(Cell *c, int p = -1);
		void Set();
		GraphItem *graph(MapPoint Point);
		void Connect(Cell *out, int outPoint, TrackElement element, int d, int enter);
		bool IsArea(MapPoint Point);

		bool inWindow(MapPoint Point);

		static Vec2 GetPosition(TrackPosition position);
		static TrackPosition GetPosition(TrackPosition position, int increase);

		/*		
		GetPosition(Position, Increase, EstimateObjects)
		GetPositionCoordinates(Position)
		EstimateObject(Indent, OutPoint, InPoint, Cell, Position)
		*/
	};
}

#endif /*__GAME_PATH_H__*/

