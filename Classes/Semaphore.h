#ifndef __GAME_SEMAPHORE_H__
#define __GAME_SEMAPHORE_H__

#include "cocos2d.h"

using namespace std;

namespace GameObjects {

	class Train;

	enum SemaphorePosition
	{
		Go = 0,
		Reverse = 1,
		Stop = 2,
	};
	
	struct ShowItem {
		MapPoint point;
		int enter;
		SemaphorElement elementType;
		Sprite *element;
	};

	struct SemaphoreResources {		
		Sprite *go;
		Sprite *reverse;
		Sprite *stop;
	};

	class Semaphore
	{

	public:
		Semaphore();
		Semaphore(Cell *cell, int Point);
		~Semaphore();

		bool Show(MapPoint Point, MapIndent Indent);
		void Hide();
		void Set();
		bool AllowedPoint(Cell *cell, int Point);

		ShowItem showItem;
		static const SemaphorePosition defaultProgram[24][12];
		SemaphorePosition program[24][12];
		//int program[24][12];
		SemaphorePosition Position;
		Cell *cell;
		SemaphoreResources Resources;

		void Next();
		void setPosition(SemaphorePosition pos);
		void setProgram(int program[24][12]);
		void resetProgram();

		vector<Train*> trains;
		void listen(Train *train);
		void remove(Train *train);

		void remove();
	private:
		EventListenerTouchOneByOne *listener;
	};
}

#endif /*__GAME_SEMAPHORE_H__*/

