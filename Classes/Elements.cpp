#include "Elements.h"
#include "Field.h"
#include "Path.h"

namespace GameObjects {

	const ElementOffset Elements::offset[2][16] = {
		{ 
			{ 0, -1, 2, SwitchElement::Vertical0 },
			{ 1, 0, 4, SwitchElement::Horizontal0 },
			{ 1, 1, 5, SwitchElement::Item450 },
			{ 1, -1, 3, SwitchElement::Item1350 },
			{ -1, 3, 7, SwitchElement::BaseCircleSect00 },
			{ -3, 1, 0, SwitchElement::BaseCircleSect10 },
			{ -3, -1, 1, SwitchElement::BaseCircleSect20 },
			{ -1, -3, 2, SwitchElement::BaseCircleSect30 },
			{ 1, -3, 3, SwitchElement::BaseCircleSect40 },
			{ 3, -1, 4, SwitchElement::BaseCircleSect50 },
			{ 3, 1, 5, SwitchElement::BaseCircleSect60 },
			{ 1, 3, 6, SwitchElement::BaseCircleSect70 },
			{ -2, 2, 0, SwitchElement::SmallCilcleSect00 },
			{ -2, -2, 2, SwitchElement::SmallCilcleSect10 },
			{ 2, -2, 4, SwitchElement::SmallCilcleSect20 },
			{ 2, 2, 6, SwitchElement::SmallCilcleSect30 }
		}, {
			{ 0, 1, 6, SwitchElement::Vertical1 },
			{ -1, 0, 0, SwitchElement::Horizontal1 },
			{ -1, -1, 1, SwitchElement::Item451 },
			{ -1, 1, 7, SwitchElement::Item1351 },
			{ 1, -3, 2, SwitchElement::BaseCircleSect01 },
			{ 3, -1, 3, SwitchElement::BaseCircleSect11 },
			{ 3, 1, 4, SwitchElement::BaseCircleSect21 },
			{ 1, 3, 5, SwitchElement::BaseCircleSect31 },
			{ -1, 3, 6, SwitchElement::BaseCircleSect41 },
			{ -3, 1, 7, SwitchElement::BaseCircleSect51 },
			{ -3, -1, 0, SwitchElement::BaseCircleSect61 },
			{ -1, -3, 1, SwitchElement::BaseCircleSect71 },
			{ 2, -2, 2, SwitchElement::SmallCilcleSect01 },
			{ 2, 2, 4, SwitchElement::SmallCilcleSect11 },
			{ -2, 2, 6, SwitchElement::SmallCilcleSect21 },
			{ -2, -2, 0, SwitchElement::SmallCilcleSect31 }
		}
	};

	const int Elements::second[2] = { 1, 0 };
	
	Elements::Elements()
	{
	}

	Elements::~Elements()
	{
	}

	Sprite *Elements::GetEmpty() {
		Sprite *item;
		Texture2D *texture = Director::getInstance()->getTextureCache()->addImage("rails.png");
		item = Sprite::createWithTexture(texture, Rect(0, 0, 1, 1));
		item->setPosition(0, 0);
		return item;
	}

