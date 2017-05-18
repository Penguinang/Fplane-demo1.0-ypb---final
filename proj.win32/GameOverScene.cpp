
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include"GameOverScene.h"

using namespace ui;

Scene* GameOverScene::createScene()
{
	auto scene = Scene::create();

	auto layer = GameOverScene::create();
	
	scene->addChild(layer);
	
	return scene;
}

void GameOverScene::end(Ref* psender)
{

	Director::getInstance()->end();
}

void GameOverScene::restart(Ref* psender)
{
	Director::getInstance()->popScene();
}

bool GameOverScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto rootNode = CSLoader::createNode("GameOver/GameOverScene.csb");
	this->addChild(rootNode);


	auto restart = dynamic_cast<Widget*>(rootNode->getChildByName("restart"));
	restart->addClickEventListener(CC_CALLBACK_1(GameOverScene::restart, this));


	auto exit = dynamic_cast<Widget*>(rootNode->getChildByName("exit"));
	exit->addClickEventListener(CC_CALLBACK_1(GameOverScene::end, this));

	return true;
};
