#include"HelpScene.h"
#include"IntroductionScene.h"

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include"cocos2d.h"


USING_NS_CC;

using namespace cocostudio::timeline;
using namespace cocos2d::ui;


Scene* Introduction_1Scene::createScene()
{

	auto scene = Scene::create();

	auto layer = Introduction_1Scene::create();


	scene->addChild(layer);


	return scene;
}

bool Introduction_1Scene::init()
{
	if (!Layer::init())
	{
		return false;
	};

	auto rootNode = CSLoader::createNode("IntroductionScene_1.csb");

	addChild(rootNode);

	/*auto click_left = MenuItemImage::create("left.png", "left_2.png", CC_CALLBACK_0(HomeScene::back, this));
	auto menu_left = Menu::create(click_left, 0);
	menu_left->setPosition(546, 300);
	rootNode->addChild(menu_left);

	auto click_right = MenuItemImage::create("right.png", "right_2.png", CC_CALLBACK_0(HomeScene::turn, this));
	auto menu_right = Menu::create(click_right, 0);
	menu_right->setPosition(668.6, 300);
	rootNode->addChild(menu_right);

	auto click_theme = MenuItemImage::create("Firstbutton.png", "Firstbutton_press.png", CC_CALLBACK_0(HomeScene::enter, this));
	auto menu_theme = Menu::create(click_theme, 0);
	menu_theme->setPosition(605, 300);
	rootNode->addChild(menu_theme);*/

	auto keyboard = EventListenerKeyboard::create();

	keyboard->onKeyPressed = [](EventKeyboard::KeyCode keycode, Event* event)
	{
		if (keycode == EventKeyboard::KeyCode::KEY_D)
			Director::getInstance()->pushScene(Introduction_2Scene::createScene());
		;
		if (keycode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
			Director::getInstance()->pushScene(Introduction_2Scene::createScene());
		;
		if (keycode == EventKeyboard::KeyCode::KEY_ESCAPE)
			Director::getInstance()->pushScene(HelpScene::createScene());
		;
		if (keycode == EventKeyboard::KeyCode::KEY_ENTER)
			Director::getInstance()->pushScene(Introduction_2Scene::createScene());
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboard, this);

	return true;
}


void Introduction_1Scene::right()
{
	Director::getInstance()->pushScene(Introduction_2Scene::createScene());
}

void Introduction_1Scene::back()
{
	Director::getInstance()->pushScene(HelpScene::createScene());
}




Scene* Introduction_2Scene::createScene()
{

	auto scene = Scene::create();

	auto layer = Introduction_2Scene::create();


	scene->addChild(layer);


	return scene;
}

bool Introduction_2Scene::init()
{
	if (!Layer::init())
	{
		return false;
	};

	auto rootNode = CSLoader::createNode("IntroductionScene_2.csb");

	addChild(rootNode);

	/*auto click_left = MenuItemImage::create("left.png", "left_2.png", CC_CALLBACK_0(HomeScene::back, this));
	auto menu_left = Menu::create(click_left, 0);
	menu_left->setPosition(546, 300);
	rootNode->addChild(menu_left);

	auto click_right = MenuItemImage::create("right.png", "right_2.png", CC_CALLBACK_0(HomeScene::turn, this));
	auto menu_right = Menu::create(click_right, 0);
	menu_right->setPosition(668.6, 300);
	rootNode->addChild(menu_right);

	auto click_theme = MenuItemImage::create("Firstbutton.png", "Firstbutton_press.png", CC_CALLBACK_0(HomeScene::enter, this));
	auto menu_theme = Menu::create(click_theme, 0);
	menu_theme->setPosition(605, 300);
	rootNode->addChild(menu_theme);*/

	auto keyboard = EventListenerKeyboard::create();

	keyboard->onKeyPressed = [](EventKeyboard::KeyCode keycode, Event* event)
	{
		if (keycode == EventKeyboard::KeyCode::KEY_D)
			Director::getInstance()->pushScene(Introduction_3Scene::createScene());
		;
		if (keycode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
			Director::getInstance()->pushScene(Introduction_3Scene::createScene());
		;
		if (keycode == EventKeyboard::KeyCode::KEY_A)
			Director::getInstance()->pushScene(Introduction_1Scene::createScene());
		;
		if (keycode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
			Director::getInstance()->pushScene(Introduction_1Scene::createScene());
		;
		if (keycode == EventKeyboard::KeyCode::KEY_ESCAPE)
			Director::getInstance()->pushScene(HelpScene::createScene());
		;

		if (keycode == EventKeyboard::KeyCode::KEY_ENTER)
			Director::getInstance()->pushScene(Introduction_3Scene::createScene());
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboard, this);

	return true;
}

void Introduction_2Scene::back()
{
	Director::getInstance()->pushScene(HelpScene::createScene());
};

void Introduction_2Scene::left()
{
	Director::getInstance()->pushScene(Introduction_1Scene::createScene());
};

void Introduction_2Scene::right()
{
	Director::getInstance()->pushScene(Introduction_3Scene::createScene());
};



Scene* Introduction_3Scene::createScene()
{

	auto scene = Scene::create();

	auto layer = Introduction_3Scene::create();


	scene->addChild(layer);


	return scene;
}

bool Introduction_3Scene::init()
{
	if (!Layer::init())
	{
		return false;
	};

	auto rootNode = CSLoader::createNode("IntroductionScene_3.csb");

	addChild(rootNode);

	/*auto click_left = MenuItemImage::create("left.png", "left_2.png", CC_CALLBACK_0(HomeScene::back, this));
	auto menu_left = Menu::create(click_left, 0);
	menu_left->setPosition(546, 300);
	rootNode->addChild(menu_left);

	auto click_right = MenuItemImage::create("right.png", "right_2.png", CC_CALLBACK_0(HomeScene::turn, this));
	auto menu_right = Menu::create(click_right, 0);
	menu_right->setPosition(668.6, 300);
	rootNode->addChild(menu_right);

	auto click_theme = MenuItemImage::create("Firstbutton.png", "Firstbutton_press.png", CC_CALLBACK_0(HomeScene::enter, this));
	auto menu_theme = Menu::create(click_theme, 0);
	menu_theme->setPosition(605, 300);
	rootNode->addChild(menu_theme);*/

	auto keyboard = EventListenerKeyboard::create();

	keyboard->onKeyPressed = [](EventKeyboard::KeyCode keycode, Event* event)
	{
		if (keycode == EventKeyboard::KeyCode::KEY_A)
			Director::getInstance()->pushScene(Introduction_2Scene::createScene());
		;
		if (keycode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
			Director::getInstance()->pushScene(Introduction_2Scene::createScene());
		;
		if (keycode == EventKeyboard::KeyCode::KEY_ESCAPE)
			Director::getInstance()->pushScene(HelpScene::createScene());
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboard, this);

	return true;
}

void Introduction_3Scene::back()
{
	Director::getInstance()->pushScene(HelpScene::createScene());
};

void Introduction_3Scene::left()
{
	Director::getInstance()->pushScene(Introduction_2Scene::createScene());
};