	Sprite *Elements::GetTrackElement(MapPoint Point, TrackElement Element) {
		Sprite *item;
		Texture2D *texture = Director::getInstance()->getTextureCache()->addImage("rails.png");

		int d = 10 * Field::getInstance()->scale;

		if (Element == Horizontal) {
			item = Sprite::createWithTexture(texture, Rect(d, 2.5 * d, d, d));
			item->setPosition(Point.x * d - 0.5 * d, Point.y * d);
		}

		if (Element == Vertical) {
			item = Sprite::createWithTexture(texture, Rect(d - 0.5 * d, d, d, d));
			item->setPosition(Point.x * d, Point.y * d + 0.5 * d);
		}

		if (Element == Item45) {
			item = Sprite::createWithTexture(texture, Rect(3 * d - 0.5 * d, d - 0.5 * d, 2 * d, 2 * d));
			item->setPosition(Point.x * d - 0.5 * d, Point.y * d - 0.5 * d);
		}

		if (Element == Item135) {
			item = Sprite::createWithTexture(texture, Rect(3 * d - 0.5 * d, 3 * d - 0.5 * d, 2 * d, 2 * d));
			item->setPosition(Point.x * d - 0.5 * d, Point.y * d + 0.5 * d);
		}

		if (Element == BaseCircleSect0) {
			item = Sprite::createWithTexture(texture, Rect(4.5 * d, 0.5 * d, 2 * d, 4 * d));
			item->setPosition(Point.x * d + 0.5 * d, Point.y * d - 1.5 * d);
		}

		if (Element == BaseCircleSect1) {
			item = Sprite::createWithTexture(texture, Rect(6.5 * d, 0.5 * d, 4 * d, 2 * d));
			item->setPosition(Point.x * d + 1.5 * d, Point.y * d - 0.5 * d);
		}

		if (Element == BaseCircleSect2) {
			item = Sprite::createWithTexture(texture, Rect(6.5 * d, 2.5 * d, 4 * d, 2 * d));
			item->setPosition(Point.x * d + 1.5 * d, Point.y * d + 0.5 * d);
		}

		if (Element == BaseCircleSect3) {
			item = Sprite::createWithTexture(texture, Rect(10.5 * d, 0.5 * d, 2 * d, 4 * d));
			item->setPosition(Point.x * d + 0.5 * d, Point.y * d + 1.5 * d);
		}

		if (Element == BaseCircleSect4) {
			item = Sprite::createWithTexture(texture, Rect(12.5 * d, 0.5 * d, 2 * d, 4 * d));
			item->setPosition(Point.x * d - 0.5 * d, Point.y * d + 1.5 * d);
		}

		if (Element == BaseCircleSect5) {
			item = Sprite::createWithTexture(texture, Rect(14.5 * d, 0.5 * d, 4 * d, 2 * d));
			item->setPosition(Point.x * d - 1.5 * d, Point.y * d + 0.5 * d);
		}

		if (Element == BaseCircleSect6) {
			item = Sprite::createWithTexture(texture, Rect(14.5 * d, 2.5 * d, 4 * d, 2 * d));
			item->setPosition(Point.x * d - 1.5 * d, Point.y * d - 0.5 * d);
		}

		if (Element == BaseCircleSect7) {
			item = Sprite::createWithTexture(texture, Rect(18.5 * d, 0.5 * d, 2 * d, 4 * d));
			item->setPosition(Point.x * d - 0.5 * d, Point.y * d - 1.5 * d);
		}

		if (Element == SmallCilcleSect0) {
			item = Sprite::createWithTexture(texture, Rect(20.5 * d, 0.5 * d, 3 * d, 3 * d));
			item->setPosition(Point.x * d + d, Point.y * d - d);
		}

		if (Element == SmallCilcleSect1) {
			item = Sprite::createWithTexture(texture, Rect(23.5 * d, 0.5 * d, 3 * d, 3 * d));
			item->setPosition(Point.x * d + d, Point.y * d + d);
		}

		if (Element == SmallCilcleSect2) {
			item = Sprite::createWithTexture(texture, Rect(26.5 * d, 0.5 * d, 3 * d, 3 * d));
			item->setPosition(Point.x * d - d, Point.y * d + d);
		}

		if (Element == SmallCilcleSect3) {
			item = Sprite::createWithTexture(texture, Rect(29.5 * d, 0.5 * d, 3 * d, 3 * d));
			item->setPosition(Point.x * d - d, Point.y * d - d);
		}

		return item;
	}

