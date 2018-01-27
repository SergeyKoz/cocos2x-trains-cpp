#include "Cell.h"
#include "Field.h"
#include "Semaphore.h"
#include "Cmd.h"

namespace GameObjects {

	Semaphore::Semaphore()
	{
	}
	
	Semaphore::Semaphore(Cell *cell, int Point)
	{
		Field *game = Field::getInstance();
		this->cell = cell;

		MapPoint p = { cell->x, cell->y };

		if (Point == 0) {			
			this->Resources = { Elements::GetSemaphoreElement(p, SemaphorGo0), Elements::GetSemaphoreElement(p, SemaphorReverse0) , Elements::GetSemaphoreElement(p, SemaphorStop0) };
		}

		if (Point == 1) {
			this->Resources = { Elements::GetSemaphoreElement(p, SemaphorGo1), Elements::GetSemaphoreElement(p, SemaphorReverse1) , Elements::GetSemaphoreElement(p, SemaphorStop1) };
		}

		if (Point == 2) {
			this->Resources = { Elements::GetSemaphoreElement(p, SemaphorGo2), Elements::GetSemaphoreElement(p, SemaphorReverse2) , Elements::GetSemaphoreElement(p, SemaphorStop2) };
		}

		if (Point == 3) {
			this->Resources = { Elements::GetSemaphoreElement(p, SemaphorGo3), Elements::GetSemaphoreElement(p, SemaphorReverse3) , Elements::GetSemaphoreElement(p, SemaphorStop3) };
		}

		if (Point == 4) {
			this->Resources = { Elements::GetSemaphoreElement(p, SemaphorGo4), Elements::GetSemaphoreElement(p, SemaphorReverse4) , Elements::GetSemaphoreElement(p, SemaphorStop4) };
		}

		if (Point == 5) {
			this->Resources = { Elements::GetSemaphoreElement(p, SemaphorGo5), Elements::GetSemaphoreElement(p, SemaphorReverse5) , Elements::GetSemaphoreElement(p, SemaphorStop5) };
		}

		if (Point == 6) {
			this->Resources = { Elements::GetSemaphoreElement(p, SemaphorGo6), Elements::GetSemaphoreElement(p, SemaphorReverse6) , Elements::GetSemaphoreElement(p, SemaphorStop6) };
		}

		if (Point == 7) {
			this->Resources = { Elements::GetSemaphoreElement(p, SemaphorGo7), Elements::GetSemaphoreElement(p, SemaphorReverse7) , Elements::GetSemaphoreElement(p, SemaphorStop7) };
		}

		Semaphore *s = this;

		auto listener = EventListenerTouchOneByOne::create();
		listener->setSwallowTouches(true);
		listener->onTouchBegan = [](Touch* touch, Event* event) {
			Node *target = event->getCurrentTarget();
			Size size = target->getContentSize();
			bool touched = Rect(0, 0, size.width, size.height).containsPoint(target->convertToNodeSpace(touch->getLocation()));
			return touched;
		};

		listener->onTouchMoved = [](Touch* touch, Event* event) {
		};

		listener->onTouchEnded = [&, s](Touch* touch, Event* event) { //[=]
			if (!trains.empty()) {
				vector<Train*>::iterator i = trains.begin();;
				for (int i = 0; i < trains.size(); i++)
				{
					/*if (Position == SemaphorePosition::Reverse) {
						trains[i]->direction == trains[i]->direction == TrainDirection::Forward ? TrainDirection::Back : TrainDirection::Forward;
					}*/
					trains[i]->SpeedReset();
				}
			}
			s->Next();
		};

		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this->Resources.go);

		game->mapLayer->addChild(this->Resources.go, ZIndexSemaphores);
		game->mapLayer->addChild(this->Resources.reverse, ZIndexSemaphores);
		game->mapLayer->addChild(this->Resources.stop, ZIndexSemaphores);

