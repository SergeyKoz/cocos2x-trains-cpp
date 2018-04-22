#ifndef __GAME_CAR_H__
#define __GAME_CAR_H__

#include "Elements.h"

namespace GameObjects {

	class Train;

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
		void initContactSystem(int bitmask);

		void GetMove(int speed);
		void RunMove();
		void remove();

		TrackPosition Axis1;
		TrackPosition Axis2;

		static const CarSettings settings[6];

		CarElement type;
		CarPosition position;
		CarPosition move;
		CarPosition shift;
		Sprite *resource;
	private:
		PhysicsBody *physicsBody;
	};
}
#endif /*__GAME_CAR_H__*/
