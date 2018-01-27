#include "Train.h"
#include "Car.h"
#include "Path.h"
#include <math.h>

namespace GameObjects {

	Train::Train()
	{
		Field *Game = Field::getInstance();		
		label = Label::createWithTTF("0", "fonts/digital-7.ttf", 10);
		label->setColor(Color3B::BLACK);
		Game->trainsLayer->addChild(label, ZIndexTrainsLabel);
		// debug
		//debugNode = DrawNode::create();
		//Game->mapLayer->addChild(debugNode, ZIndexTrainsLabel);
	}

	Train::~Train()
	{
		Field::getInstance()->trainsLayer->removeChild(label);
		this->cars.clear();
	}

	void Train::AddCar(Car car)
	{
		int c = this->cars.size();
		
		//this->cars.insert(cars.end(), car);		

		this->cars.push_back(car);

		if (Car::settings[car.type].traction > 0) {
			speed.maxSpeed += Car::settings[car.type].traction;
			speed.length = ceil(speed.maxSpeed / acceleration) * 2;
			//speed.lookLength = ceil(speed.length / 3);
			if (speed.speeds != 0) {			
				delete[] speed.speeds;				
			}
			speed.speeds = new int[speed.length];
			/*for (int i = 0; i < speed.length; i++) {
				speed.speeds[i] = 0;
			}*/			
		}
		length += Car::settings[car.type].base + 4;

		/*if (c > 0) {
			Field *Game = Field::getInstance();
			PhysicsBody* physicsBody1 = this->cars[c].resource->getPhysicsBody();
			PhysicsBody* physicsBody2 = this->cars[c - 1].resource->getPhysicsBody();			
			Vec2 p1 = {20, 0}; //Point::ZERO
			Vec2 p2 = {-20, 0}; //Point::ZERO			
			PhysicsJointDistance* joint = PhysicsJointDistance::construct(physicsBody1, physicsBody2, p1, p2);
			Game->scene->getPhysicsWorld()->addJoint(joint);
		}*/
	}

	void Train::init()
	{
		for (int i = 0; i < speed.length; i++) {
			speed.speeds[i] = 0;
		}

		/*for (int i = 0; i < 20; i++) {
			debugItems[i] = Vec2(0, 0);
		}*/
	}

	void Train::remove()
	{
		for (int i = 0; i < this->cars.size(); i++) {
			this->cars[i].remove();
		}
	}

	void Train::move()
	{
		/*Vec2 d = { 0, 2 };
		if (speed.length > 0) {
			int speed = GetSpeed();
			TrackPosition pos = Path::GetPosition(this->position, speed);
			this->position = pos;			
			for (int i = 0; i < cars.size(); i++) {
				pos = cars[i].SetPosition(pos);
				if ((direction == TrainDirection::Forward && i == 0) || (direction == TrainDirection::Back && i == cars.size() - 1) ) {
					label->setString(std::to_string(speed));
					label->setPosition(cars[i].position.p + d);
				}				
			}
		}*/

		//pin->setPosition(this->cars[0].move.p);

		GetMove(GetSpeed());
		RunMove();
	}

	void Train::SetPosition(TrackPosition position)
	{
		this->position = position;
		TrackPosition pos = position;

		//pin->setPosition({0, 0});

		for (int i = 0; i < cars.size(); i++) {
			pos = cars[i].SetPosition(pos);			
			cars[i].resource->setVisible(true);
		}
	}
	
	void Train::GetMove(int move)
	{			
		this->position = Path::GetPosition(this->position, move);
		for (int i = 0; i < cars.size(); i++) {
			cars[i].GetMove(move);
			//cars[i].RunMove();
		}
	}

	void Train::RunMove()
	{
		for (int i = 0; i < cars.size(); i++) {
			cars[i].RunMove();
		}
	}

