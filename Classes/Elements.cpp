#include "Elements.h"
#include "Field.h"
#include "Path.h"

namespace GameObjects {

	const char Elements::rules[16][24][140] = {
		{},
		{},
		{},
		{},

		{}, //BaseCircleSect0
		{},	//BaseCircleSect1	
		{ //BaseCircleSect2
			//0
			"63           |000 00000 000|000 00000 000|000 00000 000|000 00000 000|000 00000 000|000 00000 000|000 00000 000|000 00000 000|000 00000 000",
			"             |00000   00000|00000   00000|00000   00000|00000   00000|00000   00000|00000   00000|00000   00000|00000   00000|00000   00000",
			"             |000 00000 000|000 00000 000|000 00000 000|000 00010 100|000 00010 100|001 01000 000|001 01000 000|000 00000 000|000 00000 000",
			//1
			"000 00000 000|000 00000 000|000 00000 000|000 00000 000|000 00000 000|000 00000 000|000 00000 000|000 00000 000|000 00000 000|000 00000 000",
			"00000   00000|00000   00000|00000   00000|00000   00001|00000   00001|00000   00000|00000   00000|00001   00000|00001   00000|00000   00000",
			"000 00000 000|000 00000 000|000 00010 100|000 00011 100|000 01011 100|001 01011 100|001 01000 000|001 10000 000|000 00000 000|000 00000 000",
			//2
			"000 00000 000|000 00000 000|000 00000 000|000 00000 000|000 00000 000|000 00000 000|000 00000 000|000 00000 000|000 00000 000|000 00000 000",
			"00000   00000|00000   00001|00000   00011|00000   00011|00000   00001|00000   00000|00000   00000|00001   00000|00010   00000|00000   00000",
			"000 00000 000|000 00001 000|000 00000 101|000 00011 101|001 11011 111|001 11111 110|011 11111 000|010 00000 000|100 00000 000|000 00000 000",
			//3
			"000 00000 000|000 00000 000|000 00000 000|000 00000 000|000 00000 000|111 11111 111+111 11111 111+000 00000 000|000 00000 000|000 00000 000",
			"00000   00010|00000   00010|00000   00011|00000   00011|00000 1 11011|11011 1 11011+00010 1 00000+11011   00000|00000   00000|00000   00000",
			"000 00000 001|000 00000 001|000 00000 011|000 11111 111|101 11111 111|111 11111 111+111 11111 111+000 00000 000|000 00000 000|000 00000 000",
			//4
			"000 00000 000|000 00000 001|000 00000 000+111 11111 001+111 11111 111|111 11111 111|111 11111 000|110 00000 000|100 00000 000|000 00000 000",
			"00000   00000|00000   00000|00000   11110+11111   11111+11111   11000|11000   00000|11000   00000|00011   00000|01000   00000|00000   00000",
			"000 00000 000|000 00000 000|000 00000 000+101 11111 111+000 00000 000|000 00000 000|000 00000 000|000 00000 000|000 00000 000|000 00000 000",
			//5
			"000 00000 001|000 00000 000|000 00000 000|000 11111 100|011 11011 100|101 11011 100|101 11000 000|001 10000 000|000 10000 000|000 00000 000",
			"00000   01000|00000   01000|00000   10000|00000   10000|10000   10000|10000   00000|11000   00000|10000   00000|10000   00000|00000   00000",
			"000 00000 000|000 00000 000|000 00000 000|000 00000 000|000 00000 000|000 00000 000|000 00000 000|000 00000 000|000 00000 000|000 00000 000",
			//7
			"000 00000 000|000 00001 000|000 00000 100|000 00010 100|001 01010 100|001 11010 100|001 01000 000|001 01000 000|000 00000 000|000 00000 000",
			"00000   00000|00000   10000|00000   00000|00000   00000|00000   00000|10000   00000|00000   00000|00000   00000|00000   00000|00000   00000",
			"000 00000 000|000 00000 000|000 00000 000|000 00000 000|000 00000 000|000 00000 000|000 00000 000|000 00000 000|000 00000 000|000 00000 000",
			//8
			"000 00000 000|000 00000 000|000 00000 000|000 00000 000|000 00000 000|000 00000 000|000 00000 000|000 00000 000|000 00000 000|000 00000 000",
			"00000   00000|00000   00000|00000   00000|00000   00000|00000   00000|00000   00000|00000   00000|00000   00000|00000   00000|00000   00000",
			"000 00000 000|000 00000 000|000 00000 000|000 00000 000|000 00000 000|000 00000 000|000 00000 000|000 00000 000|000 00000 000|000 00000 000"
		},
		{},	//BaseCircleSect3
		{},	//BaseCircleSect4
		{},	//BaseCircleSect5
		{},	//BaseCircleSect6
		{},	//BaseCircleSect7

		{}, //SmallCilcleSect0
		{}, //SmallCilcleSect1
		{}, //SmallCilcleSect2
		{} //SmallCilcleSect3
	};

