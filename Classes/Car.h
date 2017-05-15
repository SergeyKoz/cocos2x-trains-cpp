#ifndef __GAME_CAR_H__
#define __GAME_CAR_H__

#include "Elements.h"

namespace GameObjects {

	/*enum CarTypes {
		Locomotive = 1,
		TankCar = 2,
		PassengerCar = 3,
		FreightCar = 4,
		Switcher = 5,
	};*/

	struct CarSettings {
		int base;
		int traction;
	};

	struct CarPosition {
		Vec2 p;
		float a;
	};

	class Car
	{
	public:
		Car();
		Car(CarElement type);
		~Car();

		TrackPosition SetPosition(TrackPosition position);

		TrackPosition Axis1;
		TrackPosition Axis2;

		static const CarSettings settings[6];

		CarElement type;
		CarPosition position;
		Sprite *resource;
	};
}
#endif /*__GAME_CAR_H__*/