	int Train::GetSpeed()
	{
		int k = direction == TrainDirection::Forward ? 1 : -1;
		int limit = this->speed.overLimit;
		checkOverTrack();
		
		if (limit - this->speed.overLimit != 0 && k * this->speed.speeds[this->speed.pointer] != this->speed.overLimit) {
			this->speed.limit = this->speed.overLimit;
			SpeedReset();
		}

		bool f = true;
		while (this->speed.lookPointers < this->speed.length / 2 && f) {
			if (this->speed.speeds[this->speed.lookPointer] == k * this->speed.limit && this->speed.lookPointers <= this->speed.length) {
				f = applySpeed(k * this->speed.limit);
			}
		}

		if (this->speed.speeds[this->speed.pointer] == 0 && !this->speed.lookSemaphores.empty() && this->speed.lookSemaphores[0]->Position == SemaphorePosition::Reverse) {
			this->direction = this->direction == TrainDirection::Forward ? TrainDirection::Back : TrainDirection::Forward;
			this->SpeedReset();
		}

		this->speed.pointer = next(this->speed.pointer);
		this->speed.lookPointers--;
		return this->speed.speeds[this->speed.pointer];
	}
	
	int Train::next(int pointer)
	{
		return pointer == speed.length - 1 ? 0 : pointer + 1;
	}

	int Train::prev(int pointer)
	{		
		return pointer == 0 ? speed.length - 1 : pointer - 1;
	}

	void Train::SpeedReset()
	{
		speed.lookPointer = speed.pointer;
		speed.lookPointers = 0;

		//debugReset();

		speed.lookPosition = direction == TrainDirection::Forward ? Path::GetPosition(cars[0].Axis1, 2) : Path::GetPosition(cars[cars.size() - 1].Axis2, -2);

		//addDebugPoint();

		vector<Semaphore*>::iterator i;
		for (i = this->speed.lookSemaphores.begin(); i != this->speed.lookSemaphores.end(); ++i) {
			(*i)->remove(this);
		}
		this->speed.lookSemaphores.clear();
		this->speed.limit = this->speed.overLimit;		
		applySpeedLimit(this->speed.limit);
	}

