#include "SettingScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace cocos2d::ui;

Scene* SettingScene::createScene()
{
	auto scene = Scene::create();

	auto layer = SettingScene::create();

	scene->addChild(layer);

	return scene;
}

bool SettingScene::init()
{

	if (!Layer::init())
	{
		return false;
	}

	auto rootNode = CSLoader::createNode("Start\\SettingScene.csb");

	addChild(rootNode);

	auto click_Back = MenuItemImage::create("Start\\back.png", "Start\\back_2.png", CC_CALLBACK_0(SettingScene::back, this));
	auto menu_Back = Menu::create(click_Back, 0);
	menu_Back->setPosition(903,48);
	this->addChild(menu_Back);

	auto keyboard = EventListenerKeyboard::create();

	keyboard->onKeyPressed = [](EventKeyboard::KeyCode keycode, Event* event)
	{
		if (keycode == EventKeyboard::KeyCode::KEY_ESCAPE)
			Director::getInstance()->popScene();
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboard, this);

	return true;
}

void SettingScene::back()
{
	Director::getInstance()->popToSceneStackLevel(2);
}