		this->SetPosition(Go);		
	}

	Semaphore::~Semaphore()
	{		
	}

	void Semaphore::remove()
	{
		Field *game = Field::getInstance();

		Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(this->Resources.go);

		game->mapLayer->removeChild(this->Resources.go);
		game->mapLayer->removeChild(this->Resources.reverse);
		game->mapLayer->removeChild(this->Resources.stop);
		/*this->Resources.go->release();
		this->Resources.reverse->release();
		this->Resources.stop->release();*/
	}

	bool Semaphore::Show(MapPoint Point, MapIndent Indent)
	{
		bool show = false;
		Field *game = Field::getInstance();
		Cell *cell = &game->cells[Point.x][Point.y];

		ShowItem item = showItem;

		if (cell->configuration == Polar || cell->configuration == Ortogonal) {
			int k = game->trafficSide == LeftHandTraffic ? -1 : 1;
				
			if (cell->configuration == Ortogonal) {
				if (AllowedPoint(cell, 0) && k * Indent.dy < 0) {
					showItem = { Point , 0, SemaphorGo0, Elements::GetSemaphoreElement(Point, SemaphorGo0) };
					show = true;
				}

				if (AllowedPoint(cell, 4) && k * Indent.dy > 0) {
					showItem = { Point , 4, SemaphorGo4, Elements::GetSemaphoreElement(Point, SemaphorGo4) };
					show = true;
				}

				if (AllowedPoint(cell, 2) && k * Indent.dx > 0) {
					showItem = { Point , 2, SemaphorGo2, Elements::GetSemaphoreElement(Point, SemaphorGo2) };
					show = true;
				}

				if (AllowedPoint(cell, 6) && k * Indent.dx < 0) {
					showItem = { Point , 6, SemaphorGo6, Elements::GetSemaphoreElement(Point, SemaphorGo6) };
					show = true;
				}				
			}

			if (cell->configuration == Polar) {

				if (AllowedPoint(cell, 1) && -Indent.dx * k  < -Indent.dy * k) {
					showItem = { Point , 1, SemaphorGo1, Elements::GetSemaphoreElement(Point, SemaphorGo1) };
					show = true;
				}

				if (AllowedPoint(cell, 5) && -Indent.dx * k  > -Indent.dy * k) {
					showItem = { Point , 5, SemaphorGo5, Elements::GetSemaphoreElement(Point, SemaphorGo5) };
					show = true;
				}

				if (AllowedPoint(cell, 3) && -Indent.dx * k  < Indent.dy * k) {
					showItem = { Point , 3, SemaphorGo3, Elements::GetSemaphoreElement(Point, SemaphorGo3) };
					show = true;
				}

				if (AllowedPoint(cell, 7) && -Indent.dx * k  > Indent.dy * k) {
					showItem = { Point , 7, SemaphorGo7, Elements::GetSemaphoreElement(Point, SemaphorGo7) };
					show = true;
				}
			}
		}

		if (show) {
			if (item.elementType != SemaphorNone) {
				game->mapLayer->removeChild(item.element);
			}			
			game->mapLayer->addChild(showItem.element, ZIndexSemaphores);
		}
		
		return show;
	}

	void Semaphore::Hide()
	{
		if (showItem.elementType != SemaphorNone) {			
			Field::getInstance()->mapLayer->removeChild(showItem.element);
			showItem.elementType = SemaphorNone;
		}
	}

	void Semaphore::Set()
	{
		if (showItem.elementType != SemaphorNone)
		{
			string	command = StringUtils::format("semaphore --add --cell={\"x\":%d,\"y\":%d} --point=%d", showItem.point.x, showItem.point.y, showItem.enter);
			Cmd::Exec(command);
			Hide();
		}
	}

	bool Semaphore::AllowedPoint(Cell *cell, int Point)
	{
		return cell->straightConnection[Point] != 0 && cell->switches[Point] == 0 && cell->semaphores[Point] == 0;
	}

	void Semaphore::SetPosition(SemaphorePosition pos)
	{
		Resources.go->setVisible(false);
		Resources.reverse->setVisible(false);
		Resources.stop->setVisible(false);
		if (pos == Go) {
			Resources.go->setVisible(true);
		}
		if (pos == Reverse) {
			Resources.reverse->setVisible(true);
		}
		if (pos == Stop) {
			Resources.stop->setVisible(true);
		}
		Position = pos;
	}

	void Semaphore::Next()
	{
		if (Position == Go) {
			SetPosition(Reverse);
		} else if (Position == Reverse) {
			SetPosition(Stop);
		} else {
			SetPosition(Go);
		}
	}
	
	void Semaphore::listen(Train *train)
	{
		trains.push_back(train);
	}

	void Semaphore::remove(Train *train)
	{
		trains.erase(std::remove(trains.begin(), trains.end(), train), trains.end());
	}
}
