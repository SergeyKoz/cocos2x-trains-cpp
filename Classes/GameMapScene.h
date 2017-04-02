#ifndef __GAMEMAP_SCENE_H__
#define __GAMEMAP_SCENE_H__

#include "cocos2d.h"

#include "MapBackgroundLayer.h"
#include "MapTrainsLayer.h"
#include "GameMapLayer.h"

class GameMapScene 
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
};

#endif // __GAMEMAP_SCENE_H__
