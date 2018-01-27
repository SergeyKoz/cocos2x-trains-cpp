//#include "cocos2d.h"
#include "Switch.h"
#include "Field.h"
#include "Cell.h"

USING_NS_CC;

namespace GameObjects {
	
	Switch::Switch(Cell *cell, int Point)
	{
		//Field *Game = Field::getInstance();
		//Size visibleSize = Director::getInstance()->getVisibleSize();

		this->Position = Straight;
		this->cell = cell;

		SwitchElement Element;
		
		SwitchItem *straight = new SwitchItem();
		Element = Elements::offset[cell->straightConnection[Point]->Enter][cell->straightConnection[Point]->Element].sw;
		straight->element = Elements::GetSwitchElement({ cell->x, cell->y }, Element);
		straight->element->setVisible(true);
		straight->type = Element;
		this->positions[Straight] = straight;
		
		SwitchItem *diverging = new SwitchItem();
		Element = Elements::offset[cell->divergingConnection[Point]->Enter][cell->divergingConnection[Point]->Element].sw;
		diverging->element = Elements::GetSwitchElement({ cell->x, cell->y }, Element);
		diverging->element->setVisible(false);
		diverging->type = Element;		
		this->positions[Diverging] = diverging;

		/*auto box = DrawNode::create();
		Size sz = straight->element->getContentSize();
		Rect rect = straight->element->getBoundingBox();
		Vec2 p1 = rect.origin;
		Vec2 *p2 = new Vec2(p1.x, p1.y + sz.height);
		Vec2 *p3 = new Vec2(p1.x + sz.width, p1.y + sz.height);
		Vec2 *p4 = new Vec2(p1.x + sz.width, p1.y);
		box->setLineWidth(2);
		box->drawRect(p1, *p2, *p3, *p4, Color4F::GREEN);
		Field::getInstance()->mapLayer->addChild(box);

		auto box1 = DrawNode::create();
		Size sz1 = diverging->element->getContentSize();
		Rect rect1 = diverging->element->getBoundingBox();
		Vec2 p11 = rect1.origin;
		Vec2 *p21 = new Vec2(p11.x, p11.y + sz1.height);
		Vec2 *p31 = new Vec2(p11.x + sz1.width, p11.y + sz1.height);
		Vec2 *p41 = new Vec2(p11.x + sz1.width, p11.y);
		box1->setLineWidth(2);
		box1->drawRect(p11, *p21, *p31, *p41, Color4F::YELLOW);
		Field::getInstance()->mapLayer->addChild(box1);*/

		Switch *s = this;

		auto listener = EventListenerTouchOneByOne::create();
		listener->setSwallowTouches(true);
		listener->onTouchBegan = [](Touch* touch, Event* event) {

			Node *target = event->getCurrentTarget();
			/*Vec2 point = touch->getLocation();
			Rect rect = target->getBoundingBox();	
			bool  res = rect.containsPoint(point);*/
			
			/*Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
			Size size = target->getContentSize();
			Rect area = Rect(0, 0, size.width, size.height);
			res = area.containsPoint(locationInNode);*/

			Size size = target->getContentSize();
			bool touched = Rect(0, 0, size.width, size.height).containsPoint(target->convertToNodeSpace(touch->getLocation()));
			/*if (touched) {
				target->setOpacity(180);
			}*/
			return touched;
		};

		listener->onTouchMoved = [](Touch* touch, Event* event) {
		};

		listener->onTouchEnded = [&, s](Touch* touch, Event* event) { //[=]	
			s->changePosition();
			Node *target = event->getCurrentTarget();
			target->setOpacity(255);
		};

		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, straight->element);

		Field::getInstance()->mapLayer->addChild(positions[Straight]->element, ZIndexSwitches);
		Field::getInstance()->mapLayer->addChild(positions[Diverging]->element, ZIndexSwitches);
	}

	Switch::~Switch()
	{
		/*positions[Straight]->element->release();
		positions[Diverging]->element->release();*/
	}

	void Switch::changePosition()
	{
		if (this->Position == SwitchPosition::Straight) {
			this->positions[SwitchPosition::Straight]->element->setVisible(false);
			this->positions[SwitchPosition::Diverging]->element->setVisible(true);
			this->Position = SwitchPosition::Diverging;
		} else {
			this->positions[SwitchPosition::Diverging]->element->setVisible(false);
			this->positions[SwitchPosition::Straight]->element->setVisible(true);
			this->Position = SwitchPosition::Straight;
		}		
	}

	void Switch::setPosition(SwitchPosition position)
	{
		if (position == SwitchPosition::Straight && Position == SwitchPosition::Diverging) {
			
			this->positions[SwitchPosition::Diverging]->element->setVisible(false);
			this->positions[SwitchPosition::Straight]->element->setVisible(true);
			this->Position = position;
		}
		if (position == SwitchPosition::Diverging && Position == SwitchPosition::Straight) {
			this->positions[SwitchPosition::Straight]->element->setVisible(false);
			this->positions[SwitchPosition::Diverging]->element->setVisible(true);
			this->Position = position;
		}
	}

	void Switch::remove()
	{
		Field *game = Field::getInstance();
		Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(this->positions[Straight]->element);
		game->mapLayer->removeChild(positions[Straight]->element);
		game->mapLayer->removeChild(positions[Diverging]->element);
	}
}
