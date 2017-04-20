#include "MenuItem.h"
#include "cocos2d.h"

namespace GameObjects {

	MenuItem::MenuItem(Vector<cocos2d::MenuItem*> &items, MapPoint p, cocos2d::MenuItemImage *image, cocos2d::ccMenuCallback callback, bool isEnabled, bool isShowed)
	{
		checkable = false;

		buttonDefault = image;
		buttonDefault->setPosition(p.x, p.y);
		buttonDefault->setCallback(callback);

		items.pushBack(buttonDefault);
		
		show(isShowed);
		enable(isEnabled);
	}

	MenuItem::MenuItem(Vector<cocos2d::MenuItem*> &items, MapPoint p, ButtonCheckedImages images, cocos2d::ccMenuCallback callback, bool isEnabled, bool isShowed, bool isChecked)
	{
		checkable = true;
		
		buttonDefault = images.default;
		buttonChecked = images.checked;
		buttonDefault->setPosition(p.x, p.y);
		buttonChecked->setPosition(p.x, p.y);

		buttonDefault->setCallback(callback);
		buttonChecked->setCallback(callback);

		items.pushBack(buttonDefault);
		items.pushBack(buttonChecked);

		check(isChecked);
		show(isShowed);		
		enable(isEnabled);
	}

	void MenuItem::check(bool check) {
		checked = check;
		buttonChecked->setVisible(checked);
		buttonDefault->setVisible(!checked);
	}

	void MenuItem::show(bool show) {
		showed = show;
		if (checkable) {
			if (show) {
				buttonChecked->setVisible(checked);
				buttonDefault->setVisible(!checked);
			}
			else {
				buttonChecked->setVisible(false);
				buttonDefault->setVisible(false);
			}
		} else {
			buttonDefault->setVisible(show);
		}
	}

	void MenuItem::enable(bool enable) {
		enabled = enable;
		buttonDefault->setEnabled(enable);
		if (checkable) {
			buttonChecked->setEnabled(enable);
		}
	}

	MenuItem::~MenuItem()
	{
	}	
}
