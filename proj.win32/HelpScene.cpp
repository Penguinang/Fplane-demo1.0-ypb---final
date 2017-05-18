#include "HelpScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelpScene::createScene()
{
	auto scene = Scene::create();

	auto layer = HelpScene::create();

	scene->addChild(layer);

	return scene;
}

bool HelpScene::init()
{

	if (!Layer::init())
	{
		return false;
	}

	auto rootNode = CSLoader::createNode("Start\\HelpScene.csb");

	addChild(rootNode);

	/*ActionTimeline*action = CSLoader::createTimeline("FlashNode.csb");
	rootNode->runAction(action);

	
	action->addFrameEndCallFunc(0,"FlashNode.csb",);
    action->gotoFrameAndPlay(0, 135, false);*/
	stopAllActions();
	
	CCSprite*background1 = CCSprite::create("Start\\HelpScene.png");
	background1->setPosition(600, 300);
	this->addChild(background1);

	auto click_next = MenuItemImage::create("Start\\next.png", "Start\\next_2.png", CC_CALLBACK_0(HelpScene::next, this));
	auto menu_next = Menu::create(click_next, 0);
	menu_next->setPosition(1100, 100);
	this->addChild(menu_next);

	auto click_back = MenuItemImage::create("Start\\theback.png", "Start\\theback_2.png", CC_CALLBACK_0(HelpScene::back, this));
	auto menu_back = Menu::create(click_back, 0);
	menu_back->setPosition(1100, 40);
	this->addChild(menu_back);

	return true;
}

void HelpScene::next()
{
	removeAllChildren();

	CCSprite*background2 = CCSprite::create("Start\\HelpScene_2.png");
	background2->setPosition(600, 300);
	this->addChild(background2);

	auto click_return = MenuItemImage::create("Start\\return.png", "Start\\return_2.png", CC_CALLBACK_0(HelpScene::before, this));
	auto menu_return = Menu::create(click_return, 0);
	menu_return->setPosition(1100, 100);
	this->addChild(menu_return);

	auto click_back = MenuItemImage::create("Start\\theback.png", "Start\\theback_2.png", CC_CALLBACK_0(HelpScene::back, this));
	auto menu_back = Menu::create(click_back, 0);
	menu_back->setPosition(1100, 40);
	this->addChild(menu_back);

}


void HelpScene::back()
{
	Director::getInstance()->popToSceneStackLevel(2);
}

void HelpScene::before()
{
	removeAllChildren();

	CCSprite*background1 = CCSprite::create("Start\\HelpScene.png");
	background1->setPosition(600, 300);
	this->addChild(background1);

	auto click_next = MenuItemImage::create("Start\\next.png", "Start\\next_2.png", CC_CALLBACK_0(HelpScene::next, this));
	auto menu_next = Menu::create(click_next, 0);
	menu_next->setPosition(1100, 100);
	this->addChild(menu_next);

	auto click_back = MenuItemImage::create("Start\\theback.png", "Start\\theback_2.png", CC_CALLBACK_0(HelpScene::back, this));
	auto menu_back = Menu::create(click_back, 0);
	menu_back->setPosition(1100, 40);
	this->addChild(menu_back);

}
