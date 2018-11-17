#include "MenuLayer.h"

USING_NS_CC;

bool MenuLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Vector<cocos2d::MenuItem*> items;

	this->TasksButton = new GameObjects::MenuItem(items, pos({ -1, -1 }), Elements::GetMenuElement(MenuElement::TasksButton), CC_CALLBACK_1(MenuLayer::menuDefaultCallback, this), true, true);
	this->ZoomInButton = new GameObjects::MenuItem(items, pos({ -1, -3 }), Elements::GetMenuElement(MenuElement::ZoomInButton), CC_CALLBACK_1(MenuLayer::menuDefaultCallback, this), true, true);
	this->ZoomOutButton = new GameObjects::MenuItem(items, pos({ -1, -5 }), Elements::GetMenuElement(MenuElement::ZoomOutButton), CC_CALLBACK_1(MenuLayer::menuDefaultCallback, this), true, true);
	this->UndoButton = new GameObjects::MenuItem(items, pos({ -5, -1 }), Elements::GetMenuElement(MenuElement::UndoButton), CC_CALLBACK_1(MenuLayer::menuUndoButtonCallback, this), false, true);
	this->RedoButton = new GameObjects::MenuItem(items, pos({ -3, -1 }), Elements::GetMenuElement(MenuElement::RedoButton), CC_CALLBACK_1(MenuLayer::menuRedoButtonCallback, this), false, true);
	this->RailsButton = new GameObjects::MenuItem(items, pos({ -13, -1 }), { Elements::GetMenuElement(MenuElement::RailsButton), Elements::GetMenuElement(MenuElement::RailsButtonChecked) }, CC_CALLBACK_1(MenuLayer::menuRailsButtonCallback, this), true, true, false);
	this->SemaforesButton = new GameObjects::MenuItem(items, pos({ -11, -1 }), { Elements::GetMenuElement(MenuElement::SemaforesButton), Elements::GetMenuElement(MenuElement::SemaforesButtonChecked) }, CC_CALLBACK_1(MenuLayer::menuSemaforesButtonCallback, this), true, true, false);
	this->StartButton = new GameObjects::MenuItem(items, pos({ -23, -1 }), Elements::GetMenuElement(MenuElement::StartButton), CC_CALLBACK_1(MenuLayer::menuStartButtonCallback, this), true, true);
	this->PauseButton = new GameObjects::MenuItem(items, pos({ -23, -1 }), Elements::GetMenuElement(MenuElement::PauseButton), CC_CALLBACK_1(MenuLayer::menuPauseButtonCallback, this), true, false);
	this->StopButton = new GameObjects::MenuItem(items, pos({ -21, -1 }), Elements::GetMenuElement(MenuElement::StopButton), CC_CALLBACK_1(MenuLayer::menuDefaultCallback, this), true, false);
	this->FastButton = new GameObjects::MenuItem(items, pos({ -19, -1 }), Elements::GetMenuElement(MenuElement::FastButton), CC_CALLBACK_1(MenuLayer::menuDefaultCallback, this), true, false);

	auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(MenuLayer::menuCloseCallback, this));
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2, origin.y + closeItem->getContentSize().height / 2));
	items.pushBack(closeItem);

	auto menu = Menu::createWithArray(items);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	auto label = Label::createWithTTF("My Trains", "fonts/Marker Felt.ttf", 16);
	// position the label on the center of the screen
	/*label->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - label->getContentSize().height));*/
	label->setPosition(Vec2(origin.x + label->getContentSize().width, origin.y + label->getContentSize().height));
	label->setColor(Color3B::BLACK);
	// add the label as a child to this layer
	this->addChild(label, ZIndexMenu);

	return true;
}

MapPoint MenuLayer::pos(MapPoint Point)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	int d = 10 * Field::getInstance()->scale;
	return { (int)(visibleSize.width + Point.x * d) , (int)(visibleSize.height + Point.y * d) };
}

void MenuLayer::menuDefaultCallback(Ref* pSender)
{
	/*Cmd::Exec("station --add --id=1 --cell={\"x\":20,\"y\":2} --angle=0");
	Cmd::Exec("station --add --id=2 --cell={\"x\":20,\"y\":2} --angle=90");
	Cmd::Exec("station --add --id=3 --cell={\"x\":20,\"y\":2} --angle=180");
	Cmd::Exec("station --add --id=4 --cell={\"x\":20,\"y\":2} --angle=270");*/
}

void MenuLayer::menuRailsButtonCallback(Ref* pSender)
{
	Field *game = Field::getInstance();
	if (!this->RailsButton->checked) {
		this->RailsButton->check(true);
		this->SemaforesButton->check(false);
		game->constuctionMode = ConstructRails;
	} else {
		this->RailsButton->check(false);
		game->constuctionMode = ConstructNone;
	}

	setElementsAccess();
}

void MenuLayer::menuSemaforesButtonCallback(Ref* pSender)
{
	Field *game = Field::getInstance();

	if (!this->SemaforesButton->checked) {
		this->SemaforesButton->check(true);
		this->RailsButton->check(false);
		game->constuctionMode = ConstructSemafores;
	} else {
		this->SemaforesButton->check(false);
		game->constuctionMode = ConstructNone;
	}

	setElementsAccess();	
}

void MenuLayer::menuUndoButtonCallback(Ref* pSender)
{
	Cmd::Undo();
}

void MenuLayer::menuRedoButtonCallback(Ref* pSender)
{
	Cmd::Redo();
}

void MenuLayer::menuStartButtonCallback(Ref* pSender)
{
	Field::getInstance()->gameMode = GameMode::ModeOn;	
	this->StartButton->show(false);
	this->PauseButton->show(true);
}

void MenuLayer::menuPauseButtonCallback(Ref* pSender)
{
	Field::getInstance()->gameMode = GameMode::ModeOff;	
	this->StartButton->show(true);
	this->PauseButton->show(false);
}

void MenuLayer::setElementsAccess()
{
	Field *game = Field::getInstance();
	EventDispatcher *eventDispatcher = Director::getInstance()->getEventDispatcher();
	for (int x = 0; x < game->SizeX; x++) {
		for (int y = 0; y < game->SizeY; y++) {
			if (game->cells[x][y].configuration != None) {
				for (int i = 0; i < 8; i++)
				{
					if (game->cells[x][y].semaphores[i] > 0) {
						if (game->constuctionMode == ConstructNone) {
							eventDispatcher->resumeEventListenersForTarget(game->cells[x][y].semaphores[i]->Resources.go);
						} else {
							eventDispatcher->pauseEventListenersForTarget(game->cells[x][y].semaphores[i]->Resources.go);
						}
					}

					if (game->cells[x][y].switches[i] > 0) {
						if (game->constuctionMode == ConstructNone) {
							eventDispatcher->resumeEventListenersForTarget(game->cells[x][y].switches[i]->positions[SwitchPosition::Straight]->element);
						} else {
							eventDispatcher->pauseEventListenersForTarget(game->cells[x][y].switches[i]->positions[SwitchPosition::Straight]->element);
						}
					}
				}
			}
		}
	}
}

void MenuLayer::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);
}
