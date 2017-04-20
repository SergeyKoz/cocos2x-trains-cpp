#include "cocos2d.h"
#include "GameObjects.h"

USING_NS_CC;
using namespace GameObjects;

class MenuLayer : public cocos2d::Layer
{
public:
	virtual bool init();
		
	void menuDefaultCallback(cocos2d::Ref* pSender);
	void menuRailsButtonCallback(cocos2d::Ref* pSender);
	void menuSemaforesButtonCallback(Ref* pSender);

	void menuCloseCallback(cocos2d::Ref* pSender);

	GameObjects::MenuItem *TasksButton;
	GameObjects::MenuItem *ZoomInButton;
	GameObjects::MenuItem *ZoomOutButton;
	GameObjects::MenuItem *UndoButton;
	GameObjects::MenuItem *RedoButton;
	GameObjects::MenuItem *RailsButton;
	GameObjects::MenuItem *SemaforesButton;
	GameObjects::MenuItem *StartButton;
	GameObjects::MenuItem *PauseButton;
	GameObjects::MenuItem *StopButton;
	GameObjects::MenuItem *FastButton;

	MapPoint pos(MapPoint Point);

	CREATE_FUNC(MenuLayer);
};

