#include "cocos2d.h"
#include <math.h>
#include "GameObjects.h"

using namespace GameObjects;

USING_NS_CC;

class TrainsLayer : public cocos2d::Layer
{	
public:   
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
	virtual void onEnter();

	void trainsMoveCallback(float dt);

	TrainCollision collision;
	
    // implement the "static create()" method manually
	CREATE_FUNC(TrainsLayer);
private:
	bool onContactBegin(PhysicsContact &contact);
};
