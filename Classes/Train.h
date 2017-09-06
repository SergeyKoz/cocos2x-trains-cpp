#ifndef __GAME_TRAIN_H__
#define __GAME_TRAIN_H__

#include "Elements.h"
#include "Car.h"
#include "Switch.h"
#include "Semaphore.h"
#include "cocos2d.h"

namespace GameObjects {

	class Semaphore;
	class Switch;

	enum TrainDirection {
		Forward = 1,
		Back = 2
	};

	struct SpeedProgram {
		int *speeds = 0;
		int length = 0;
		int pointer = 0;
		int lookPointer = 0;
		int lookPointers = 0;
		//int lookLength = 0;
		int limit = 0;
		int overLimit = 0;
		int maxSpeed = 0;
		TrackPosition lookPosition;
		vector<Semaphore*> lookSemaphores;
		vector<Switch*> lookSwitches;
		vector<Switch*> overSwitches;
	};

	class Train
	{
	public:
		Train();
		~Train();

		void AddCar(Car *car);

		void init();
		void move();

		int next(int pointer);
		int prev(int pointer);
		
		TrainDirection direction;
		vector<Car> cars;

		int acceleration = 2;
		int length = 0; //length of the train

		TrackPosition position;
		SpeedProgram speed;
		Label *label;

		void SetPosition(TrackPosition position);
		int GetSpeed();
		void GetMove(int move);
		void RunMove();
		void SpeedReset();

		void checkOverTrack();
		bool checkLookTrack(int move);
		bool applySpeed(int Speed);
		void applySpeedLimit(int limit);

		void slowDown(int Speed, int Indent);

		/* debug */
		/*DrawNode *debugNode;
		Vec2 debugItems[20];
		int debugPointer = 0;
		int nextDebug(int pointer);
		int prevDebug(int pointer);
		void addDebugPoint();
		void addDebugPoint(TrackPosition pos);
		void debugReset();*/
	};
}
#endif /*__GAME_TRAIN_H__*/
