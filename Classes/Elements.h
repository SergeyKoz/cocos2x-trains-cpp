#ifndef __GAME_ELEMENTS_H__
#define __GAME_ELEMENTS_H__ 

#include "cocos2d.h"
USING_NS_CC;

#include <string>

using namespace std;

namespace GameObjects {

	class Cell;

	struct MapPoint;
		
	enum TrackElement
	{
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

		/*StartButtonEnabled = 0,
		StartButtonDisabled = 1,
		FastButtonEnabled = 2,
		FastButtonDisabled = 3,
		PauseButtonEnabled = 4,
		PauseButtonDisabled = 5,
		StopButtonEnabled = 6,
		StopButtonDisabled = 7,
		RailsButtonEnabled = 8,
		RailsButtonDisabled = 9,
		RailsButtonCheckedEnabled = 10,
		RailsButtonCheckedDisabled = 11,
		SemaforesButtonEnabled = 12,
		SemaforesButtonDisabled = 13,
		SemaforesButtonCheckedEnabled = 14,
		SemaforesButtonCheckedDisabled = 15,
		ZoomInButtonEnabled = 16,
		ZoomInButtonDisabled = 17,
		ZoomOutButtonEnabled = 18,
		ZoomOutButtonDisabled = 19,
		UndoButtonEnabled = 20,
		UndoButtonDisabled = 21,
		RedoButtonEnabled = 22,
		RedoButtonDisabled = 23,
		TasksButtonEnabled = 24,
		TasksButtonDisabled = 25*/
	};

	struct ElementOffset {
		int dx;
		int dy;
		int p;
		SwitchElement sw;
	};

	class Elements
	{
	/*protected:
		Elements();
		Elements(const Elements&);
		Elements &operator=(Elements&);
		~Elements();
	private:
		static Elements *p_instance;*/
		
	public:
		Elements();
		~Elements();

		//static const char rules[16][24][140];
		static const ElementOffset offset[2][16];
		static const int second[2];

		static Elements *getInstance();
		static Sprite *GetTrackElement(MapPoint Point, TrackElement Element);
		static Sprite *GetSwitchElement(MapPoint Point, SwitchElement Element);

		static MenuItemImage *GetMenuElement(MenuElement Element);
		

		//static void setRules(int x, int y, TrackElement Element);
		//static void setRule(Cell *c, int x, int y, int p, TrackElement e1, TrackElement e2);
	};
}

#endif /*__GAME_ELEMENTS_H__*/