	void Train::checkOverTrack()
	{
		int limit = speed.maxSpeed;		
		vector<Switch*> switches;
		int i = length;
		TrackPosition pos = direction == TrainDirection::Forward ? position : cars[cars.size() - 1].Axis2;
		Entry *entry;
		bool first = true;
		
		while (i > 0)
		{
			if (direction == TrainDirection::Forward) {
				entry = pos.cell->getEntry(pos.point);
				if (pos.indent - i >= 0) {
					pos.indent = pos.indent - i;
					i = 0;
					if (Path::track[entry->Element].SpeedLimit > 0 && Path::track[entry->Element].SpeedLimit < limit) {						
						limit = Path::track[entry->Element].SpeedLimit;
					}
 				}
				if (pos.indent - i < 0) {
					int nextPoint = Cell::Related[pos.point];

					if (pos.cell->switches[pos.point] > 0) {
						switches.push_back(pos.cell->switches[pos.point]);
					}
					if (pos.cell->switches[nextPoint] > 0) {
						switches.push_back(pos.cell->switches[nextPoint]);
					}
					if (first && pos.cell->semaphores[nextPoint] != 0 && pos.cell->semaphores[nextPoint]->Position == SemaphorePosition::Go) {
						pos.cell->semaphores[nextPoint]->remove(this);
						this->speed.lookSemaphores.erase(std::remove(this->speed.lookSemaphores.begin(), this->speed.lookSemaphores.end(), pos.cell->semaphores[nextPoint]), this->speed.lookSemaphores.end());
					}

					first = false;

					if (pos.cell->getEntry(nextPoint) != 0) {
						i = i - (pos.indent + 1);
						entry = pos.cell->getEntry(nextPoint);
						pos.cell = entry->to;
						pos.point = entry->Point;
						pos.indent = Path::track[entry->Element].items.size() - 1;
						if (Path::track[entry->Element].SpeedLimit > 0 && Path::track[entry->Element].SpeedLimit < limit) {
							limit = Path::track[entry->Element].SpeedLimit;
						}
					} else {
						pos.indent = 0;
						i = 0;
					}
				}
			}

			if (direction == TrainDirection::Back) {				
				entry = pos.cell->getEntry(pos.point);
				int TrackLength = Path::track[entry->Element].items.size();
				if (pos.indent + i < TrackLength) {
					pos.indent = pos.indent + i;
					i = 0;
					if (Path::track[entry->Element].SpeedLimit > 0 && Path::track[entry->Element].SpeedLimit < limit) {
						limit = Path::track[entry->Element].SpeedLimit;
					}
				}
				if (pos.indent + i >= TrackLength) {
					int nextPoint = Cell::Related[entry->Point];

					if (entry->to->switches[entry->Point] > 0) {
						switches.push_back(entry->to->switches[entry->Point]);
					}
					if (entry->to->switches[Cell::Related[entry->Point]] > 0) {
						switches.push_back(entry->to->switches[Cell::Related[entry->Point]]);
					}
					if (first && entry->to->semaphores[Cell::Related[entry->Point]] != 0 && entry->to->semaphores[Cell::Related[entry->Point]]->Position == SemaphorePosition::Go) {
						entry->to->semaphores[Cell::Related[entry->Point]]->remove(this);
						this->speed.lookSemaphores.erase(std::remove(this->speed.lookSemaphores.begin(), this->speed.lookSemaphores.end(), entry->to->semaphores[Cell::Related[entry->Point]]), this->speed.lookSemaphores.end());
					}

					first = false;

					if (entry->to->getEntry(nextPoint) != 0) {
						i = i - TrackLength + pos.indent - 1;
						pos.cell = entry->to;
						pos.indent = 0;
						pos.point = nextPoint;
						if (Path::track[entry->Element].SpeedLimit > 0 && Path::track[entry->Element].SpeedLimit < limit) {
							limit = Path::track[entry->Element].SpeedLimit;
						}
					} else {
						pos.indent = TrackLength - i;
						i = 0;
					}
				}
			}
		}

		speed.overLimit = limit;

		vector<Switch*>::iterator j;
		int k = 0;
		if (speed.overSwitches.empty()) {
			if (!switches.empty()) {
				for (j = switches.begin(); j < switches.end(); ++j)
				{
					speed.overSwitches.push_back(*j);
				}
			}
		} else {
			vector<Switch*>::iterator c = speed.overSwitches.begin();
			for (j = switches.begin(); j < switches.end(); ++j)
			{
				if (*j != *c) {
					speed.overSwitches.insert(c, *j);
				}
				k++;
				c = speed.overSwitches.begin() + k;
			}
			k = switches.size();
			while (k < speed.overSwitches.size())
			{
				c = speed.overSwitches.end() - 1;
				speed.overSwitches.pop_back();
			}
		}
	}

