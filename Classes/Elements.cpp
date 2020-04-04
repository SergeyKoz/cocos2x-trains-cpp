#include "Elements.h"
#include "Field.h"
#include "Path.h"

namespace GameObjects {

	const ElementOffset Elements::offset[2][24] = {
		{ 
			{ { 0, -1 }, 2 },
			{ { 1, 0 }, 4 },
			{ { 1, 1 }, 5 },
			{ { 1, -1 }, 3 },
			{ { -1, 3 }, 7 },
			{ { -3, 1 }, 0 },
			{ { -3, -1 }, 1 },
			{ { -1, -3 }, 2 },
			{ { 1, -3 }, 3 },
			{ { 3, -1 }, 4 },
			{ { 3, 1 }, 5 },
			{ { 1, 3 }, 6 },
			{ { -2, 2 }, 0 },
			{ { -2, -2 }, 2 },
			{ { 2, -2 }, 4 },
			{ { 2, 2 }, 6 },
			{ { 3, -1 }, 4 },
			{ { 3, 1 }, 4 },
			{ { 2, 1 }, 5 },
			{ { 1, 2 }, 5 },
			{ { 1, 3 }, 6 },
			{ { -1, 3 }, 6 },
			{ { -1, 2 }, 7 },
			{ { -2, 1 }, 7 },
		}, {
			{ { 0, 1 }, 6 },
			{ { -1, 0 }, 0 },
			{ { -1, -1 }, 1 },
			{ { -1, 1 }, 7 },
			{ { 1, -3 }, 2 },
			{ { 3, -1 }, 3 },
			{ { 3, 1 }, 4 },
			{ { 1, 3 }, 5 },
			{ { -1, 3 }, 6 },
			{ { -3, 1 }, 7 },
			{ { -3, -1 }, 0 },
			{ { -1, -3 }, 1 },
			{ { 2, -2 }, 2 },
			{ { 2, 2 }, 4 },
			{ { -2, 2 }, 6 },
			{ { -2, -2 }, 0 },
			{ { -3, 1 }, 0 },
			{ { -3, -1 }, 0 },
			{ { -2, -1 }, 1 },
			{ { -1, -2 }, 1 },
			{ { -1, -3 }, 2 },
			{ { 1, -3 }, 2 },
			{ { 1, -2 }, 3 },
			{ { 2, -1 }, 3 },
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

		if (Element == Crossover00 || Element == Crossover01 || Element == Crossover20 || Element == Crossover21) {
			item = Sprite::createWithTexture(texture, Rect(d, 16.5 * d, 3 * d, 2 * d));
		}

		if (Element == TrackElement::Crossover10 || Element == TrackElement::Crossover11 || Element == TrackElement::Crossover30 || Element == TrackElement::Crossover31) {
			item = Sprite::createWithTexture(texture, Rect(15.5 * d, 15.5 * d, 2 * d, 3 * d));
		}

		if (Element == TrackElement::Crossover00) {
			//item->setPosition(Point.x * d + 1.5 * d, Point.y * d - 0.5 * d);
			item->setPosition(Point.x * d - 1.5 * d, Point.y * d + 0.5 * d);
		}

		if (Element == TrackElement::Crossover01) {
			item->setFlippedY(true);
			//item->setPosition(Point.x * d + 1.5 * d, Point.y * d + 0.5 * d);
			item->setPosition(Point.x * d - 1.5 * d, Point.y * d - 0.5 * d);
		}

		if (Element == TrackElement::Crossover10) {
			item->setRotation(90);
			//item->setPosition(Point.x * d + 1 * d, Point.y * d + 0.5 * d);
			item->setPosition(Point.x * d - 1 * d, Point.y * d - 0.5 * d);
		}

		if (Element == TrackElement::Crossover11) {
			item->setFlippedX(true);
			//item->setPosition(Point.x * d + 0.5 * d, Point.y * d + 1.0 * d);
			item->setPosition(Point.x * d - 0.5 * d, Point.y * d - 1.0 * d);
		}

		if (Element == TrackElement::Crossover20) {
			item->setRotation(90);
			item->setPosition(Point.x * d - 0.5 * d, Point.y * d - 1.5 * d);
		}

		if (Element == TrackElement::Crossover21) {
			item->setFlippedY(true);
			item->setRotation(90);
			item->setPosition(Point.x * d + 0.5 * d, Point.y * d - 1.5 * d);
		}
		
		
		if (Element == TrackElement::Crossover30) {
			item->setPosition(Point.x * d + 0.5 * d, Point.y * d - 1.0 * d);
		}

		if (Element == TrackElement::Crossover31) {
			item->setFlippedX(true);
			item->setRotation(90);
			item->setPosition(Point.x * d + 1.0 * d, Point.y * d - 0.5 * d);
		}
		item->setName(Elements::getTrackElement(Element));

		return item;
	}

	Sprite *Elements::GetTrackBedElement(MapPoint Point, TrackElement Element) {
		Sprite *item;
		Texture2D *texture = Director::getInstance()->getTextureCache()->addImage("rails.png");

		int d = 10 * Field::getInstance()->scale;

		int dy = 22;

		if (Element == TrackElement::Horizontal) {
			item = Sprite::createWithTexture(texture, Rect(d, 24.5 * d, d, d));
			item->setPosition(Point.x * d - 0.5 * d, Point.y * d);
		}

		if (Element == TrackElement::Vertical) {
			item = Sprite::createWithTexture(texture, Rect(d - 0.5 * d, 23 * d, d, d));
			item->setPosition(Point.x * d, Point.y * d + 0.5 * d);
		}

		if (Element == TrackElement::Item45) {
			item = Sprite::createWithTexture(texture, Rect(3 * d - 0.5 * d, 22.5 * d, 2 * d, 2 * d));
			item->setPosition(Point.x * d - 0.5 * d, Point.y * d - 0.5 * d);
		}

		if (Element == TrackElement::Item135) {
			item = Sprite::createWithTexture(texture, Rect(3 * d - 0.5 * d, 24.5 * d, 2 * d, 2 * d));
			item->setPosition(Point.x * d - 0.5 * d, Point.y * d + 0.5 * d);
		}

		if (Element == TrackElement::BaseCircleSect0) {
			item = Sprite::createWithTexture(texture, Rect(4.5 * d, 22.5 * d, 2 * d, 4 * d));
			item->setPosition(Point.x * d + 0.5 * d, Point.y * d - 1.5 * d);
		}

		if (Element == TrackElement::BaseCircleSect1) {
			item = Sprite::createWithTexture(texture, Rect(6.5 * d, 22.5 * d, 4 * d, 2 * d));
			item->setPosition(Point.x * d + 1.5 * d, Point.y * d - 0.5 * d);
		}

		if (Element == TrackElement::BaseCircleSect2) {
			item = Sprite::createWithTexture(texture, Rect(6.5 * d, 24.5 * d, 4 * d, 2 * d));
			item->setPosition(Point.x * d + 1.5 * d, Point.y * d + 0.5 * d);
		}

		if (Element == TrackElement::BaseCircleSect3) {
			item = Sprite::createWithTexture(texture, Rect(10.5 * d, 22.5 * d, 2 * d, 4 * d));
			item->setPosition(Point.x * d + 0.5 * d, Point.y * d + 1.5 * d);
		}

		if (Element == TrackElement::BaseCircleSect4) {
			item = Sprite::createWithTexture(texture, Rect(12.5 * d, 22.5 * d, 2 * d, 4 * d));
			item->setPosition(Point.x * d - 0.5 * d, Point.y * d + 1.5 * d);
		}

		if (Element == TrackElement::BaseCircleSect5) {
			item = Sprite::createWithTexture(texture, Rect(14.5 * d, 22.5 * d, 4 * d, 2 * d));
			item->setPosition(Point.x * d - 1.5 * d, Point.y * d + 0.5 * d);
		}

		if (Element == TrackElement::BaseCircleSect6) {
			item = Sprite::createWithTexture(texture, Rect(14.5 * d, 24.5 * d, 4 * d, 2 * d));
			item->setPosition(Point.x * d - 1.5 * d, Point.y * d - 0.5 * d);
		}

		if (Element == TrackElement::BaseCircleSect7) {
			item = Sprite::createWithTexture(texture, Rect(18.5 * d, 22.5 * d, 2 * d, 4 * d));
			item->setPosition(Point.x * d - 0.5 * d, Point.y * d - 1.5 * d);
		}

		if (Element == TrackElement::SmallCilcleSect0) {
			item = Sprite::createWithTexture(texture, Rect(20.5 * d, 22.5 * d, 3 * d, 3 * d));
			item->setPosition(Point.x * d + d, Point.y * d - d);
		}

		if (Element == TrackElement::SmallCilcleSect1) {
			item = Sprite::createWithTexture(texture, Rect(23.5 * d, 22.5 * d, 3 * d, 3 * d));
			item->setPosition(Point.x * d + d, Point.y * d + d);
		}

		if (Element == TrackElement::SmallCilcleSect2) {
			item = Sprite::createWithTexture(texture, Rect(26.5 * d, 22.5 * d, 3 * d, 3 * d));
			item->setPosition(Point.x * d - d, Point.y * d + d);
		}

		if (Element == TrackElement::SmallCilcleSect3) {
			item = Sprite::createWithTexture(texture, Rect(29.5 * d, 22.5 * d, 3 * d, 3 * d));
			item->setPosition(Point.x * d - d, Point.y * d - d);
		}

		if (Element == TrackElement::Crossover00 || Element == TrackElement::Crossover01 || Element == TrackElement::Crossover20 || Element == TrackElement::Crossover21) {
			item = Sprite::createWithTexture(texture, Rect(d, 28.5 * d, 3 * d, 2 * d));
		}

		if (Element == TrackElement::Crossover10 || Element == TrackElement::Crossover11 || Element == TrackElement::Crossover30 || Element == TrackElement::Crossover31) {
			item = Sprite::createWithTexture(texture, Rect(15.5 * d, 27.5 * d, 2 * d, 3 * d));
		}

		if (Element == TrackElement::Crossover00) {
			item->setPosition(Point.x * d - 1.5 * d, Point.y * d + 0.5 * d);
		}

		if (Element == TrackElement::Crossover01) {
			item->setFlippedY(true);
			item->setPosition(Point.x * d - 1.5 * d, Point.y * d - 0.5 * d);
		}

		if (Element == TrackElement::Crossover10) {
			item->setRotation(90);
			item->setPosition(Point.x * d - 1 * d, Point.y * d - 0.5 * d);
		}

		if (Element == TrackElement::Crossover11) {
			item->setFlippedX(true);
			item->setPosition(Point.x * d - 0.5 * d, Point.y * d - 1.0 * d);
		}

		if (Element == TrackElement::Crossover20) {
			item->setRotation(90);
			item->setPosition(Point.x * d - 0.5 * d, Point.y * d - 1.5 * d);
		}

		if (Element == TrackElement::Crossover21) {
			item->setFlippedY(true);
			item->setRotation(90);
			item->setPosition(Point.x * d + 0.5 * d, Point.y * d - 1.5 * d);
		}


		if (Element == TrackElement::Crossover30) {
			item->setPosition(Point.x * d + 0.5 * d, Point.y * d - 1.0 * d);
		}

		if (Element == TrackElement::Crossover31) {
			item->setFlippedX(true);
			item->setRotation(90);
			item->setPosition(Point.x * d + 1.0 * d, Point.y * d - 0.5 * d);
		}
		item->setName(Elements::getTrackElement(Element));

		return item;
	}

	TrackElement Elements::getTrackElement(string element)
	{
		TrackElement el = TrackElement::None;
		if (element == "Vertical") {
			el = TrackElement::Vertical;
		} else if (element == "Horizontal") {
			el = TrackElement::Horizontal;
		} else if (element == "Item45") {
			el = TrackElement::Item45;
		} else if (element == "Item135") {
			el = TrackElement::Item135;
		} else if (element == "BaseCircleSect0") {
			el = TrackElement::BaseCircleSect0;
		} else if (element == "BaseCircleSect1") {
			el = TrackElement::BaseCircleSect1;
		} else if (element == "BaseCircleSect2") {
			el = TrackElement::BaseCircleSect2;
		} else if (element == "BaseCircleSect3") {
			el = TrackElement::BaseCircleSect3;
		} else if (element == "BaseCircleSect4") {
			el = TrackElement::BaseCircleSect4;
		} else if (element == "BaseCircleSect5") {
			el = TrackElement::BaseCircleSect5;
		} else if (element == "BaseCircleSect6") {
			el = TrackElement::BaseCircleSect6;
		} else if (element == "BaseCircleSect7") {
			el = TrackElement::BaseCircleSect7;
		} else if (element == "SmallCilcleSect0") {
			el = TrackElement::SmallCilcleSect0;
		} else if (element == "SmallCilcleSect1") {
			el = TrackElement::SmallCilcleSect1;
		} else if (element == "SmallCilcleSect2") {
			el = TrackElement::SmallCilcleSect2;
		} else if (element == "SmallCilcleSect3") {
			el = TrackElement::SmallCilcleSect3;
		} else if (element == "Crossover00") {
			el = TrackElement::Crossover00;
		} else if (element == "Crossover01") {
			el = TrackElement::Crossover01;
		} else if (element == "Crossover10") {
			el = TrackElement::Crossover10;
		} else if (element == "Crossover11") {
			el = TrackElement::Crossover11;
		} else if (element == "Crossover20") {
			el = TrackElement::Crossover20;
		} else if (element == "Crossover21") {
			el = TrackElement::Crossover21;
		} else if (element == "Crossover30") {
			el = TrackElement::Crossover30;
		} else if (element == "Crossover31") {
			el = TrackElement::Crossover31;
		}
		return el;
	}

	string Elements::getTrackElement(TrackElement Element)
	{
		string element = "None";
		switch (Element)
		{		
		case TrackElement::Vertical: element = "Vertical"; break;
		case TrackElement::Horizontal: element = "Horizontal"; break;
		case TrackElement::Item45: element = "Item45"; break;
		case TrackElement::Item135: element = "Item135"; break;
		case TrackElement::BaseCircleSect0: element = "BaseCircleSect0"; break;
		case TrackElement::BaseCircleSect1: element = "BaseCircleSect1"; break;
		case TrackElement::BaseCircleSect2: element = "BaseCircleSect2"; break;
		case TrackElement::BaseCircleSect3: element = "BaseCircleSect3"; break;
		case TrackElement::BaseCircleSect4: element = "BaseCircleSect4"; break;
		case TrackElement::BaseCircleSect5: element = "BaseCircleSect5"; break;
		case TrackElement::BaseCircleSect6: element = "BaseCircleSect6"; break;
		case TrackElement::BaseCircleSect7: element = "BaseCircleSect7"; break;
		case TrackElement::SmallCilcleSect0: element = "SmallCilcleSect0"; break;
		case TrackElement::SmallCilcleSect1: element = "SmallCilcleSect1"; break;
		case TrackElement::SmallCilcleSect2: element = "SmallCilcleSect2"; break;
		case TrackElement::SmallCilcleSect3: element = "SmallCilcleSect3"; break;
		case TrackElement::Crossover00: element = "Crossover00"; break;
		case TrackElement::Crossover01: element = "Crossover01"; break;
		case TrackElement::Crossover10: element = "Crossover10"; break;
		case TrackElement::Crossover11: element = "Crossover11"; break;
		case TrackElement::Crossover20: element = "Crossover20"; break;
		case TrackElement::Crossover21: element = "Crossover21"; break;
		case TrackElement::Crossover30: element = "Crossover30"; break;
		case TrackElement::Crossover31: element = "Crossover31"; break;

		default: element = "None"; break;
		}
		return element;
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

		//crossovers
		if (Element == Crossover000 || Element == Crossover001 || Element == Crossover010 || Element == Crossover011 || Element == Crossover200 || Element == Crossover201 || Element == Crossover210 || Element == Crossover211) {
			item = Sprite::createWithTexture(texture, Rect(d, 19.5 * d, 1.5 * d, 1.0 * d));
		}
		if (Element == Crossover100 || Element == Crossover101 || Element == Crossover110 || Element == Crossover111  || Element == Crossover300 || Element == Crossover301 || Element == Crossover310 || Element == Crossover311) {
			item = Sprite::createWithTexture(texture, Rect(14.5 * d, 18.75 * d, 1.5 * d, 1.5 * d));
		}

		if (Element == Crossover000) {
			item->setPosition(Point.x * d + 0.75 * d, Point.y * d - 0.0 * d);
		}

		if (Element == Crossover001) {
			item->setRotation(180);
			item->setPosition(Point.x * d - 0.75 * d, Point.y * d - 0.0 * d);
		}

		if (Element == Crossover010) {
			item->setFlippedY(true);
			item->setPosition(Point.x * d + 0.75 * d, Point.y * d - 0.0 * d);
		}

		if (Element == Crossover011) {
			item->setFlippedY(true);
			item->setRotation(180);
			item->setPosition(Point.x * d - 0.75 * d, Point.y * d - 0.0 * d);
		}
		
		if (Element == Crossover200) {
			item->setRotation(270);
			item->setPosition(Point.x * d - 0.0 * d, Point.y * d + 0.75 * d);
		}

		if (Element == Crossover201) {
			item->setRotation(90);
			item->setPosition(Point.x * d - 0.0 * d, Point.y * d - 0.75 * d);
		}
		
		if (Element == Crossover210) {
			item->setRotation(270);
			item->setFlippedY(true);
			item->setPosition(Point.x * d - 0.0 * d, Point.y * d + 0.75 * d);
		}

		if (Element == Crossover211) {
			item->setRotation(90);
			item->setFlippedY(true);
			item->setPosition(Point.x * d - 0.0 * d, Point.y * d - 0.75 * d);
		}

		//----------------
		if (Element == Crossover100) {
			item->setFlippedY(true);
			item->setFlippedX(true);
			item->setRotation(90);
			item->setPosition(Point.x * d + 0.5 * d, Point.y * d + 0.25 * d);
		}

		if (Element == Crossover101) {
			item->setRotation(90);
			item->setPosition(Point.x * d - 0.5 * d, Point.y * d - 0.25 * d);
		}

		if (Element == Crossover110) {
			item->setFlippedY(true);
			item->setPosition(Point.x * d + 0.25 * d, Point.y * d + 0.5 * d);
		}

		if (Element == Crossover111) {
			item->setFlippedX(true);
			item->setPosition(Point.x * d - 0.25 * d, Point.y * d - 0.5 * d);
		}

		if (Element == Crossover300) {
			item->setFlippedY(true);
			item->setFlippedX(true);
			item->setPosition(Point.x * d - 0.25 * d, Point.y * d + 0.5 * d);
		}

		if (Element == Crossover301) {
			item->setPosition(Point.x * d + 0.25 * d, Point.y * d - 0.5 * d);
		}


		if (Element == Crossover310) {
			item->setFlippedX(true);
			item->setRotation(90);
			item->setPosition(Point.x * d - 0.5 * d, Point.y * d + 0.25 * d);
		}
		if (Element == Crossover311) {
			item->setFlippedY(true);
			item->setRotation(90);
			item->setPosition(Point.x * d + 0.5 * d, Point.y * d - 0.25 * d);
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

	Sprite *Elements::GetObjectElement(ObjectsElement Element) {
		Sprite *item;
		Texture2D *texture = Director::getInstance()->getTextureCache()->addImage("objects.png");
		int d = 10 * Field::getInstance()->scale;

		if (Element == ObjectsElement::RailwayStaton) {			
			item = Sprite::createWithTexture(texture, Rect(20 * d, 10 * d, 8 * d, 10 * d));
			item->setName("RailwayStaton");
		}		
		return item;
	}

	CarElement Elements::getCarElement(string element)
	{
		CarElement el;
		if (element == "Locomotive") {
			el = CarElement::Locomotive;
		}
		else if (element == "TankCar") {
			el = CarElement::TankCar;
		}
		else if (element == "PassengerCar") {
			el = CarElement::PassengerCar;
		}
		else if (element == "FreightCar") {
			el = CarElement::FreightCar;
		}
		else if (element == "Switcher") {
			el = CarElement::Switcher;
		}				
		return el;
	}

	string Elements::getCarElement(CarElement Element)
	{
		string element;
		switch (Element)
		{
		case CarElement::Locomotive: element = "Locomotive"; break;
		case CarElement::TankCar: element = "TankCar"; break;
		case CarElement::PassengerCar: element = "PassengerCar"; break;
		case CarElement::FreightCar: element = "FreightCar"; break;
		case CarElement::Switcher: element = "Switcher"; break;
		default: element = ""; break;
		}
		return element;
	}

	TrainDirection Elements::getDirection(string direction)
	{
		TrainDirection el;
		if (direction == "Forward") {
			el = TrainDirection::Forward;
		} else if (direction == "Back") {
			el = TrainDirection::Back;
		}		
		return el;
	}

	SwitchPosition Elements::getSwitchPosition(string position)
	{
		SwitchPosition el;
		if (position == "Straight") {
			el = SwitchPosition::Straight;
		} else if (position == "Diverging") {
			el = SwitchPosition::Diverging;
		}
		return el;
	}

	SemaphorePosition Elements::getSemaphorePosition(string position)
	{
		SemaphorePosition el;
		if (position == "Go") {
			el = SemaphorePosition::Go;
		}
		else if (position == "Reverse") {
			el = SemaphorePosition::Reverse;
		}
		else if (position == "Stop") {
			el = SemaphorePosition::Stop;
		}
		return el;
	}
}
