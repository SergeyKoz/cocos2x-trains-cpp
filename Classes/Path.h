#ifndef __GAME_PATH_H__
#define __GAME_PATH_H__

#include <vector>
#include "Field.h"

using namespace std;

namespace GameObjects {

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
		int p;
		float dt;		
		float sin;
		float cos;
		Cell *sc;
	};

	struct GraphItem {
		bool isArea = false;
		bool isBorder = false;
		bool isInside = false;
		MapPoint p;
		int d[8];
		bool f[8];
		TrackElement e[8];
		Cell *In[8];
		int Out[8];
	};

	struct PathItem {
		TrackElement elementType;
		Sprite *element;
		int enter;
		Cell *current;
		Cell *next;
		int point;
	};

	struct TrackItem {
		int SpeedLimit;
		MapPoint shift[2];
		int point[8];
		SwitchElement Switch[2];
		int entry[8];
		int length;
		vector<Vec2> items;		
	};

	struct AccessItem {		
		byte access;
		byte c;
		MapPoint p;
	};

	struct AccessItems {
		vector<AccessItem> items;
	};

	class Path
	{

	public:
		Path();
		~Path();

		static const MapPoint closer[20];
		static const TrackItem track[24];		
		static const AccessItems access[2][24];

		Area Area;		
		GraphItem **Graph;
		vector<GraphItem*> GraphItems;
		vector<PathItem*> PathItems;
		vector<MapPoint> BorderItems;
		vector<MapPoint> InsideItems;
		MapSize size;
		MapPoint origin;

		bool Init(MapPoint Point);
		void Show(MapPoint Point, int Enter);
		void Find(Cell *c, int p = -1);
		void Set();
		GraphItem *graph(MapPoint Point);
		void Connect(Cell *out, int outPoint, TrackElement element, int d, int enter);

		bool isArea(MapPoint Point);
		bool inWindow(MapPoint Point);
		bool isAllow(Cell *out, int outPoint, int outEnter, Cell *in, int inPoint, int inEnter, TrackElement element);

		bool checkIntersection(MapPoint point1, int enter1, TrackElement element1, MapPoint point2, int enter2, TrackElement element2);
		static AccessItems getIntersection(MapPoint point, AccessItems items, MapPoint intersectPoint, AccessItems intersectItems);

		bool checkBaseCircle(Cell *cell, int point, int enter, TrackElement element);
		bool checkBaseCircle(TrackElement element, int enter, TrackElement graphElement);

		bool checkCrossover(Cell *cell, int point, int enter, TrackElement element);
		bool checkCrossover(TrackElement element, int enter, TrackElement graphElement);
		
		static Vec2 GetPosition(TrackPosition position);
		static TrackPosition GetPosition(TrackPosition position, int increase);
		static TrackPosition backPosition(TrackPosition position);

		//DrawNode *debugNode;
	};
}

#endif /*__GAME_PATH_H__*/