	const ElementOffset Elements::offset[2][16] = {
		{ { 0, -1, 2 }, { 1, 0, 4 }, { 1, 1, 5 }, { 1, -1, 3 }, { -1, 3, 7 }, { -3, 1, 0 }, { -3, -1, 1 }, { -1, -3, 2 }, { 1, -3, 3 }, { 3, -1, 4 }, { 3, 1, 5 }, { 1, 3, 6 }, { -2, 2, 0 }, { -2, -2, 2 }, { 2, -2, 4 }, { 2, 2, 6 } },
		{ { 0, 1, 6 }, { -1, 0, 0 }, { -1, -1, 1 }, { -1, 1, 7 }, { 1, -3, 2 }, { 3, -1, 3 }, { 3, 1, 4 }, { 1, 3, 5 }, { -1, 3, 6 }, { -3, 1, 7 }, { -3, -1, 0 }, { -1, -3, 1 }, { 2, -2, 2 }, { 2, 2, 4 }, { -2, 2, 6 }, { -2, -2, 0 } }
	};
	
	/*Elements *Elements::p_instance = 0;

	Elements *Elements::getInstance() {
	if (p_instance == 0) {
	p_instance = new Elements;
	}
	return p_instance;
	}
	*/

	Elements::Elements()
	{
	}

	Elements::~Elements()
	{
	}

