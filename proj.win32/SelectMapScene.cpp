#include "SelectMapScene.h"
#include"RunGameScene.h"


#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* SelectMapScene::createScene()
{
	auto scene = Scene::create();

	auto layer = SelectMapScene::create();

	scene->addChild(layer);

	return scene;
}



bool SelectMapScene::init()
{
	if (!Layer::init())
		return false;
	auto rootNode = CSLoader::createNode("SelectMapScene.csb");
	addChild(rootNode);

	auto mySprite = Sprite::create("mysprite.png");
	mySprite->setPosition(Vec2(30,55));
	mySprite->setRotation(-90);
	mySprite->setScale(1.0);
	this->addChild(mySprite, 0);
	mySprite->setName("mySprite");

	

	

	auto selectbuttonzero = MenuItemImage::create(
		"Select_Button.png",
		"Button_Disable.png",
		CC_CALLBACK_1(SelectMapScene::addzero,this)                   //点击产生第二个按钮的同时回调动作一
	);           //此步回调执行完成后转到第一个战斗场景
	selectbuttonzero->setPosition(Point(380, 160));
	auto menuzero = Menu::create(selectbuttonzero, NULL);
	menuzero->setPosition(Vec2::ZERO);
	this->addChild(menuzero, 0);                //button 1,   


	auto selectbuttonone = MenuItemImage::create(
		"Select_Button.png",
		"Button_Disable.png",
		CC_CALLBACK_1(SelectMapScene::addone, this)
	);
	selectbuttonone->setPosition(Point(200, 450));
	auto menuone = Menu::create(selectbuttonone, NULL);
	menuone->setPosition(Vec2::ZERO);
	this->addChild(menuone, 1);               //button 2

	auto selectbuttontwo = MenuItemImage::create(
		"Select_Button.png",
		"Button_Disable.png",
		CC_CALLBACK_1(SelectMapScene::addtwo, this)
	);
	selectbuttontwo->setPosition(Point(650,230));
	auto menutwo = Menu::create(selectbuttontwo, NULL);
	menutwo->setPosition(Vec2::ZERO);
	this->addChild(menutwo, 2);               //button 3

	auto selectbuttonthree = MenuItemImage::create(
		"Select_Button.png",
		"Button_Disable.png",
		CC_CALLBACK_1(SelectMapScene::addthree, this)
	);
	selectbuttonthree->setPosition(Point(840, 460));
	auto menuthree = Menu::create(selectbuttonthree, NULL);
	menuthree->setPosition(Vec2::ZERO);
	this->addChild(menuthree, 3);               //button 4
	
	auto selectbuttonfour = MenuItemImage::create(
		"Select_Button.png",
		"Button_Disable.png",
		CC_CALLBACK_1(SelectMapScene::addfour, this)
	);
	selectbuttonfour->setPosition(Point(1000, 140));
	auto menufour = Menu::create(selectbuttonfour, NULL);
	menufour->setPosition(Vec2::ZERO);
	this->addChild(menufour, 4);               //button 5


	auto keyboard = EventListenerKeyboard::create();
	keyboard->onKeyPressed = [=](EventKeyboard::KeyCode keycode, Event* event)
	{
		if (keycode == EventKeyboard::KeyCode::KEY_ENTER)
		{
			auto scene = Scene::createWithPhysics();
			scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
			scene->getPhysicsWorld()->setGravity(Vec2(0, 0));

			auto layer = RunGameScene::create();
			layer->mapNumber = this->mapNumber;

			scene->addChild(layer);

			Director::getInstance()->pushScene(scene);
			
			
		}
		;
		if (keycode == EventKeyboard::KeyCode::KEY_ESCAPE)
			Director::getInstance()->popScene();
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboard, this);

	return true;
}

//void SelectMapScene::onEnter()
//{

//}



void SelectMapScene::addzero(Ref* pSender)
{
	auto mySprite = this->getChildByName("mySprite");

	auto moveto0 = MoveTo::create(0.5, Vec2(380, 160));
	
	mySprite->runAction(Sequence::create(moveto0,  nullptr));
		
	mapNumber = 1;
};


void SelectMapScene::addone(Ref* pSender)
{
	auto mySprite = this->getChildByName("mySprite");

	
	auto moveto1 = MoveTo::create(0.5, Vec2(200, 450));
	
	mySprite->runAction(Sequence::create( moveto1, nullptr));

	mapNumber = 2;
};

void SelectMapScene::addtwo(Ref* pSender)
{
	auto mySprite = this->getChildByName("mySprite");

	
	auto moveto2 = MoveTo::create(0.5, Vec2(650, 230));
	
	mySprite->runAction(Sequence::create( moveto2, nullptr));

	mapNumber = 3;
};

void SelectMapScene::addthree(Ref* pSender)
{
	auto mySprite = this->getChildByName("mySprite");

	
	auto moveto3 = MoveTo::create(0.5, Vec2(840, 460));
	
	mySprite->runAction(Sequence::create( moveto3, nullptr));
	
	mapNumber = 4;
};

void SelectMapScene::addfour(Ref* pSender)
{
	auto mySprite = this->getChildByName("mySprite");
	
	auto moveto4 = MoveTo::create(0.5, Vec2(1000, 140));
	mySprite->runAction(Sequence::create( moveto4, nullptr));

	mapNumber = 5;
};