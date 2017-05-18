#include "ExitScene.h"
#include"HomeScene.h"
#include"HelpScene.h"

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* ExitScene::createScene()
{
	auto scene = Scene::create();

	auto layer = ExitScene::create();


	scene->addChild(layer);


	return scene;
}

bool ExitScene::init()
{
	if (!Layer::init())
		return false;
	auto rootNode = CSLoader::createNode("ExitScene.csb");
	addChild(rootNode);

	auto click_left = MenuItemImage::create("left.png", "left_2.png", CC_CALLBACK_0(ExitScene::back, this));
	auto menu_left = Menu::create(click_left, 0);
	menu_left->setPosition(546, 300);
	rootNode->addChild(menu_left);

	auto click_right = MenuItemImage::create("right.png", "right_2.png", CC_CALLBACK_0(ExitScene::turn, this));
	auto menu_right = Menu::create(click_right, 0);
	menu_right->setPosition(668.6, 300);
	rootNode->addChild(menu_right);

	auto click_theme = MenuItemImage::create("Forthbutton.png", "Forthbutton_press.png", CC_CALLBACK_0(ExitScene::enter, this));
	auto menu_theme = Menu::create(click_theme, 0);
	menu_theme->setPosition(605, 300);
	rootNode->addChild(menu_theme);



	auto keyboard = EventListenerKeyboard::create();
	keyboard->onKeyPressed = [](EventKeyboard::KeyCode keycode, Event* event)
	{
		if (keycode == EventKeyboard::KeyCode::KEY_D)
			Director::getInstance()->pushScene(HomeScene::createScene());
		;
		if (keycode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
			Director::getInstance()->pushScene(HomeScene::createScene());
		;
		if (keycode == EventKeyboard::KeyCode::KEY_A)
			Director::getInstance()->pushScene(HelpScene::createScene());
		;
		if (keycode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
			Director::getInstance()->pushScene(HelpScene::createScene());
		if (keycode == EventKeyboard::KeyCode::KEY_ENTER)
			Director::getInstance()->end();
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboard, this);
}

void ExitScene::turn()
{
	Director::getInstance()->pushScene(HomeScene::createScene());
}

void ExitScene::back()
{
	Director::getInstance()->pushScene(HelpScene::createScene());
}

void ExitScene::enter()
{
	Director::getInstance()->end();
}