	bool Train::checkLookTrack(int move)
	{
		bool limitEvent = false;
		bool switchtEvent = false;
		bool semaphoreEvent = false;
		bool endEvent = false;
		int indent;
		int k = direction == TrainDirection::Forward ? 1 : -1;
		int speed = k * move;		
		vector<Switch*> switches;
		TrackPosition pos = this->speed.lookPosition;
		int i = move > 0 ? move : -move;
		Entry *entry;

		while (i > 0 && !(limitEvent || switchtEvent || semaphoreEvent || endEvent))
		{			
			if (direction == TrainDirection::Forward) {
				entry = pos.cell->getEntry(pos.point);
				int TrackLength = Path::track[entry->Element].items.size();
				if (pos.indent + i < TrackLength) {
					pos.indent = pos.indent + i;
					
					if (Path::track[entry->Element].SpeedLimit > 0 && Path::track[entry->Element].SpeedLimit < speed) {
						speed = Path::track[entry->Element].SpeedLimit;
						limitEvent = true;
						indent = move - i - 1;
						//addDebugPoint(Path::GetPosition(this->speed.lookPosition, k * indent));
					}
					i = 0;
				}
				if (pos.indent + i >= TrackLength) {
					int nextPoint = Cell::Related[entry->Point];
										
					if (pos.cell->switches[pos.point] > 0) {
						switches.push_back(pos.cell->switches[pos.point]);
					}
					if (pos.cell->switches[Cell::Related[pos.point]] > 0) {
						switches.push_back(pos.cell->switches[Cell::Related[pos.point]]);
					}

					if (entry->to->getEntry(nextPoint) != 0) {
						i = i - TrackLength + pos.indent;						
						pos.cell = entry->to;
						pos.indent = 0;
						pos.point = nextPoint;

						if (entry->to->semaphores[entry->Point] != 0) {
							entry->to->semaphores[entry->Point]->listen(this);
							this->speed.lookSemaphores.push_back(entry->to->semaphores[entry->Point]);
							if (entry->to->semaphores[entry->Point]->Position == SemaphorePosition::Stop || entry->to->semaphores[entry->Point]->Position == SemaphorePosition::Reverse) {
								semaphoreEvent = true;
								indent = move - i;
							}
						}

						if (Path::track[entry->Element].SpeedLimit > 0 && Path::track[entry->Element].SpeedLimit < speed) {
							speed = Path::track[entry->Element].SpeedLimit;
							limitEvent = true;
							indent = move - i;
							//addDebugPoint(Path::GetPosition(this->speed.lookPosition, k * indent));
						}

						if (i <= 0) {
							entry = pos.cell->getEntry(pos.point);
							if (Path::track[entry->Element].SpeedLimit > 0 && Path::track[entry->Element].SpeedLimit < speed) {
								speed = Path::track[entry->Element].SpeedLimit;
								limitEvent = true;
								indent = move + i;
								//addDebugPoint(Path::GetPosition(this->speed.lookPosition, k * indent));
							}
						}
					} else {						
						endEvent = true;
						indent = move - (i - TrackLength + pos.indent) - 1;
						i = 0;
					}
				}
			}

			if (direction == TrainDirection::Back) {
				entry = pos.cell->getEntry(pos.point);
				if (pos.indent - i >= 0) {
					pos.indent = pos.indent - i;
					i = 0;
				}
				if (pos.indent - i < 0) {
					int nextPoint = Cell::Related[pos.point];
					/*if (pos.cell->switches[pos.point] > 0) {
						switches.push_back(pos.cell->switches[pos.point]);
					}
					if (pos.cell->switches[nextPoint] > 0) {
						switches.push_back(pos.cell->switches[nextPoint]);
					}*/

					if (pos.cell->getEntry(nextPoint) != 0) {
						i = i - (pos.indent + 1);

						if (pos.cell->semaphores[pos.point] != 0) {
							pos.cell->semaphores[pos.point]->listen(this);
							this->speed.lookSemaphores.push_back(pos.cell->semaphores[pos.point]);
							if (pos.cell->semaphores[pos.point]->Position == SemaphorePosition::Stop || pos.cell->semaphores[pos.point]->Position == SemaphorePosition::Reverse) {
								semaphoreEvent = true;
								indent = - (move + i) - 1;
							}
						}

						entry = pos.cell->getEntry(nextPoint);
						pos.cell = entry->to;
						pos.point = entry->Point;
						pos.indent = Path::track[entry->Element].items.size() - 1;

						if (Path::track[entry->Element].SpeedLimit > 0 && Path::track[entry->Element].SpeedLimit < speed) {
							speed = Path::track[entry->Element].SpeedLimit;
							limitEvent = true;
							indent = - (move + i) - 1;							
							//addDebugPoint(Path::GetPosition(this->speed.lookPosition, k * indent));
						}
					} else {
						endEvent = true;
						i = i - (pos.indent + 1);
						indent = -(move + i) - 1;
						//pos.indent = 0;
						i = 0;
					}
				}
			}
		}

		if (semaphoreEvent || endEvent || switchtEvent) {
			slowDown(0, indent);
		} else if (limitEvent) {
			//limitEvent = false;
			slowDown(k * speed, indent);
		}

		bool f = limitEvent || switchtEvent || semaphoreEvent || endEvent;
		if (!f) {
			this->speed.lookPosition = pos;
			// debug
			//addDebugPoint();
		}
		return !f;
	}
	