	Sprite *Elements::GetSwitchElement(MapPoint Point, SwitchElement Element) {
		Sprite *item;
		Texture2D *texture = Director::getInstance()->getTextureCache()->addImage("rails.png");
		int d = 10 * Field::getInstance()->scale;

		if (Element == Horizontal0) {
			item = Sprite::createWithTexture(texture, Rect(d, 6.5 * d, 1.5 * d, d));
			item->setPosition(Point.x * d + 0.75 * d, Point.y * d);
		}

		if (Element == Horizontal1) {
			item = Sprite::createWithTexture(texture, Rect(0.5 * d, 6.5 * d, 1.5 * d, d));
			item->setPosition(Point.x * d - 0.75 * d, Point.y * d);
		}

		if (Element == Vertical0) {
			item = Sprite::createWithTexture(texture, Rect(d - 0.5 * d, d + 4 * d, d, 1.5 * d));
			item->setPosition(Point.x * d, Point.y * d - 0.75 * d);
		}

		if (Element == Vertical1) {
			item = Sprite::createWithTexture(texture, Rect(d - 0.5 * d, d + 3.5 * d, d, 1.5 * d));
			item->setPosition(Point.x * d, Point.y * d + 0.75 * d);
		}

		if (Element == Item450) {
			item = Sprite::createWithTexture(texture, Rect(3 * d - 0.25 * d, d + 3.75 * d, 1.5 * d, 1.5 * d));
			item->setPosition(Point.x * d + 0.5 *  d, Point.y * d + 0.5 * d);
		}

		if (Element == Item451) {
			item = Sprite::createWithTexture(texture, Rect(3 * d - 0.25 * d, d + 3.75 * d, 1.5 * d, 1.5 * d));
			item->setPosition(Point.x * d - 0.5 *  d, Point.y * d - 0.5 * d);
		}

		if (Element == Item1350) {
			item = Sprite::createWithTexture(texture, Rect(3 * d - 0.25 * d, 3 * d + 3.75 * d, 1.5 * d, 1.5 * d));
			item->setPosition(Point.x * d + 0.5 *  d, Point.y * d - 0.5 * d);
		}

		if (Element == Item1351) {
			item = Sprite::createWithTexture(texture, Rect(3 * d - 0.5 * d, 3 * d + 3.5 * d, 1.5 * d, 1.5 * d));
			item->setPosition(Point.x * d - 0.5 *  d, Point.y * d + 0.5 * d);
		}

		// base circle
		if (Element == BaseCircleSect00) {
			item = Sprite::createWithTexture(texture, Rect(5.5 * d, 6.5 * d, d, 1.5 * d));
			item->setPosition(Point.x * d, Point.y * d + 0.75 * d);
		}

		if (Element == BaseCircleSect01) {
			item = Sprite::createWithTexture(texture, Rect(4.75 * d, 4.75 * d, 1.5 * d, 1.5 * d));
			item->setPosition(Point.x * d + 0.5 * d, Point.y * d - 0.5 * d);
		}

		if (Element == BaseCircleSect10) {
			item = Sprite::createWithTexture(texture, Rect(8.75 * d, 4.75 * d, 1.5 * d, 1.5 * d));
			item->setPosition(Point.x * d - 0.5 * d, Point.y * d + 0.5 * d);
		}

		if (Element == BaseCircleSect11) {
			item = Sprite::createWithTexture(texture, Rect(7 * d, 4.5 * d, 1.5 * d, d));
			item->setPosition(Point.x * d + 0.75 * d, Point.y * d);
		}

		if (Element == BaseCircleSect20) {
			item = Sprite::createWithTexture(texture, Rect(8.5 * d, 6.5 * d, 1.5 * d, d));
			item->setPosition(Point.x * d - 0.75 * d, Point.y * d);
		}

		if (Element == BaseCircleSect21) {
			item = Sprite::createWithTexture(texture, Rect(6.75 * d, 6.75 * d, 1.5 * d, 1.5 * d));
			item->setPosition(Point.x * d + 0.5 * d, Point.y * d + 0.5 * d);
		}

		if (Element == BaseCircleSect30) {
			item = Sprite::createWithTexture(texture, Rect(10.75 * d, 4.75 * d, 1.5 * d, 1.5 * d));
			item->setPosition(Point.x * d - 0.5 * d, Point.y * d - 0.5 * d);
		}

		if (Element == BaseCircleSect31) {
			item = Sprite::createWithTexture(texture, Rect(10.5 * d, 6.5 * d, d, 1.5 * d));
			item->setPosition(Point.x * d, Point.y * d + 0.75 * d);
		}

		if (Element == BaseCircleSect40) {
			item = Sprite::createWithTexture(texture, Rect(12.5 * d, 5 * d, d, 1.5 * d));
			item->setPosition(Point.x * d, Point.y * d - 0.75 * d);
		}

		if (Element == BaseCircleSect41) {
			item = Sprite::createWithTexture(texture, Rect(12.75 * d, 6.75 * d, 1.5 * d, 1.5 * d));
			item->setPosition(Point.x * d - 0.5 * d, Point.y * d + 0.5 * d);
		}

		if (Element == BaseCircleSect50) {
			item = Sprite::createWithTexture(texture, Rect(14.75 * d, 4.75 * d, 1.5 * d, 1.5 * d));
			item->setPosition(Point.x * d + 0.5 * d, Point.y * d - 0.5 * d);
		}

		if (Element == BaseCircleSect51) {
			item = Sprite::createWithTexture(texture, Rect(16.5 * d, 5.5 * d, 1.5 * d, d));
			item->setPosition(Point.x * d - 0.75 * d, Point.y * d);
		}

		if (Element == BaseCircleSect60) {
			item = Sprite::createWithTexture(texture, Rect(15 * d, 7.5 * d, 1.5 * d, d));
			item->setPosition(Point.x * d + 0.75 * d, Point.y * d);
		}

		if (Element == BaseCircleSect61) {
			item = Sprite::createWithTexture(texture, Rect(16.75 * d, 6.75 * d, 1.5 * d, 1.5 * d));
			item->setPosition(Point.x * d - 0.5 * d, Point.y * d - 0.5 * d);
		}

		if (Element == BaseCircleSect70) {
			item = Sprite::createWithTexture(texture, Rect(18.75 * d, 6.75 * d, 1.5 * d, 1.5 * d));
			item->setPosition(Point.x * d + 0.5 * d, Point.y * d + 0.5 * d);
		}

		if (Element == BaseCircleSect71) {
			item = Sprite::createWithTexture(texture, Rect(19.5 * d, 5 * d, d, 1.5 * d));
			item->setPosition(Point.x * d, Point.y * d - 0.75 * d);
		}

		// small circle
		if (Element == SmallCilcleSect00) {
			item = Sprite::createWithTexture(texture, Rect(22.5 * d, 5.5 * d, d, 1.5 * d));
			item->setPosition(Point.x * d, Point.y * d + 0.75 * d);
		}

		if (Element == SmallCilcleSect01) {
			item = Sprite::createWithTexture(texture, Rect(21 * d, 4.5 * d, 1.5 * d, d));
			item->setPosition(Point.x * d + 0.75 * d, Point.y * d);
		}

		if (Element == SmallCilcleSect10) {
			item = Sprite::createWithTexture(texture, Rect(24.5 * d, 4.5 * d, 1.5 * d, d));
			item->setPosition(Point.x * d - 0.75 * d, Point.y * d);
		}

		if (Element == SmallCilcleSect11) {
			item = Sprite::createWithTexture(texture, Rect(23.5 * d, 5.5 * d, d, 1.5 * d));
			item->setPosition(Point.x * d, Point.y * d + 0.75 * d);
		}

		if (Element == SmallCilcleSect20) {
			item = Sprite::createWithTexture(texture, Rect(26.5 * d, 5 * d, d, 1.5 * d));
			item->setPosition(Point.x * d, Point.y * d - 0.75 * d);
		}

		if (Element == SmallCilcleSect21) {
			item = Sprite::createWithTexture(texture, Rect(27.5 * d, 6.5 * d, 1.5 * d, d));
			item->setPosition(Point.x * d - 0.75 * d, Point.y * d);
		}

		if (Element == SmallCilcleSect30) {
			item = Sprite::createWithTexture(texture, Rect(30 * d, 6.5 * d, 1.5 * d, d));
			item->setPosition(Point.x * d + 0.75 * d, Point.y * d);
		}

		if (Element == SmallCilcleSect31) {
			item = Sprite::createWithTexture(texture, Rect(31.5 * d, 5 * d, d, 1.5 * d));
			item->setPosition(Point.x * d, Point.y * d - 0.75 * d);
		}
		return item;
	}

