#ifndef __GAME_ELEMENTS_H__
#define __GAME_ELEMENTS_H__ 

#include "cocos2d.h"
USING_NS_CC;

#include <string>
using namespace std;



namespace GameObjects {

	class Cell;
	
	struct ElementOffset{
		int dx;
		int dy;
		int p;
	};
	
	enum TrackElement
	{
		Vertical,
		Horizontal,
		Item45,
		Item135,
		BaseCircleSect0,
		BaseCircleSect1,
		BaseCircleSect2,
		BaseCircleSect3,
		BaseCircleSect4,
		BaseCircleSect5,
		BaseCircleSect6,
		BaseCircleSect7,
		SmallCilcleSect0,
		SmallCilcleSect1,
		SmallCilcleSect2,
		SmallCilcleSect3
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

		static const char rules[16][24][140];
		static const ElementOffset offset[2][16];

		static Elements *getInstance();
		static Sprite *GetElement(int x, int y, TrackElement Element);

		//static void setRules(int x, int y, TrackElement Element);
		//static void setRule(Cell *c, int x, int y, int p, TrackElement e1, TrackElement e2);
	};
}

#endif /*__GAME_ELEMENTS_H__*/