	void Train::applySpeedLimit(int limit)
	{
		int k = direction == TrainDirection::Forward ? 1 : -1;
		int Speed = k * this->speed.speeds[this->speed.pointer];
		
		bool f = true;
		if (Speed != limit) {
			if (limit - Speed  > 0) {
				//speed up
				while (limit > Speed && f) {
					if (Speed + acceleration > limit) {
						Speed = limit;
					} else {
						Speed += acceleration;
					}
					if (!applySpeed(k * Speed)) {
						f = false;
					}
				}
			} else {
				//slow down
				while (limit < Speed && f) {
					if (Speed - acceleration < limit) {
						Speed = limit;
					} else {
						Speed -= acceleration;
					}

					if (!applySpeed(k * Speed)) {
						f = false;
					}
				}
			}
		}		
	}

	bool Train::applySpeed(int Speed)
	{
		bool f = checkLookTrack(Speed);		
		if (f) {
			this->speed.lookPointer = next(this->speed.lookPointer);
			this->speed.lookPointers++;
			this->speed.speeds[this->speed.lookPointer] = Speed;
		}
		return f;
	}
	
	void Train::slowDown(int Speed, int Indent)
	{
		int k = direction == TrainDirection::Forward ? 1 : -1;
		Speed *= k;
		int lookPointer = this->speed.lookPointer;
		int lookPointers = this->speed.lookPointers;
		int prev = k * this->speed.speeds[lookPointer];				
		int next = Speed;

		vector<int> items;
		int p = prev;
		items.push_back(k * next);

		if (Indent > 0) {
			p = Indent;
			while (p > 0) {
				next += acceleration;
				items.push_back(k * next);
				p -= next;
			}
			p = prev + p;
		}

		while (prev - next > acceleration) {
			while (p > 0) {
				next += acceleration;
				items.push_back(k * next);
				p -= next;
			}
			lookPointer = this->prev(lookPointer);
			lookPointers--;
			prev = k * this->speed.speeds[lookPointer];
			p += prev;
		}

		if (lookPointers >= 0) {
			if (p > 0 && prev == p) {
				items.push_back(k * next);
				p = 0;
			}
			lookPointers--;
			this->speed.lookPointers = lookPointers;
			lookPointer = this->prev(lookPointer);
		} else {
			this->speed.lookPointers = 0;
			lookPointer = this->speed.pointer;
		}

		vector<int>::reverse_iterator c;
		for (c = items.rbegin(); c < items.rend(); ++c) {
			if (p > 0 && (k * *c <= p && k * *c + acceleration > p) ) {
				lookPointer = this->next(lookPointer);
				lookPointers++;
				this->speed.speeds[lookPointer] = k * p;
				p = 0;
			}
			lookPointer = this->next(lookPointer);
			lookPointers++;
			this->speed.speeds[lookPointer] = *c;
		}

		this->speed.lookPointer = lookPointer;
		this->speed.lookPointers = lookPointers;
		this->speed.limit = Speed;
		this->speed.lookPosition = Path::GetPosition(this->speed.lookPosition, k * (Indent + Speed - p));
		
		// debug
		//addDebugPoint();
	}
	
	/* debug */
	/*int Train::nextDebug(int pointer)
	{
		return pointer == 20 - 1 ? 0 : pointer + 1;
	}

	int Train::prevDebug(int pointer)
	{
		return pointer == 0 ? 20 - 1 : pointer - 1;
	}

	void Train::addDebugPoint() {
		debugPointer = nextDebug(debugPointer);
		debugNode->drawDot(debugItems[debugPointer], 2.0, Color4F::WHITE);
		debugItems[debugPointer] = Path::GetPosition(this->speed.lookPosition);
		debugNode->drawDot(debugItems[debugPointer], 2.0, Color4F::BLUE);
	}

	void Train::addDebugPoint(TrackPosition pos) {
		debugPointer = nextDebug(debugPointer);
		debugNode->drawDot(debugItems[debugPointer], 3.0, Color4F::RED);
		debugItems[debugPointer] = Path::GetPosition(pos);
		debugNode->drawDot(debugItems[debugPointer], 3.0, Color4F::RED);
	}

	void Train::debugReset() {
		for (int i = 0; i < 20; i++) {
			debugNode->drawDot(debugItems[i], 2.0, Color4F::WHITE);
		}
	}*/
}
