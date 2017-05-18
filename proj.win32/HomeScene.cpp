#include "HomeScene.h"
#include"HelpScene.h"
#include"SelectMapScene.h"
#include"SettingScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HomeScene::createScene()
{
    auto scene = Scene::create();
    
    auto layer = HomeScene::create();

    scene->addChild(layer);

    return scene;
}

bool HomeScene::init()
{
    
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("Start\\HomeScene.csb");
    addChild(rootNode);

	CCSprite*background1 = CCSprite::create("Start\\First.png");
	background1->setPosition(600, 300);
	this->addChild(background1);

	CCSprite*theme = CCSprite::create("Start\\theme.png");
	theme->setPosition(302, 300);
	this->addChild(theme);

	auto click_left = MenuItemImage::create("Start\\left.png", "Start\\left_2.png", CC_CALLBACK_0(HomeScene::left1, this));
	auto menu_left = Menu::create(click_left, 0);
	menu_left->setPosition(546, 300);
	this->addChild(menu_left);

	auto click_Right = MenuItemImage::create("Start\\right.png", "Start\\right_2.png", CC_CALLBACK_0(HomeScene::right1, this));
	auto menu_Right = Menu::create(click_Right, 0);
	menu_Right->setPosition(668.6, 300);
	this->addChild(menu_Right);

	auto click_theme = MenuItemImage::create("Start\\Firstbutton.png", "Start\\Firstbutton_press.png", CC_CALLBACK_0(HomeScene::enter1, this));
	auto menu_theme = Menu::create(click_theme, 0);
	menu_theme->setPosition(605, 300);
	this->addChild(menu_theme);

	auto keyboard = EventListenerKeyboard::create();

	keyboard->onKeyPressed = [this](EventKeyboard::KeyCode keycode, Event* event)
	{
		if (keycode == EventKeyboard::KeyCode::KEY_D)
		{
			right1();
		};
		if (keycode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
		{
			right1();
		};
		if (keycode == EventKeyboard::KeyCode::KEY_A)
		{
			left1();
		};
		if (keycode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
		{
			left1();
		};
		if (keycode == EventKeyboard::KeyCode::KEY_ENTER)
		{
			enter1();
		};
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboard, this);

	return true;
}



void HomeScene::left1()
{

	removeAllChildren();

	CCSprite*background4 = CCSprite::create("Start\\Forth.png");
	background4->setPosition(600, 300);
	this->addChild(background4);

	CCSprite*theme = CCSprite::create("Start\\theme.png");
	theme->setPosition(302, 300);
	this->addChild(theme);

	auto click_left = MenuItemImage::create("Start\\left.png", "Start\\left_2.png", CC_CALLBACK_0(HomeScene::left4, this));
	auto menu_left = Menu::create(click_left, 0);
	menu_left->setPosition(546, 300);
	this->addChild(menu_left);

	auto click_Right = MenuItemImage::create("Start\\right.png", "Start\\right_2.png", CC_CALLBACK_0(HomeScene::right4, this));
	auto menu_Right = Menu::create(click_Right, 0);
	menu_Right->setPosition(668.6, 300);
	this->addChild(menu_Right);

	auto click_theme = MenuItemImage::create("Start\\Forthbutton.png", "Start\\Forthbutton_press.png", CC_CALLBACK_0(HomeScene::enter4, this));
	auto menu_theme = Menu::create(click_theme, 0);
	menu_theme->setPosition(605, 300);
	this->addChild(menu_theme);

	auto keyboard = EventListenerKeyboard::create();

	keyboard->onKeyPressed = [this](EventKeyboard::KeyCode keycode, Event* event)
	{
		if (keycode == EventKeyboard::KeyCode::KEY_D)
		{
			right4();
		};
		if (keycode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
		{
			right4();
		};
		if (keycode == EventKeyboard::KeyCode::KEY_A)
		{
			left4();
		};
		if (keycode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
		{
			left4();
		};
		if (keycode == EventKeyboard::KeyCode::KEY_ENTER)
		{
			enter4();
		};
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboard, this);

}

void HomeScene::right1()
{
	removeAllChildren();

	CCSprite*background4 = CCSprite::create("Start\\Second.png");
	background4->setPosition(600, 300);
	this->addChild(background4);

	CCSprite*theme = CCSprite::create("Start\\theme.png");
	theme->setPosition(302, 300);
	this->addChild(theme);

	auto click_left = MenuItemImage::create("Start\\left.png", "Start\\left_2.png", CC_CALLBACK_0(HomeScene::left2, this));
	auto menu_left = Menu::create(click_left, 0);
	menu_left->setPosition(546, 300);
	this->addChild(menu_left);

	auto click_Right = MenuItemImage::create("Start\\right.png", "Start\\right_2.png", CC_CALLBACK_0(HomeScene::right2, this));
	auto menu_Right = Menu::create(click_Right, 0);
	menu_Right->setPosition(668.6, 300);
	this->addChild(menu_Right);

	auto click_theme = MenuItemImage::create("Start\\Secondbutton.png", "Start\\Secondbutton_press.png", CC_CALLBACK_0(HomeScene::enter2, this));
	auto menu_theme = Menu::create(click_theme, 0);
	menu_theme->setPosition(605, 300);
	this->addChild(menu_theme);

	auto keyboard = EventListenerKeyboard::create();

	keyboard->onKeyPressed = [this](EventKeyboard::KeyCode keycode, Event* event)
	{
		if (keycode == EventKeyboard::KeyCode::KEY_D)
		{
			right2();
		};
		if (keycode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
		{
			right2();
		};
		if (keycode == EventKeyboard::KeyCode::KEY_A)
		{
			left2();
		};
		if (keycode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
		{
			left2();
		};
		if (keycode == EventKeyboard::KeyCode::KEY_ENTER)
		{
			enter2();
		};
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboard, this);

}

void HomeScene::enter1()
{
	auto scene = SelectMapScene::createScene();
	Director::getInstance()->runWithScene(scene);
}

void HomeScene::left2()
{
	removeAllChildren();

	CCSprite*background1 = CCSprite::create("Start\\First.png");
	background1->setPosition(600, 300);
	this->addChild(background1);

	CCSprite*theme = CCSprite::create("Start\\theme.png");
	theme->setPosition(302, 300);
	this->addChild(theme);

	auto click_left = MenuItemImage::create("Start\\left.png", "Start\\left_2.png", CC_CALLBACK_0(HomeScene::left1, this));
	auto menu_left = Menu::create(click_left, 0);
	menu_left->setPosition(546, 300);
	this->addChild(menu_left);

	auto click_Right = MenuItemImage::create("Start\\right.png", "Start\\right_2.png", CC_CALLBACK_0(HomeScene::right1, this));
	auto menu_Right = Menu::create(click_Right, 0);
	menu_Right->setPosition(668.6, 300);
	this->addChild(menu_Right);

	auto click_theme = MenuItemImage::create("Start\\Firstbutton.png", "Start\\Firstbutton_press.png", CC_CALLBACK_0(HomeScene::enter1, this));
	auto menu_theme = Menu::create(click_theme, 0);
	menu_theme->setPosition(605, 300);
	this->addChild(menu_theme);

	auto keyboard = EventListenerKeyboard::create();

	keyboard->onKeyPressed = [this](EventKeyboard::KeyCode keycode, Event* event)
	{
		if (keycode == EventKeyboard::KeyCode::KEY_D)
		{
			right1();
		};
		if (keycode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
		{
			right1();
		};
		if (keycode == EventKeyboard::KeyCode::KEY_A)
		{
			left1();
		};
		if (keycode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
		{
			left1();
		};
		if (keycode == EventKeyboard::KeyCode::KEY_ENTER)
		{
			enter1();
		};
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboard, this);

}

void HomeScene::right2()
{
	removeAllChildren();

	CCSprite*background3 = CCSprite::create("Start\\Third.png");
	background3->setPosition(600, 300);
	this->addChild(background3);

	CCSprite*theme = CCSprite::create("Start\\theme.png");
	theme->setPosition(302, 300);
	this->addChild(theme);

	auto click_left = MenuItemImage::create("Start\\left.png", "Start\\left_2.png", CC_CALLBACK_0(HomeScene::left3, this));
	auto menu_left = Menu::create(click_left, 0);
	menu_left->setPosition(546, 300);
	this->addChild(menu_left);

	auto click_Right = MenuItemImage::create("Start\\right.png", "Start\\right_2.png", CC_CALLBACK_0(HomeScene::right3, this));
	auto menu_Right = Menu::create(click_Right, 0);
	menu_Right->setPosition(668.6, 300);
	this->addChild(menu_Right);

	auto click_theme = MenuItemImage::create("Start\\Thirdbutton.png", "Start\\Thirdbutton_press.png", CC_CALLBACK_0(HomeScene::enter3, this));
	auto menu_theme = Menu::create(click_theme, 0);
	menu_theme->setPosition(605, 300);
	this->addChild(menu_theme);

	auto keyboard = EventListenerKeyboard::create();

	keyboard->onKeyPressed = [this](EventKeyboard::KeyCode keycode, Event* event)
	{
		if (keycode == EventKeyboard::KeyCode::KEY_D)
		{
			right3();
		};
		if (keycode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
		{
			right3();
		};
		if (keycode == EventKeyboard::KeyCode::KEY_A)
		{
			left3();
		};
		if (keycode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
		{
			left3();
		};
		if (keycode == EventKeyboard::KeyCode::KEY_ENTER)
		{
			enter3();
		};
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboard, this);

}

void HomeScene::enter2()
{
	Director::getInstance()->pushScene(SettingScene::createScene());
}

void HomeScene::left3()
{
	removeAllChildren();

	CCSprite*background2 = CCSprite::create("Start\\Second.png");
	background2->setPosition(600, 300);
	this->addChild(background2);

	CCSprite*theme = CCSprite::create("Start\\theme.png");
	theme->setPosition(302, 300);
	this->addChild(theme);

	auto click_left = MenuItemImage::create("Start\\left.png", "Start\\left_2.png", CC_CALLBACK_0(HomeScene::left2, this));
	auto menu_left = Menu::create(click_left, 0);
	menu_left->setPosition(546, 300);
	this->addChild(menu_left);

	auto click_Right = MenuItemImage::create("Start\\right.png", "Start\\right_2.png", CC_CALLBACK_0(HomeScene::right2, this));
	auto menu_Right = Menu::create(click_Right, 0);
	menu_Right->setPosition(668.6, 300);
	this->addChild(menu_Right);

	auto click_theme = MenuItemImage::create("Start\\Secondbutton.png", "Start\\Secondbutton_press.png", CC_CALLBACK_0(HomeScene::enter2, this));
	auto menu_theme = Menu::create(click_theme, 0);
	menu_theme->setPosition(605, 300);
	this->addChild(menu_theme);

	auto keyboard = EventListenerKeyboard::create();

	keyboard->onKeyPressed = [this](EventKeyboard::KeyCode keycode, Event* event)
	{
		if (keycode == EventKeyboard::KeyCode::KEY_D)
		{
			right2();
		};
		if (keycode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
		{
			right2();
		};
		if (keycode == EventKeyboard::KeyCode::KEY_A)
		{
			left2();
		};
		if (keycode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
		{
			left2();
		};
		if (keycode == EventKeyboard::KeyCode::KEY_ENTER)
		{
			enter2();
		};
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboard, this);

}

void HomeScene::right3()
{
	removeAllChildren();

	CCSprite*background4 = CCSprite::create("Start\\Forth.png");
	background4->setPosition(600, 300);
	this->addChild(background4);

	CCSprite*theme = CCSprite::create("Start\\theme.png");
	theme->setPosition(302, 300);
	this->addChild(theme);

	auto click_left = MenuItemImage::create("Start\\left.png", "Start\\left_2.png", CC_CALLBACK_0(HomeScene::left4, this));
	auto menu_left = Menu::create(click_left, 0);
	menu_left->setPosition(546, 300);
	this->addChild(menu_left);

	auto click_Right = MenuItemImage::create("Start\\right.png", "Start\\right_2.png", CC_CALLBACK_0(HomeScene::right4, this));
	auto menu_Right = Menu::create(click_Right, 0);
	menu_Right->setPosition(668.6, 300);
	this->addChild(menu_Right);

	auto click_theme = MenuItemImage::create("Start\\Forthbutton.png", "Start\\Forthbutton_press.png", CC_CALLBACK_0(HomeScene::enter4, this));
	auto menu_theme = Menu::create(click_theme, 0);
	menu_theme->setPosition(605, 300);
	this->addChild(menu_theme);
	
	auto keyboard = EventListenerKeyboard::create();

	keyboard->onKeyPressed = [this](EventKeyboard::KeyCode keycode, Event* event)
	{
		if (keycode == EventKeyboard::KeyCode::KEY_D)
		{
			right4();
		};
		if (keycode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
		{
			right4();
		};
		if (keycode == EventKeyboard::KeyCode::KEY_A)
		{
			left4();
		};
		if (keycode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
		{
			left4();
		};
		if (keycode == EventKeyboard::KeyCode::KEY_ENTER)
		{
			enter4();
		};
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboard, this);



}

void HomeScene::enter3()
{
	Director::getInstance()->pushScene(HelpScene::createScene());
}

void HomeScene::left4()
{
	removeAllChildren();

	CCSprite*background3 = CCSprite::create("Start\\Third.png");
	background3->setPosition(600, 300);
	this->addChild(background3);

	CCSprite*theme = CCSprite::create("Start\\theme.png");
	theme->setPosition(302, 300);
	this->addChild(theme);

	auto click_left = MenuItemImage::create("Start\\left.png", "Start\\left_2.png", CC_CALLBACK_0(HomeScene::left3, this));
	auto menu_left = Menu::create(click_left, 0);
	menu_left->setPosition(546, 300);
	this->addChild(menu_left);

	auto click_Right = MenuItemImage::create("Start\\right.png", "Start\\right_2.png", CC_CALLBACK_0(HomeScene::right3, this));
	auto menu_Right = Menu::create(click_Right, 0);
	menu_Right->setPosition(668.6, 300);
	this->addChild(menu_Right);

	auto click_theme = MenuItemImage::create("Start\\Thirdbutton.png", "Start\\Thirdbutton_press.png", CC_CALLBACK_0(HomeScene::enter3, this));
	auto menu_theme = Menu::create(click_theme, 0);
	menu_theme->setPosition(605, 300);
	this->addChild(menu_theme);

	auto keyboard = EventListenerKeyboard::create();

	keyboard->onKeyPressed = [this](EventKeyboard::KeyCode keycode, Event* event)
	{
		if (keycode == EventKeyboard::KeyCode::KEY_D)
		{
			right3();
		};
		if (keycode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
		{
			right3();
		};
		if (keycode == EventKeyboard::KeyCode::KEY_A)
		{
			left3();
		};
		if (keycode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
		{
			left3();
		};
		if (keycode == EventKeyboard::KeyCode::KEY_ENTER)
		{
			enter3();
		};
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboard, this);

}

void HomeScene::right4()
{
	removeAllChildren();

	CCSprite*background1 = CCSprite::create("Start\\First.png");
	background1->setPosition(600, 300);
	this->addChild(background1);

	CCSprite*theme = CCSprite::create("Start\\theme.png");
	theme->setPosition(302, 300);
	this->addChild(theme);

	auto click_left = MenuItemImage::create("Start\\left.png", "Start\\left_2.png", CC_CALLBACK_0(HomeScene::left1, this));
	auto menu_left = Menu::create(click_left, 0);
	menu_left->setPosition(546, 300);
	this->addChild(menu_left);

	auto click_Right = MenuItemImage::create("Start\\right.png", "Start\\right_2.png", CC_CALLBACK_0(HomeScene::right1, this));
	auto menu_Right = Menu::create(click_Right, 0);
	menu_Right->setPosition(668.6, 300);
	this->addChild(menu_Right);

	auto click_theme = MenuItemImage::create("Start\\Firstbutton.png", "Start\\Firstbutton_press.png", CC_CALLBACK_0(HomeScene::enter1, this));
	auto menu_theme = Menu::create(click_theme, 0);
	menu_theme->setPosition(605, 300);
	this->addChild(menu_theme);

	auto keyboard = EventListenerKeyboard::create();

	keyboard->onKeyPressed = [this](EventKeyboard::KeyCode keycode, Event* event)
	{
		if (keycode == EventKeyboard::KeyCode::KEY_D)
		{
			right1();
		};
		if (keycode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
		{
			right1();
		};
		if (keycode == EventKeyboard::KeyCode::KEY_A)
		{
			left1();
		};
		if (keycode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
		{
			left1();
		};
		if (keycode == EventKeyboard::KeyCode::KEY_ENTER)
		{
			enter1();
		};
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboard, this);

}

void HomeScene::enter4()
{
	Director::getInstance()->end();
}