	Sprite *Elements::GetElement(int x, int y, TrackElement Element){
		Sprite *item;
		Texture2D *texture = Director::getInstance()->getTextureCache()->addImage("rails.png");

		int d = 10 * Field::getInstance()->scale;

		if (Element == Horizontal) {
			item = Sprite::createWithTexture(texture, Rect(d, 2.5 * d, d, d));
			item->setPosition(x * d - 0.5 * d, y * d);
		}

		if (Element == Vertical) {
			item = Sprite::createWithTexture(texture, Rect(d - 0.5 * d, d, d, d));
			item->setPosition(x * d, y * d + 0.5 * d);
		}

		if (Element == Item45) {
			item = Sprite::createWithTexture(texture, Rect(3 * d - 0.5 * d, d - 0.5 * d, 2 * d, 2 * d));
			item->setPosition(x * d - 0.5 * d, y * d - 0.5 * d);
		}

		if (Element == Item135) {
			item = Sprite::createWithTexture(texture, Rect(3 * d - 0.5 * d, 3 * d - 0.5 * d, 2 * d, 2 * d));
			item->setPosition(x * d - 0.5 * d, y * d + 0.5 * d);
		}

		if (Element == BaseCircleSect0) {
			item = Sprite::createWithTexture(texture, Rect(4.5 * d, 0.5 * d, 2 * d, 4 * d));
			item->setPosition(x * d + 0.5 * d, y * d - 1.5 * d);
		}

		if (Element == BaseCircleSect1) {
			item = Sprite::createWithTexture(texture, Rect(6.5 * d, 0.5 * d, 4 * d, 2 * d));
			item->setPosition(x * d + 1.5 * d, y * d - 0.5 * d);
		}

		if (Element == BaseCircleSect2) {
			item = Sprite::createWithTexture(texture, Rect(6.5 * d, 2.5 * d, 4 * d, 2 * d));
			item->setPosition(x * d + 1.5 * d, y * d + 0.5 * d);
		}

		if (Element == BaseCircleSect3) {
			item = Sprite::createWithTexture(texture, Rect(10.5 * d, 0.5 * d, 2 * d, 4 * d));
			item->setPosition(x * d + 0.5 * d, y * d + 1.5 * d);
		}

		if (Element == BaseCircleSect4) {
			item = Sprite::createWithTexture(texture, Rect(12.5 * d, 0.5 * d, 2 * d, 4 * d));
			item->setPosition(x * d - 0.5 * d, y * d + 1.5 * d);
		}

		if (Element == BaseCircleSect5) {
			item = Sprite::createWithTexture(texture, Rect(14.5 * d, 0.5 * d, 4 * d, 2 * d));
			item->setPosition(x * d - 1.5 * d, y * d + 0.5 * d);
		}

		if (Element == BaseCircleSect6) {
			item = Sprite::createWithTexture(texture, Rect(14.5 * d, 2.5 * d, 4 * d, 2 * d));
			item->setPosition(x * d - 1.5 * d, y * d - 0.5 * d);
		}

		if (Element == BaseCircleSect7) {
			item = Sprite::createWithTexture(texture, Rect(18.5 * d, 0.5 * d, 2 * d, 4 * d));
			item->setPosition(x * d - 0.5 * d, y * d - 1.5 * d);
		}

		if (Element == SmallCilcleSect0) {
			item = Sprite::createWithTexture(texture, Rect(20.5 * d, 0.5 * d, 3 * d, 3 * d));
			item->setPosition(x * d + d, y * d - d);
		}

		if (Element == SmallCilcleSect1) {
			item = Sprite::createWithTexture(texture, Rect(23.5 * d, 0.5 * d, 3 * d, 3 * d));
			item->setPosition(x * d + d, y * d + d);
		}

		if (Element == SmallCilcleSect2) {
			item = Sprite::createWithTexture(texture, Rect(26.5 * d, 0.5 * d, 3 * d, 3 * d));
			item->setPosition(x * d - d, y * d + d);
		}

		if (Element == SmallCilcleSect3) {
			item = Sprite::createWithTexture(texture, Rect(29.5 * d, 0.5 * d, 3 * d, 3 * d));
			item->setPosition(x * d - d, y * d - d);
		}

		return item;
	}

