#include "cocos2d.h"
#include "GameObjects.h"

using namespace GameObjects;

class MapLayer : public cocos2d::Layer
{
public:
   
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
	virtual void onEnter();
		
 	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchMoved(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);

    // implement the "static create()" method manually
	CREATE_FUNC(MapLayer);

	TouchMode touchMode = Move;
	Vec2 startLocation = { -1, -1 };

	Path path;
	Semaphore semaphore;

	//vector<Sprite> backGround;

	//Node* pin;

	vector<Sprite*> **sectors;
		
	void renderMap();
	void showMap();
	void renderMapSector(int x, int y);
	void onRenderMapEnd();

	int getStartPoint(MapPoint c, Vec2 d);

	void testNet();
	void testNetSector(int x, int y);

	string p(int p, int d);
};
