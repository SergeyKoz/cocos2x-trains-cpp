#include "Car.h"
#include "Path.h"
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
}
