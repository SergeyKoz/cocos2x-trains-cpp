#ifndef __GAME_MENUITEM_H__
#define __GAME_MENUITEM_H__

#include "cocos2d.h"
#include "GameObjects.h"

//#include "Elements.h"
//#include "Cell.h"

namespace GameObjects {

	struct ButtonDefaultImages {
		cocos2d::MenuItemImage *default;
	};

	struct ButtonCheckedImages {
		cocos2d::MenuItemImage *default;
		cocos2d::MenuItemImage *checked;
	};

	class MenuItem
	{

	public:
		MenuItem(Vector<cocos2d::MenuItem*> &items, MapPoint p, cocos2d::MenuItemImage *image, cocos2d::ccMenuCallback callback, bool isEnabled, bool isShowed);
		MenuItem(Vector<cocos2d::MenuItem*> &items, MapPoint p, ButtonCheckedImages images, cocos2d::ccMenuCallback callback, bool isEnabled, bool isShowed, bool isChecked);

		cocos2d::MenuItemImage *buttonDefault;
		cocos2d::MenuItemImage *buttonChecked;

		bool checkable;
		bool enabled;
		bool showed;
		bool checked;

		void check(bool check);
		void show(bool show);
		void enable(bool enable);
		
		~MenuItem();
	
	};
}

#endif /*__GAME_MENUITEM_H__*/