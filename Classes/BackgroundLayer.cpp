#include "BackgroundLayer.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool BackgroundLayer::init()
{  
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
	LayerColor *bg = LayerColor::create(Color4B(255, 255, 255, 255));
	this->addChild(bg);
	
    return true;
}