	MenuItemImage *Elements::GetMenuElement(MenuElement Element) {
		int d = 10 * Field::getInstance()->scale;
		Texture2D *texture = Director::getInstance()->getTextureCache()->addImage("rails.png");

		MenuItemImage *item = MenuItemImage::create();

		if (Element == StartButton) {
			item->setNormalImage(Sprite::createWithTexture(texture, Rect(d, 10 * d, 2 * d, 2 * d)));
			item->setDisabledImage(Sprite::createWithTexture(texture, Rect(d, 12 * d, 2 * d, 2 * d)));
		}

		if (Element == FastButton) {
			item->setNormalImage(Sprite::createWithTexture(texture, Rect(3 * d, 10 * d, 2 * d, 2 * d)));
			item->setDisabledImage(Sprite::createWithTexture(texture, Rect(3 * d, 12 * d, 2 * d, 2 * d)));
		}

		if (Element == PauseButton) {
			item->setNormalImage(Sprite::createWithTexture(texture, Rect(5 * d, 10 * d, 2 * d, 2 * d)));
			item->setDisabledImage(Sprite::createWithTexture(texture, Rect(5 * d, 12 * d, 2 * d, 2 * d)));
		}

		if (Element == StopButton) {
			item->setNormalImage(Sprite::createWithTexture(texture, Rect(7 * d, 10 * d, 2 * d, 2 * d)));
			item->setDisabledImage(Sprite::createWithTexture(texture, Rect(7 * d, 12 * d, 2 * d, 2 * d)));
		}
		
		//rails button
		if (Element == RailsButton) {
			item->setNormalImage(Sprite::createWithTexture(texture, Rect(9 * d, 10 * d, 2 * d, 2 * d)));
			item->setDisabledImage(Sprite::createWithTexture(texture, Rect(9 * d, 12 * d, 2 * d, 2 * d)));
		}		

		if (Element == RailsButtonChecked) {
			item->setNormalImage(Sprite::createWithTexture(texture, Rect(23 * d, 10 * d, 2 * d, 2 * d)));
			item->setDisabledImage(Sprite::createWithTexture(texture, Rect(23 * d, 12 * d, 2 * d, 2 * d)));
		}

		if (Element == SemaforesButton) {
			item->setNormalImage(Sprite::createWithTexture(texture, Rect(11 * d, 10 * d, 2 * d, 2 * d)));
			item->setDisabledImage(Sprite::createWithTexture(texture, Rect(11 * d, 12 * d, 2 * d, 2 * d)));
		}

		if (Element == SemaforesButtonChecked) {
			item->setNormalImage(Sprite::createWithTexture(texture, Rect(25 * d, 10 * d, 2 * d, 2 * d)));
			item->setDisabledImage(Sprite::createWithTexture(texture, Rect(25 * d, 12 * d, 2 * d, 2 * d)));
		}
		
		if (Element == ZoomInButton) {
			item->setNormalImage(Sprite::createWithTexture(texture, Rect(13 * d, 10 * d, 2 * d, 2 * d)));
			item->setDisabledImage(Sprite::createWithTexture(texture, Rect(13 * d, 12 * d, 2 * d, 2 * d)));
		}

		if (Element == ZoomOutButton) {
			item->setNormalImage(Sprite::createWithTexture(texture, Rect(15 * d, 10 * d, 2 * d, 2 * d)));
			item->setDisabledImage(Sprite::createWithTexture(texture, Rect(15 * d, 12 * d, 2 * d, 2 * d)));
		}

		if (Element == UndoButton) {
			item->setNormalImage(Sprite::createWithTexture(texture, Rect(17 * d, 10 * d, 2 * d, 2 * d)));
			item->setDisabledImage(Sprite::createWithTexture(texture, Rect(17 * d, 12 * d, 2 * d, 2 * d)));
		}

		if (Element == RedoButton) {
			item->setNormalImage(Sprite::createWithTexture(texture, Rect(19 * d, 10 * d, 2 * d, 2 * d)));
			item->setDisabledImage(Sprite::createWithTexture(texture, Rect(19 * d, 12 * d, 2 * d, 2 * d)));
		}

		if (Element == TasksButton) {
			item->setNormalImage(Sprite::createWithTexture(texture, Rect(21 * d, 10 * d, 2 * d, 2 * d)));
			item->setDisabledImage(Sprite::createWithTexture(texture, Rect(21 * d, 12 * d, 2 * d, 2 * d)));
		}
		return item;
	}