	/*void Elements::setRules(int x, int y, TrackElement Element){

		if (Element == BaseCircleSect2) {

			int dx = (int)(rules[Element][0][0] - '0');
			int dy = (int)(rules[Element][0][1] - '0');

			Field *game = Field::getInstance();

			Cell *current;
			int ix, iy;
			

			bool Debug = true;
			DrawNode *draw;
			int ox, oy;
						
			for (int cx = 0; cx < 10; cx++){ //10
				for (int cy = 0; cy < 8; cy++){//8
					if ((cx != 0 || cy != 0) && (x + (cx - dx) > 0 && y + (cy - dy) > 0)){						
						current = &game->cells[x + (cx - dx)][y - (cy - dy)];
						ix = cx * 14;
						iy = cy * 3;

						if (Debug){
							ox = current->x * 20;
							oy = current->y * 20;
							draw = DrawNode::create();
							draw->drawRect(Vec2(ox, oy), Vec2(ox + 2, oy + 2), Color4F::BLACK);
							Field::getInstance()->trainsLayer->addChild(draw);
						}

						//0-------------
						setRule(current, ix + 12, iy + 1, 0, Element, SmallCilcleSect0);
						if (Debug && rules[Element][iy + 1][ix + 12] == '1'){
							draw = DrawNode::create();
							draw->drawRect(Vec2(ox + 4, oy - 2), Vec2(ox + 6, oy), Color4F::GREEN);
							Field::getInstance()->trainsLayer->addChild(draw);
						}

						setRule(current, ix + 11, iy + 1, 0, Element, BaseCircleSect1);
						if (Debug && rules[Element][iy + 1][ix + 11] == '1'){
							draw = DrawNode::create();
							draw->drawRect(Vec2(ox + 6, oy - 2), Vec2(ox + 8, oy), Color4F::GREEN);							
							Field::getInstance()->trainsLayer->addChild(draw);
						}

						setRule(current, ix + 10, iy + 1, 0, Element, Horizontal);
						if (Debug && rules[Element][iy + 1][ix + 10] == '1'){
							draw = DrawNode::create();
							draw->drawRect(Vec2(ox + 6, oy), Vec2(ox + 8, oy + 2), Color4F::ORANGE);							
							Field::getInstance()->trainsLayer->addChild(draw);
						}

						setRule(current, ix + 9, iy + 1, 0, Element, BaseCircleSect6);
						if (Debug && rules[Element][iy + 1][ix + 9] == '1'){
							draw = DrawNode::create();							
							draw->drawRect(Vec2(ox + 6, oy + 2), Vec2(ox + 8, oy + 4), Color4F::GREEN);
							Field::getInstance()->trainsLayer->addChild(draw);
						}

						setRule(current, ix + 8, iy + 1, 0, Element, SmallCilcleSect3);
						if (Debug && rules[Element][iy + 1][ix + 8] == '1'){
							draw = DrawNode::create();							
							draw->drawRect(Vec2(ox + 4, oy + 2), Vec2(ox + 6, oy + 4), Color4F::GREEN);
							Field::getInstance()->trainsLayer->addChild(draw);
						}

						//1-------------
						setRule(current, ix + 12, iy, 1, Element, BaseCircleSect7);
						if (Debug && rules[Element][iy][ix + 12] == '1'){
							draw = DrawNode::create();
							draw->drawRect(Vec2(ox + 6, oy + 4), Vec2(ox + 8, oy + 6), Color4F::BLUE);
							Field::getInstance()->trainsLayer->addChild(draw);
						}
						setRule(current, ix + 11, iy, 1, Element, Item45);
						if (Debug && rules[Element][iy][ix + 11] == '1'){
							draw = DrawNode::create();
							draw->drawRect(Vec2(ox + 4, oy + 4), Vec2(ox + 6, oy + 6), Color4F::RED);
							Field::getInstance()->trainsLayer->addChild(draw);
						}
						setRule(current, ix + 10, iy, 1, Element, BaseCircleSect2);
						if (Debug && rules[Element][iy][ix + 10] == '1'){
							draw = DrawNode::create();
							draw->drawRect(Vec2(ox + 4, oy + 6), Vec2(ox + 6, oy + 8), Color4F::BLUE);
							Field::getInstance()->trainsLayer->addChild(draw);
						}

						//2-------------						
						setRule(current, ix + 8, iy, 2, Element, SmallCilcleSect1);
						if (Debug && rules[Element][iy][ix + 8] == '1'){
							draw = DrawNode::create();
							draw->drawRect(Vec2(ox + 2, oy + 4), Vec2(ox + 4, oy + 6), Color4F::GREEN);
							Field::getInstance()->trainsLayer->addChild(draw);
						}

						setRule(current, ix + 7, iy, 2, Element, BaseCircleSect3);
						if (Debug && rules[Element][iy][ix + 7] == '1'){
							draw = DrawNode::create();
							draw->drawRect(Vec2(ox + 2, oy + 6), Vec2(ox + 4, oy + 8), Color4F::GREEN);
							Field::getInstance()->trainsLayer->addChild(draw);
						}

						setRule(current, ix + 6, iy, 2, Element, Vertical);
						if (Debug && rules[Element][iy][ix + 6] == '1'){
							draw = DrawNode::create();
							draw->drawRect(Vec2(ox, oy + 6), Vec2(ox + 2, oy + 8), Color4F::ORANGE);
							Field::getInstance()->trainsLayer->addChild(draw);
						}

						setRule(current, ix + 5, iy, 2, Element, BaseCircleSect0);
						if (Debug && rules[Element][iy][ix + 5] == '1'){
							draw = DrawNode::create();
							draw->drawRect(Vec2(ox - 2, oy + 6), Vec2(ox, oy + 8), Color4F::GREEN);
							Field::getInstance()->trainsLayer->addChild(draw);
						}

						setRule(current, ix + 4, iy, 2, Element, SmallCilcleSect0);
						if (Debug && rules[Element][iy][ix + 4] == '1'){
							draw = DrawNode::create();
							draw->drawRect(Vec2(ox - 2, oy + 4), Vec2(ox, oy + 6), Color4F::GREEN);
							Field::getInstance()->trainsLayer->addChild(draw);
						}

						//3-------------						
						setRule(current, ix + 2, iy, 3, Element, BaseCircleSect4);
						if (Debug && rules[Element][iy][ix + 2] == '1'){
							draw = DrawNode::create();
							draw->drawRect(Vec2(ox - 6, oy + 4), Vec2(ox - 4, oy + 6), Color4F::BLUE);
							Field::getInstance()->trainsLayer->addChild(draw);
						}
						setRule(current, ix + 1, iy, 3, Element, Item135);
						if (Debug && rules[Element][iy][ix + 1] == '1'){
							draw = DrawNode::create();
							draw->drawRect(Vec2(ox - 4, oy + 4), Vec2(ox - 2, oy + 6), Color4F::RED);
							Field::getInstance()->trainsLayer->addChild(draw);
						}
						setRule(current, ix, iy, 3, Element, BaseCircleSect1);
						if (Debug && rules[Element][iy][ix] == '1'){
							draw = DrawNode::create();
							draw->drawRect(Vec2(ox - 4, oy + 6), Vec2(ox - 2, oy + 8), Color4F::BLUE);
							Field::getInstance()->trainsLayer->addChild(draw);
						}

						//4-------------
						setRule(current, ix + 4, iy + 1, 4, Element, SmallCilcleSect2);
						if (Debug && rules[Element][iy + 1][ix + 4] == '1'){
							draw = DrawNode::create();
							draw->drawRect(Vec2(ox - 4, oy + 2), Vec2(ox - 2, oy + 4), Color4F::GREEN);
							Field::getInstance()->trainsLayer->addChild(draw);
						}
						
						setRule(current, ix + 3, iy + 1, 4, Element, BaseCircleSect5);
						if (Debug && rules[Element][iy + 1][ix + 3] == '1'){
							draw = DrawNode::create();
							draw->drawRect(Vec2(ox - 6, oy + 2), Vec2(ox - 4, oy + 4), Color4F::GREEN);
							Field::getInstance()->trainsLayer->addChild(draw);
						}

						setRule(current, ix + 2, iy + 1, 4, Element, Horizontal);
						if (Debug && rules[Element][iy + 1][ix + 2] == '1'){
							draw = DrawNode::create();
							draw->drawRect(Vec2(ox - 6, oy), Vec2(ox - 4, oy + 2), Color4F::ORANGE);
							Field::getInstance()->trainsLayer->addChild(draw);
						}

						setRule(current, ix + 1, iy + 1, 4, Element, BaseCircleSect2);
						if (Debug && rules[Element][iy + 1][ix + 1] == '1'){
							draw = DrawNode::create();
							draw->drawRect(Vec2(ox - 6, oy - 2), Vec2(ox - 4, oy), Color4F::GREEN);
							Field::getInstance()->trainsLayer->addChild(draw);
						}

						setRule(current, ix, iy + 1, 4, Element, SmallCilcleSect1);
						if (Debug && rules[Element][iy + 1][ix] == '1'){
							draw = DrawNode::create();
							draw->drawRect(Vec2(ox - 4, oy - 2), Vec2(ox - 2, oy), Color4F::GREEN);
							Field::getInstance()->trainsLayer->addChild(draw);
						}

						//5-------------
						setRule(current, ix, iy + 2, 5, Element, BaseCircleSect6);
						if (Debug && rules[Element][iy + 2][ix] == '1'){
							draw = DrawNode::create();
							draw->drawRect(Vec2(ox - 6, oy - 4), Vec2(ox - 4, oy - 2), Color4F::BLUE);
							Field::getInstance()->trainsLayer->addChild(draw);
						}

						setRule(current, ix + 1, iy + 2, 5, Element, Item45);
						if (Debug && rules[Element][iy + 2][ix + 1] == '1'){
							draw = DrawNode::create();
							draw->drawRect(Vec2(ox - 4, oy - 4), Vec2(ox - 2, oy - 2), Color4F::RED);
							Field::getInstance()->trainsLayer->addChild(draw);
						}

						setRule(current, ix + 2, iy + 2, 5, Element, BaseCircleSect7);
						if (Debug && rules[Element][iy + 2][ix + 2] == '1'){
							draw = DrawNode::create();
							draw->drawRect(Vec2(ox - 4, oy - 6), Vec2(ox - 2, oy - 4), Color4F::BLUE);
							Field::getInstance()->trainsLayer->addChild(draw);
						}

						//6-------------
						setRule(current, ix + 4, iy + 2, 6, Element, SmallCilcleSect3);
						if (Debug && rules[Element][iy + 2][ix + 4] == '1'){
							draw = DrawNode::create();
							draw->drawRect(Vec2(ox - 2, oy - 4), Vec2(ox, oy - 2), Color4F::GREEN);
							Field::getInstance()->trainsLayer->addChild(draw);
						}

						setRule(current, ix + 5, iy + 2, 6, Element, BaseCircleSect7);
						if (Debug && rules[Element][iy + 2][ix + 5] == '1'){
							draw = DrawNode::create();
							draw->drawRect(Vec2(ox - 2, oy - 6), Vec2(ox, oy - 4), Color4F::GREEN);
							Field::getInstance()->trainsLayer->addChild(draw);
						}

						setRule(current, ix + 6, iy + 2, 6, Element, Vertical);
						if (Debug && rules[Element][iy + 2][ix + 6] == '1'){
							draw = DrawNode::create();
							draw->drawRect(Vec2(ox, oy - 6), Vec2(ox + 2, oy - 4), Color4F::ORANGE);
							Field::getInstance()->trainsLayer->addChild(draw);
						}

						setRule(current, ix + 7, iy + 2, 6, Element, BaseCircleSect4);
						if (Debug && rules[Element][iy + 2][ix + 7] == '1'){
							draw = DrawNode::create();
							draw->drawRect(Vec2(ox + 2, oy - 6), Vec2(ox + 4, oy - 4), Color4F::GREEN);
							Field::getInstance()->trainsLayer->addChild(draw);
						}

						setRule(current, ix + 8, iy + 2, 6, Element, SmallCilcleSect2);
						if (Debug && rules[Element][iy + 2][ix + 8] == '1'){
							draw = DrawNode::create();
							draw->drawRect(Vec2(ox + 2, oy - 4), Vec2(ox + 4, oy - 2), Color4F::GREEN);
							Field::getInstance()->trainsLayer->addChild(draw);
						}

						//7-------------
						setRule(current, ix + 10, iy + 2, 7, Element, BaseCircleSect0);
						if (Debug && rules[Element][iy + 2][ix + 10] == '1'){
							draw = DrawNode::create();
							draw->drawRect(Vec2(ox + 4, oy - 6), Vec2(ox + 6, oy - 4), Color4F::BLUE);
							Field::getInstance()->trainsLayer->addChild(draw);
						}

						setRule(current, ix + 11, iy + 2, 7, Element, Item135);
						if (Debug && rules[Element][iy + 2][ix + 11] == '1'){
							draw = DrawNode::create();
							draw->drawRect(Vec2(ox + 4, oy - 4), Vec2(ox + 6, oy - 2), Color4F::RED);
							Field::getInstance()->trainsLayer->addChild(draw);
						}

						setRule(current, ix + 12, iy + 2, 7, Element, BaseCircleSect5);
						if (Debug && rules[Element][iy + 2][ix + 12] == '1'){
							draw = DrawNode::create();
							draw->drawRect(Vec2(ox + 6, oy - 4), Vec2(ox + 8, oy - 2), Color4F::BLUE);
							Field::getInstance()->trainsLayer->addChild(draw);
						}
					}
				}
			}
		}
	}

	void Elements::setRule(Cell *c, int x, int y, int p, TrackElement e1, TrackElement e2){
		if (rules[e1][y][x] == '1'){
			c->allowEnter[p][e2] = false;
		}
	}*/
}
