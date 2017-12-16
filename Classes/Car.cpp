#include "Car.h"
#include "Path.h"
#include "MapLAyer.h"
#include <math.h>

#define PI 3.14159265358979323846f
#define hPI PI / 2
#define Deg 180.0f / PI

namespace GameObjects {

	const CarSettings Car::settings[6] = { { 0, 0 } , { 16, 5 }, { 16, 0 }, { 16, 0 }, { 16, 0 }, { 12, 3 } };

	Car::Car()
	{
	}

	Car::Car(CarElement type)
	{
		this->type = type;
		this->resource = Elements::GetCarElement(this->type);
		this->resource->setVisible(false);

		Size size = this->resource->getContentSize();

		int k = Field::getInstance()->scale;

		size.height -= 2 * k;
		size.width -= 2 * k;

		
		auto physicsBody = PhysicsBody::createBox(size, PhysicsMaterial());
		//physicsBody->setMass(MASS_DEFAULT);
		//physicsBody->setVelocityLimit(PHYSICS_INFINITY);

		physicsBody->setDynamic(true);
		physicsBody->setGravityEnable(false);
		
		this->resource->setPhysicsBody(physicsBody);
		Field::getInstance()->trainsLayer->addChild(this->resource, ZIndexTrains);
	}

	Car::~Car()
	{
	}

	TrackPosition Car::SetPosition(TrackPosition position) {		
		Axis1 = position;
		Vec2 p1 = Path::GetPosition(Axis1);		
		Axis2 = Path::GetPosition(Axis1, -settings[type].base);
		Vec2 p2 = Path::GetPosition(Axis2);
		this->position = { { (p1.x + (p2.x - p1.x) / 2), (p1.y + (p2.y - p1.y) / 2) }, (atan2((p2.x - p1.x), (p2.y - p1.y)) + hPI) * Deg };
		this->resource->setPosition(this->position.p);
		this->resource->setRotation(this->position.a);			
		return Path::GetPosition(Axis2, -4);		
	}

	void Car::GetMove(int speed)
	{
		//move
		Axis1 = Path::GetPosition(Axis1, speed);		
		Vec2 p1 = Path::GetPosition(Axis1);
		Axis2 = Path::GetPosition(Axis2, speed);		
		Vec2 p2 = Path::GetPosition(Axis2);
		this->move = { { (p1.x + (p2.x - p1.x) / 2), (p1.y + (p2.y - p1.y) / 2) }, (atan2((p2.x - p1.x), (p2.y - p1.y)) + hPI) * Deg };

		/*TrackPosition pos = Path::GetPosition(Axis1, speed);
		Axis1 = pos;
		Vec2 p1 = Path::GetPosition(pos);
		pos = Path::GetPosition(Axis2, speed);
		Axis2 = pos;
		Vec2 p2 = Path::GetPosition(pos);*/
		//CarPosition move = { { (p1.x + (p2.x - p1.x) / 2), (p1.y + (p2.y - p1.y) / 2) }, (atan2((p2.x - p1.x), (p2.y - p1.y)) + hPI) * Deg };
		//this->shift = { move.p - this->position.p, move.a - this->position.a };
		//this->move = move;		
	}

	void Car::RunMove()
	{
		Rect box = Field::getInstance()->mapLayer->getBoundingBox();
		if (box.containsPoint(2 * box.origin + this->move.p)) {
			this->resource->runAction(MoveTo::create(0.2f, this->move.p));
			this->resource->runAction(RotateTo::create(0.2f, this->move.a));
		} else {
			this->resource->setPosition(this->move.p);
			this->resource->setRotation(this->move.a);
		}	
	}
}