	Sprite *Elements::GetSemaphoreElement(MapPoint Point, SemaphorElement Element) {
		Sprite *item;
		Texture2D *texture = Director::getInstance()->getTextureCache()->addImage("rails.png");

		int d = 10 * Field::getInstance()->scale;
		int k = Field::getInstance()->trafficSide == LeftHandTraffic ? -1 : 1;
	
		if (Element == SemaphorGo0 || Element == SemaphorGo1 || Element == SemaphorGo2 || Element == SemaphorGo3 || Element == SemaphorGo4 || Element == SemaphorGo5 || Element == SemaphorGo6 || Element == SemaphorGo7) {
			item = Sprite::createWithTexture(texture, Rect(0.6 * d, 14.5 * d, 1 * d, 1 * d));
		}

		if (Element == SemaphorStop0 || Element == SemaphorStop1 || Element == SemaphorStop2 || Element == SemaphorStop3 || Element == SemaphorStop4 || Element == SemaphorStop5 || Element == SemaphorStop6 || Element == SemaphorStop7) {
			item = Sprite::createWithTexture(texture, Rect(1.6 * d, 14.5 * d, 1 * d, 1 * d));
		}

		if (Element == SemaphorReverse0 || Element == SemaphorReverse1 || Element == SemaphorReverse2 || Element == SemaphorReverse3 || Element == SemaphorReverse4 || Element == SemaphorReverse5 || Element == SemaphorReverse6 || Element == SemaphorReverse7) {
			item = Sprite::createWithTexture(texture, Rect(2.6 * d, 14.5 * d, 1 * d, 1 * d));
		}

		if (Element == SemaphorGo0 || Element == SemaphorStop0 || Element == SemaphorReverse0) {
			item->setPosition(Point.x * d, Point.y * d + k * 0.5 * d);
		}

		if (Element == SemaphorGo1 || Element == SemaphorStop1 || Element == SemaphorReverse1) {
			item->setPosition(Point.x * d - k * 0.3525 * d, Point.y * d + k * 0.3525 * d);
			item->setRotation(315);
		}

		if (Element == SemaphorGo2 || Element == SemaphorStop2 || Element == SemaphorReverse2) {
			item->setPosition(Point.x * d - k * 0.5 * d, Point.y * d);
			item->setRotation(270);
		}

		if (Element == SemaphorGo3 || Element == SemaphorStop3 || Element == SemaphorReverse3) {
			item->setPosition(Point.x * d - k * 0.3525 * d, Point.y * d - k * 0.3525 * d);
			item->setRotation(225);
		}

		if (Element == SemaphorGo4 || Element == SemaphorStop4 || Element == SemaphorReverse4) {
			item->setPosition(Point.x * d, Point.y * d - k * 0.5 * d);
			item->setRotation(180);
		}

		if (Element == SemaphorGo5 || Element == SemaphorStop5 || Element == SemaphorReverse5) {
			item->setPosition(Point.x * d + k * 0.3525 * d, Point.y * d - k * 0.3525 * d);
			item->setRotation(135);
		}

		if (Element == SemaphorGo6 || Element == SemaphorStop6 || Element == SemaphorReverse6) {
			item->setPosition(Point.x * d + k * 0.5 * d, Point.y * d);
			item->setRotation(90);
		}

		if (Element == SemaphorGo7 || Element == SemaphorStop7 || Element == SemaphorReverse7) {
			item->setPosition(Point.x * d + k * 0.3525 * d, Point.y * d + k * 0.3525 * d);
			item->setRotation(45);
		}
		
		return item;
	}

	Sprite *Elements::GetCarElement(CarElement Element) {
		Sprite *item;
		Texture2D *texture = Director::getInstance()->getTextureCache()->addImage("rails.png");
		int d = 10 * Field::getInstance()->scale;
		
		if (Element == Locomotive) {
			//item = Sprite::createWithTexture(texture, Rect(0.5 * d, 8.5 * d, 3 * d, 1 * d));
			item = Sprite::createWithTexture(texture, Rect(1 * d, 8.65 * d, 2 * d, 0.7 * d));
		}

		if (Element == TankCar) {
			//item = Sprite::createWithTexture(texture, Rect(3.5 * d, 8.5 * d, 3 * d, 1 * d));
			item = Sprite::createWithTexture(texture, Rect(4 * d, 8.65 * d, 2 * d, 0.7 * d));
		}

		if (Element == Switcher) {
			//item = Sprite::createWithTexture(texture, Rect(6.8 * d, 8.5 * d, 2 * d, 1 * d));
			item = Sprite::createWithTexture(texture, Rect(7 * d, 8.65 * d, 1.6 * d, 0.7 * d));
		}

		if (Element == PassengerCar) {		
		}

		if (Element == FreightCar) {
		}
		return item;
	}
}
