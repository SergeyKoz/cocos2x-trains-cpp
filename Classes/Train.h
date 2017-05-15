#ifndef __GAME_TRAIN_H__
#define __GAME_TRAIN_H__

#include "Elements.h"
#include "Car.h"

//#include <map>
//using namespace std;

namespace GameObjects {

	enum TrainDirection {
		Forward = 1,
		Back = 2
	};

	/*struct TrackPosition {
		Cell *cell;
		int point;
		int indent;
	};*/

	class Train
	{
	public:
		Train();
		~Train();

		void AddCar(Car *car);

		void Init();
		void Move();

		TrainDirection direction;
		vector<Car> cars;

		TrackPosition position;

		void SetPosition(TrackPosition position);
		int GetSpeed();
		void GetMove(int move);
		void RunMove();
		void SpeedProgramReset();
	};
}
#endif /*__GAME_TRAIN_H__*/
