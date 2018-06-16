#include "Train.h"
#include "Car.h"
#include "Path.h"
#include <math.h>
//#include <thread>

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
		car.initContactSystem(id);

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

		GetMove(GetSpeed());
		
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

		/*std::thread t([&] {
			GetMove(GetSpeed());
		});
		t.detach();*/



		Director::getInstance()->getScheduler()->performFunctionInCocosThread([&] {
			GetMove(GetSpeed());			
		});
		
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
		//debug
		//debugReset();

		speed.lookPosition = direction == TrainDirection::Forward ? Path::GetPosition(cars[0].Axis1, 2) : Path::GetPosition(cars[cars.size() - 1].Axis2, -2);
		//debug
		//addDebugPoint();

		vector<Semaphore*>::iterator i;
		for (i = this->speed.lookSemaphores.begin(); i != this->speed.lookSemaphores.end(); ++i) {
			(*i)->remove(this);
		}
		this->speed.lookSemaphores.clear();

		vector<Switch*>::iterator c;
		for (c = this->speed.lookSwitches.begin(); c != this->speed.lookSwitches.end(); ++c) {
			(*c)->removeLook(this);
		}
		this->speed.lookSwitches.clear();

		vector<Switch*>::iterator j;
		for (j = this->speed.overSwitches.begin(); j != this->speed.overSwitches.end(); ++j) {
			(*j)->removeOver(this);
		}
		this->speed.overSwitches.clear();

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

		if (direction == TrainDirection::Back) {
			pos = Path::backPosition(pos);
		}
		
		while (i > 0)
		{
			entry = pos.cell->getEntry(pos.point, pos.element);
			if (pos.indent - i >= 0) {
				pos.indent = pos.indent - i;
				i = 0;
				if (Path::track[entry->Element].SpeedLimit > 0 && Path::track[entry->Element].SpeedLimit < limit) {						
					limit = Path::track[entry->Element].SpeedLimit;
				}
 			}
			if (pos.indent - i < 0) {
				int nextPoint = Cell::Related[pos.point];
				//switches
				if (pos.cell->switches[pos.point] > 0) {
					switches.push_back(pos.cell->switches[pos.point]);
				}
				if (pos.cell->switches[nextPoint] > 0) {
					switches.push_back(pos.cell->switches[nextPoint]);
				}
				//semaphores
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
					pos.indent = Path::track[entry->Element].length - 1;
					pos.element = entry->Element;
					if (Path::track[entry->Element].SpeedLimit > 0 && Path::track[entry->Element].SpeedLimit < limit) {
						limit = Path::track[entry->Element].SpeedLimit;
					}
				} else {
					pos.indent = 0;
					i = 0;
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
					(*j)->listenOver(this);
					(*j)->removeLook(this);
					speed.lookSwitches.erase(std::remove(speed.lookSwitches.begin(), speed.lookSwitches.end(), (*j)), speed.lookSwitches.end());
				}
			}
		} else {
			vector<Switch*>::iterator c = speed.overSwitches.begin();
			for (j = switches.begin(); j < switches.end(); ++j)
			{
				if (*j != *c) {
					speed.overSwitches.insert(c, *j);
					(*j)->listenOver(this);
					(*j)->removeLook(this);
					speed.lookSwitches.erase(std::remove(speed.lookSwitches.begin(), speed.lookSwitches.end(), (*j)), speed.lookSwitches.end());
				}
				k++;
				c = speed.overSwitches.begin() + k;
			}
			k = switches.size();
			while (k < speed.overSwitches.size())
			{
				c = speed.overSwitches.end() - 1;
				speed.overSwitches.back()->removeOver(this);
				speed.overSwitches.pop_back();
			}
		}
	}

	bool Train::checkLookTrack(int move)
	{
		Entry *entry, *nextEntry, *_entry;

		bool limitEvent = false;
		bool switchtEvent = false;
		bool semaphoreEvent = false;
		bool endEvent = false;
		int indent = 0;
		int k = direction == TrainDirection::Forward ? 1 : -1;
		int speed = k * move;		
		int i = move > 0 ? move : -move;
		move = speed;

		TrackPosition pos = this->speed.lookPosition;

		if (direction == TrainDirection::Back) {
			pos = Path::backPosition(pos);
		} 
				
		while (i > 0 && !(semaphoreEvent || endEvent || switchtEvent))
		{
			entry = pos.cell->getEntry(pos.point, pos.element);
			TrackItem track = Path::track[entry->Element];
			if (pos.indent + i < track.length) {
				pos.indent = pos.indent + i;
				if (track.SpeedLimit > 0 && track.SpeedLimit < speed) {
					speed = track.SpeedLimit;
					limitEvent = true;
					indent = move - i;
						
					//debug
					//addDebugPoint(Path::GetPosition(this->speed.lookPosition, indent));
				}

				//in switch
				if (entry->to->getEntry(Cell::Related[entry->Point]) != 0) {
					_entry = entry->to->getEntry(Cell::Related[entry->Point]);
					if ((_entry->Element == TrackElement::Horizontal || _entry->Element == TrackElement::Vertical) && _entry->to->getEntry(Cell::Related[_entry->Point]) != 0) {
						_entry = _entry->to->getEntry(Cell::Related[_entry->Point]);
						if ((_entry->Element == TrackElement::Horizontal || _entry->Element == TrackElement::Vertical) && _entry->to->switches[_entry->Point] > 0) {							
							this->speed.lookSwitches.push_back(_entry->to->switches[_entry->Point]);
							_entry->to->switches[_entry->Point]->listenLook(this);
							if (_entry->Element != _entry->to->getEntry(_entry->Point)->Element)
							{
								//closed
								switchtEvent = true;
								indent = move - i + Path::track[entry->Element].length - 5;
							}
						}
					}

					if (_entry->Element == TrackElement::Item135 || _entry->Element == TrackElement::Item45) {
						if (!switchtEvent && _entry->to->switches[_entry->Point] > 0) {
							this->speed.lookSwitches.push_back(_entry->to->switches[_entry->Point]);
							_entry->to->switches[_entry->Point]->listenLook(this);
							if (_entry->Element != _entry->to->getEntry(_entry->Point)->Element)
							{
								//closed
								switchtEvent = true;
								indent = move - i + Path::track[entry->Element].length - 5;
							}
						}
					}
				}

				if (!switchtEvent && entry->to->switches[entry->Point] > 0) {
					this->speed.lookSwitches.push_back(entry->to->switches[entry->Point]);
					entry->to->switches[entry->Point]->listenLook(this);
					if (entry->Element != entry->to->getEntry(entry->Point)->Element)
					{
						//closed
						switchtEvent = true;
						switch (entry->Element)
						{
						case TrackElement::BaseCircleSect0: case TrackElement::BaseCircleSect1: case TrackElement::BaseCircleSect2: case TrackElement::BaseCircleSect3: case TrackElement::BaseCircleSect4: case TrackElement::BaseCircleSect5: case TrackElement::BaseCircleSect6: case TrackElement::BaseCircleSect7:
							indent = move - i + Path::track[entry->Element].length - 25;
							break;
						default:
							indent = move - i + Path::track[entry->Element].length - 15;
							break;
						}
					}
				}
				i = 0;
			}
			if (pos.indent + i >= track.length) {
				int nextPoint = Cell::Related[entry->Point];
				if (entry->to->getEntry(nextPoint) != 0) {
					i = i - track.length + pos.indent;

					pos.cell = entry->to;
					pos.indent = 0;
					pos.point = nextPoint;
					pos.element = entry->to->getEntry(nextPoint)->Element;

					//in switch
					
					if (entry->to->getEntry(Cell::Related[entry->Point]) != 0) {
						_entry = entry->to->getEntry(Cell::Related[entry->Point]);
						if ((_entry->Element == TrackElement::Horizontal || _entry->Element == TrackElement::Vertical) && _entry->to->getEntry(Cell::Related[_entry->Point]) != 0) {
							_entry = _entry->to->getEntry(Cell::Related[_entry->Point]);
							if ((_entry->Element == TrackElement::Horizontal || _entry->Element == TrackElement::Vertical) && _entry->to->switches[_entry->Point] > 0) {
								this->speed.lookSwitches.push_back(_entry->to->switches[_entry->Point]);
								_entry->to->switches[_entry->Point]->listenLook(this);
								if (_entry->Element != _entry->to->getEntry(_entry->Point)->Element)
								{
									//closed
									switchtEvent = true;
									indent = move - i + Path::track[entry->Element].length - 5;
									i = 0;
								}
							}							
						}

						if ((_entry->Element == TrackElement::Item135 || _entry->Element == TrackElement::Item45) && !switchtEvent && _entry->to->switches[_entry->Point] > 0) {
							this->speed.lookSwitches.push_back(_entry->to->switches[_entry->Point]);
							_entry->to->switches[_entry->Point]->listenLook(this);
							if (_entry->Element != _entry->to->getEntry(_entry->Point)->Element)
							{
								//closed
								switchtEvent = true;
								indent = move - i + Path::track[entry->Element].length - 5;
								i = 0;
							}														
						}
					}
					
					if (!switchtEvent && entry->to->switches[entry->Point] > 0) {
						this->speed.lookSwitches.push_back(entry->to->switches[entry->Point]);
						entry->to->switches[entry->Point]->listenLook(this);
						if (entry->Element != entry->to->getEntry(entry->Point)->Element)
						{
							//closed
							switchtEvent = true;								
							switch (entry->Element)
							{							
							case TrackElement::BaseCircleSect0: case TrackElement::BaseCircleSect1: case TrackElement::BaseCircleSect2: case TrackElement::BaseCircleSect3: case TrackElement::BaseCircleSect4: case TrackElement::BaseCircleSect5: case TrackElement::BaseCircleSect6: case TrackElement::BaseCircleSect7:
								indent = move - i + Path::track[entry->Element].length - 25;
								break;
							default:
								indent = move - i + Path::track[entry->Element].length - 15;
								break;
							}
							i = 0;
						}
					}

					//out switch
					if (pos.cell->switches[pos.point] > 0) {
						this->speed.lookSwitches.push_back(pos.cell->switches[pos.point]);
						pos.cell->switches[pos.point]->listenLook(this);
					}

					//in semaphore
					if (pos.cell->semaphores[entry->Point] != 0) {
						pos.cell->semaphores[entry->Point]->listen(this);
						this->speed.lookSemaphores.push_back(pos.cell->semaphores[entry->Point]);
						if (pos.cell->semaphores[entry->Point]->Position == SemaphorePosition::Stop || pos.cell->semaphores[entry->Point]->Position == SemaphorePosition::Reverse) {
							semaphoreEvent = true;

							indent = move - i;
						}
					}

					if (track.SpeedLimit > 0 && track.SpeedLimit < speed) {
						speed = track.SpeedLimit;
						limitEvent = true;
							
						indent = move - i;

						//debug
						//addDebugPoint(Path::GetPosition(this->speed.lookPosition, indent));
					}
				} else {						
					endEvent = true;
					indent = move - (i - track.length + pos.indent) - 1;
					i = 0;
				}
			}			
		}

		if (semaphoreEvent || endEvent || switchtEvent) {
			slowDown(0, indent);
		} else if (limitEvent) {
			slowDown(k * speed, indent);
		}

		bool f = limitEvent || semaphoreEvent || endEvent || switchtEvent;
		if (!f) {
			if (direction == TrainDirection::Back) {
				pos = Path::backPosition(pos);
			}
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
	}
	*/
}
