#ifndef __GAME_ELEMENTS_H__
#define __GAME_ELEMENTS_H__ 

#include "cocos2d.h"
USING_NS_CC;

#include <string>

using namespace std;

namespace GameObjects {

	class Cell;

	struct MapPoint {
		int x;
		int y;
	public:
		bool operator==(const MapPoint& p) {
			return x == p.x && y == p.y;
		}
		bool operator!=(const MapPoint& p) {
			return x != p.x || y != p.y;
		}
	};

	struct MapIndent {
		float dx;
		float dy;
	};

	struct TrackPosition {
		Cell *cell;
		int point;
		int indent;
	};
		
	enum TrackElement
	{
		None = -1,
		Vertical = 0,
		Horizontal = 1,
		Item45 = 2,
		Item135 = 3,
		BaseCircleSect0 = 4,
		BaseCircleSect1 = 5,
		BaseCircleSect2 = 6,
		BaseCircleSect3 = 7,
		BaseCircleSect4 = 8,
		BaseCircleSect5 = 9,
		BaseCircleSect6 = 10,
		BaseCircleSect7 = 11,
		SmallCilcleSect0 = 12,
		SmallCilcleSect1 = 13,
		SmallCilcleSect2 = 14,
		SmallCilcleSect3 = 15
	};

	enum SwitchElement
	{
		Vertical0 = 0,
		Vertical1 = 1,
		Horizontal0 = 2,
		Horizontal1 = 3,
		Item450 = 4,
		Item451 = 5,
		Item1350 = 6,
		Item1351 = 7,
		BaseCircleSect00 = 8,
		BaseCircleSect01 = 9,
		BaseCircleSect10 = 10,
		BaseCircleSect11 = 11,
		BaseCircleSect20 = 12,
		BaseCircleSect21 = 13,
		BaseCircleSect30 = 14,
		BaseCircleSect31 = 15,
		BaseCircleSect40 = 16,
		BaseCircleSect41 = 17,
		BaseCircleSect50 = 18,
		BaseCircleSect51 = 19,
		BaseCircleSect60 = 20,
		BaseCircleSect61 = 21,
		BaseCircleSect70 = 22,
		BaseCircleSect71 = 23,
		SmallCilcleSect00 = 24,
		SmallCilcleSect01 = 25,
		SmallCilcleSect10 = 26,
		SmallCilcleSect11 = 27,
		SmallCilcleSect20 = 28,
		SmallCilcleSect21 = 29,
		SmallCilcleSect30 = 30,
		SmallCilcleSect31 = 31
	};

	enum MenuElement {
		StartButton = 0,
		FastButton = 1,
		PauseButton = 2,
		StopButton = 3,
		RailsButton = 4,
		RailsButtonChecked = 5,
		SemaforesButton = 6,
		SemaforesButtonChecked = 7,
		ZoomInButton = 8,
		ZoomOutButton = 9,
		UndoButton = 10,
		RedoButton = 11,
		TasksButton = 12
	};

	enum SemaphorElement {
		SemaphorNone = -1,
		SemaphorGo0 = 0,
		SemaphorGo1 = 1,
		SemaphorGo2 = 2,
		SemaphorGo3 = 3,
		SemaphorGo4 = 4,
		SemaphorGo5 = 5,
		SemaphorGo6 = 6,
		SemaphorGo7 = 7,
		SemaphorStop0 = 8,
		SemaphorStop1 = 9,
		SemaphorStop2 = 10,
		SemaphorStop3 = 11,
		SemaphorStop4 = 12,
		SemaphorStop5 = 13,
		SemaphorStop6 = 14,
		SemaphorStop7 = 15,
		SemaphorStop8 = 16,
		SemaphorReverse0 = 17,
		SemaphorReverse1 = 18,
		SemaphorReverse2 = 19,
		SemaphorReverse3 = 20,
		SemaphorReverse4 = 21,
		SemaphorReverse5 = 22,
		SemaphorReverse6 = 23,
		SemaphorReverse7 = 24
	};

	enum CarElement {
		Locomotive = 1,
		TankCar = 2,
		PassengerCar = 3,
		FreightCar = 4,
		Switcher = 5,
	};

	struct ElementOffset {
		int dx;
		int dy;
		int p;		
		SwitchElement sw;
	};

	class Elements
	{	
	public:
		Elements();
		~Elements();

		//static const char rules[16][24][140];
		static const ElementOffset offset[2][16];
		static const int second[2];

		static Elements *getInstance();
		static Sprite *GetEmpty();
		static Sprite *GetTrackElement(MapPoint Point, TrackElement Element);
		static Sprite *GetSwitchElement(MapPoint Point, SwitchElement Element);
		static Sprite *GetSemaphoreElement(MapPoint Point, SemaphorElement Element);
		static Sprite *GetCarElement(CarElement Element);
		static MenuItemImage *GetMenuElement(MenuElement Element);
		
		//static void setRules(int x, int y, TrackElement Element);
		//static void setRule(Cell *c, int x, int y, int p, TrackElement e1, TrackElement e2);
	};
}
#endif /*__GAME_ELEMENTS_H__*/
