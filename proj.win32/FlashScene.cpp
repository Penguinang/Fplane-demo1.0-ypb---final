#include "FlashScene.h"
#include"HomeScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace cocos2d::ui;

Scene* FlashScene::createScene()
{
	auto scene = Scene::create();

	auto layer = FlashScene::create();

	scene->addChild(layer);

	return scene;
}

bool FlashScene::init()
{

	if (!Layer::init())
	{
		return false;
	}

	auto rootNode = CSLoader::createNode("Start\\FlashScene.csb");

	addChild(rootNode);


	ActionTimeline*action = CSLoader::createTimeline("Start\\FlashNode.csb");

	auto a= []()
	{
		Director::getInstance()->pushScene(HomeScene::createScene());
	};

	action->addFrameEndCallFunc(135,"Start\\FlashNode.csb",a);

	rootNode->runAction(action);

	action->gotoFrameAndPlay(0, 135, false);

	return true;
}
