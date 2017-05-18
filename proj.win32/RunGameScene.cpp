#include"RunGameScene.h"
#include "SimpleAudioEngine.h"


#include "cocostudio/CocoStudio.h"


#include "MyDefine.h"
#include"Enemy.h"
#include"MyBodyParser.h"
#include"MyBullet.h"

USING_NS_CC;

using namespace CocosDenshion;
using namespace cocostudio::timeline;

Scene* RunGameScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);


	auto layer = RunGameScene::create();


	scene->addChild(layer);


	return scene;
}


bool RunGameScene::init()
{
	if (!Layer::init())
		return false;

	

	return true;
}
void RunGameScene::onEnter()
{
	Layer::onEnter();
	loadmissioninfo();

	auto rootNode = CSLoader::createNode("RunGameScene.csb");
	addChild(rootNode);
	rootNode->setName("rootNode");


	auto visiblesize = Director::getInstance()->getVisibleSize();
	auto edgebox = PhysicsBody::createEdgeBox(visiblesize, PHYSICSBODY_MATERIAL_DEFAULT);
	rootNode->setPhysicsBody(edgebox);

	///////////////////////////////////////		音乐控制	////////////////////////////////////////////////

	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BGMFileName.data());
	SimpleAudioEngine::getInstance()->preloadEffect("zidan.mp3");

	SimpleAudioEngine::getInstance()->playBackgroundMusic(BGMFileName.data(),true);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////	environment
	///////容纳敌机和背景的节点
	auto environment = rootNode->getChildByName("environment");
	environment->setZOrder(-1);
	environment->setAnchorPoint(Vec2(0.5, 0.5));
	environment->setPosition(600, 300);

	char bkpicname[50];
	sprintf(bkpicname, "RunGameScene/bkpic/bk_%d.jpg", mapNumber);

	auto background = Sprite::create(bkpicname);
	background->setName("background");
	background->setAnchorPoint(Point(0.5, 0.5));
	background->setPosition(0, 0);
	environment->addChild(background);

	background->setVisible(true);
	background->setZOrder(-1);


	//auto smallmap = rootNode->getChildByName("smallmap");

	auto smallmap = Sprite::create("smallmap/map_01.png");
	smallmap->setName("smallmap");
	smallmap->setPosition(1050, 470);
	rootNode->addChild(smallmap);

	auto smallman = Sprite::create("smallmap/smallman.png");
	smallman->setName("smallman");
	smallman->setPosition(1050, 470);
	rootNode->addChild(smallman);

	auto menucallback = [=](Ref*)
	{
		auto menulayer = this->getChildByName("menulayer");
		if (menulayer)
		{
			menulayer->removeFromParent();
		}
		else
		{
			menulayer = CSLoader::createNode("RunGameScene/Pause/Pause.csb");
			menulayer->setPosition(600, 300);
			menulayer->setName("menulayer");
			this->addChild(menulayer);

			auto back = dynamic_cast<cocos2d::ui::Button*>(menulayer->getChildByName("back"));
			auto backcallback = [=](Ref* sender)
			{
				Director::getInstance()->popScene();
			};
			back->addClickEventListener(backcallback);

			auto continueButton = dynamic_cast<cocos2d::ui::Button*>(menulayer->getChildByName("continue"));
			auto continuecallback = [=](Ref* sender)
			{
				menulayer->removeFromParent();
			};
			continueButton->addClickEventListener(continuecallback);

		}
	};

	auto menu = dynamic_cast<cocos2d::ui::Button*>(rootNode->getChildByName("mainmenu"));
	menu->addClickEventListener(menucallback);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////初始化Fplane类
	/*FPlane::create(rootNode);
	auto fplane = FPlane::getInstance()->getFPlane();*/
	auto fplane = FPlane::create(rootNode);
	rootNode->addChild(fplane);
	fplane->setPosition(100, 200);
	/*auto smallplane = Sprite::create("smallmap/fplane.png");
	smallmap->addChild(smallplane);
	smallplane->setName("smallplane");*/



	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////初始化Boss类
	/*Boss::getOriginInstance(environment, "boss");
	auto boss = Boss::create();

	boss->getbosssprite()->setZOrder(0);*/

	//Boss::getOriginInstance(environment, "boss");


	/*auto boss = Boss::create(BossFrameName,BossBlood);
	environment->addChild(boss);
	boss->setName("boss");
	boss->setZOrder(0);*/
	/*auto smallboss = Sprite::create("smallmap/boss.png");
	smallmap->addChild(smallboss);
	smallboss->setName("smallboss");*/


	EnemyRegister::create();
	auto &enemyregister = EnemyRegister::getInstance()->enemyregister;
	rootNode->addChild(EnemyRegister::getInstance());

	mission = 0;
	nextroom();

	//auto enemy1 = JuniorEnemy::create(junior, seniorbullet);
	//environment->addChild(enemy1);
	//enemy1->setPosition(100, 300);
	//enemyregister.pushBack(enemy1);
	////enemyregister[enemyregister.end()->first] = enemy1;
	////auto smallenemy1 = Sprite::create("smallmap/enemy.png");
	////smallmap->addChild(smallenemy1);
	//////enemyregister[enemy1] = smallenemy1;
	////enemyregister.insert(enemy1, smallenemy1);



	//auto enemy2 = JuniorEnemy::create(junior, seniorbullet);
	//environment->addChild(enemy2);
	//enemy2->setPosition(900, 100);
	//enemyregister.pushBack(enemy2);
	////enemyregister[enemyregister.end()->first] = enemy2;
	///*auto smallenemy2 = Sprite::create("smallmap/enemy.png");
	//smallmap->addChild(smallenemy2);
	//smallmap->setVisible(false);*/

	////smallenemy2->setTag(SMALLENEMY + 1);
	//////enemyregister[enemy2] = smallenemy2;
	////



	//auto enemy3 = JuniorEnemy::create(junior, seniorbullet);
	//environment->addChild(enemy3);
	//enemy2->setPosition(-900, 2100);
	//enemyregister.pushBack(enemy3);
	////enemyregister[enemyregister.end()->first] = enemy3;
	////auto smallenemy3 = Sprite::create("smallmap/enemy.png");
	////smallmap->addChild(smallenemy3);
	////smallenemy3->setTag(SMALLENEMY + 2);
	//////enemyregister[enemy3] = smallenemy3;



	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////增加血条
	/*auto layer = LayerColor::create(Color4B(225, 0, 0, 255));
	layer->setContentSize(CCSizeMake(1000, 80));
	layer->setPosition(Point(0, 0));
	layer->setName("blood");
	addChild(layer, 10);*/

	/*auto bloodarea = Sprite::create("Bullet/MyBullet_2.png");
	rootNode->addChild(bloodarea);
	bloodarea->setPosition(150, 150);
	bloodarea->setContentSize(Size(50,50));
	auto spriteSize = bloodarea->getContentSize();
	auto size = Director::getInstance()->getWinSize();*/


	//CCSprite *pRectSpriteRB = CCSprite::create("Bullet/MyBullet_2.png", CCRect(0,0, spriteSize.width , spriteSize.height/2 ));
	////pRectSpriteRB->setPosition(ccp(size.width / 2 + spriteSize.width + pRectSpriteRB->getContentSize().width / 2, size.height / 2 - spriteSize.height / 2 - pRectSpriteRB->getContentSize().height / 2));
	//rootNode->addChild(pRectSpriteRB);
	//pRectSpriteRB->setPosition(500, 500);
	////右下原图


	///////////////////////////////////////////////////////////////////////////////////////////////////////////





	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////用鼠标旋转，射击飞机
	auto mouserotate = EventListenerMouse::create();
	mouserotate->onMouseMove = [=](EventMouse* event)
	{
		auto MousePos = Director::sharedDirector()->getInstance()->convertToGL(event->getLocation());
		auto ThisPos = fplane->getPosition();
		auto angle = CC_RADIANS_TO_DEGREES(atan2(ThisPos.y - MousePos.y, MousePos.x - ThisPos.x));
		fplane->setRotation(angle);

	};
	mouserotate->onMouseDown = [=](EventMouse* event)
	{
		fplane->shoot(seniorbullet);
		SimpleAudioEngine::getInstance()->playEffect("zidan.mp3");
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouserotate, this);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////用键盘移动飞机
	auto keyboardmove = EventListenerKeyboard::create();
	keyboardmove->onKeyPressed = [=](EventKeyboard::KeyCode keycode, Event* event)
	{
		if (keycode == EventKeyboard::KeyCode::KEY_ESCAPE)
			Director::getInstance()->end();

		if (keycode == EventKeyboard::KeyCode::KEY_Q)
			fplane->thunder();
		else if (keycode == EventKeyboard::KeyCode::KEY_E)
			fplane->drop();
		else if (keycode == EventKeyboard::KeyCode::KEY_R)
			fplane->protect();

		if (keycode == EventKeyboard::KeyCode::KEY_SPACE)
		{
			rootNode->pause();

			for (const auto& node : rootNode->getChildren())
			{
				node->pause();
			}
		}
		if (keycode == EventKeyboard::KeyCode::KEY_R)
			Director::getInstance()->resume();
		//Director::getInstance()->popScene();
		else if (RunGameScene::transformkey(keycode) != -1)
			this->keystate[RunGameScene::transformkey(keycode)] = true;
	};
	keyboardmove->onKeyReleased = [=](EventKeyboard::KeyCode keycode, Event* event)
	{
		if (RunGameScene::transformkey(keycode) != -1)
			this->keystate[RunGameScene::transformkey(keycode)] = false;
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardmove, this);
	;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////增加碰撞事件

	//// 添加 碰撞事件监听器
	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();

	auto contact = EventListenerPhysicsContact::create();
	contact->onContactBegin = [this](cocos2d::PhysicsContact& contact)
	{
		auto spriteA = contact.getShapeA()->getBody()->getNode();
		auto spriteB = contact.getShapeB()->getBody()->getNode();

		///////////////////////////////////////////////////MyBullet 与 Boss 碰撞///////////////////////////////////////////
		Node *boss = 0;
		Node *mybullet = 0;
		if (spriteA->getName() == "boss"&&spriteB->getName() == "mybullet")
		{
			//A是FPlane
			/*spriteB->setVisible(false);
			spriteB->getPhysicsBody()->setContactTestBitmask(0);
			spriteB->getPhysicsBody()->setCategoryBitmask(0);*/
			//FPlane::getInstance()->getshot(superbullet);
			//((Boss*)spriteA)->getshot(superbullet);
			boss = spriteA;
			mybullet = spriteB;
			//spriteA->setVisible(false);
			//log("contact +1");

		}
		else if (spriteB->getName() == "boss"&&spriteA->getName() == "mybullet")
		{
			//B是FPlane
			/*spriteA->setVisible(false);
			spriteA->getPhysicsBody()->setContactTestBitmask(0);
			spriteA->getPhysicsBody()->setCategoryBitmask(0);*/


			//FPlane::getInstance()->getshot(superbullet);
			//((Boss*)spriteB)->getshot(superbullet);
			boss = spriteB;
			mybullet = spriteA;
			//spriteB->setVisible(false);
			//log("contact +1");
		}

		if (boss&&mybullet)
		{
			//auto n = mybullet->getReferenceCount();
			((Boss*)boss)->getshot(superbullet);
			//boss->release();


			///////////////////////////////////////////////	BUG	////////////////////////////////////////////////
			////////////////////////由于未知原因，每个碰撞会被执行两次，所以不能在一次碰撞中删除某个节点，如子弹或飞机,
			////////////////////////改为设置不可见，并将接触的可能去除
			//mybullet->removeFromParent();
			mybullet->setVisible(false);
			//n = mybullet->getReferenceCount();

			//mybullet->release();
			mybullet->getPhysicsBody()->setCategoryBitmask(0);
			mybullet->getPhysicsBody()->setContactTestBitmask(0);

			log("%d号子弹与boss碰撞", mybullet->getTag() - 100);
			return true;
		}



		/////////////////////////////////////////////////MyBullet 与 一般飞机碰撞////////////////////////////////////////////////
		Node *enemy = 0;
		mybullet = 0;
		if (spriteA->getName() == "JuniorEnemy"&&spriteB->getName() == "mybullet")
		{
			enemy = spriteA;
			mybullet = spriteB;

		}
		else if (spriteB->getName() == "JuniorEnemy"&&spriteA->getName() == "mybullet")
		{
			enemy = spriteB;
			mybullet = spriteA;
		}

		if (enemy&&mybullet)
		{
			((JuniorEnemy*)enemy)->getshot(superbullet);
			mybullet->/*removeFromParent*/setVisible(false);
			mybullet->getPhysicsBody()->setCategoryBitmask(0);
			mybullet->getPhysicsBody()->setContactTestBitmask(0);

			log("%d号子弹与JuniorEnemy碰撞", mybullet->getTag() - 100);
			return true;
		}

		/////////////////////////////////////////////////EnemyBullet 与 FPlane碰撞////////////////////////////////////////////////
		Node *enemybullet = 0;
		Node* fplane = 0;
		if (spriteA->getName() == "fplane"&&spriteB->getName() == "enemybullet")
		{
			fplane = spriteA;
			enemybullet = spriteB;

		}
		else if (spriteB->getName() == "fplane"&&spriteA->getName() == "enemybullet")
		{
			fplane = spriteB;
			enemybullet = spriteA;
		}

		if (fplane&&enemybullet)
		{
			((FPlane*)fplane)->getshot(((EnemyBullet*)enemybullet)->type);
			enemybullet->/*removeFromParent();*/setVisible(false);
			enemybullet->getPhysicsBody()->setCategoryBitmask(0);
			enemybullet->getPhysicsBody()->setContactTestBitmask(0);

			log("敌人子弹与我碰撞");
			return true;
		}


		/////////////////////////////////////////////////JuniorEnemy 与 FPlane碰撞////////////////////////////////////////////////
		enemy = 0;
		fplane = 0;
		if (spriteA->getName() == "fplane" && (spriteB->getName() == "JuniorEnemy"|| spriteB->getName() == "boss"))
		{
			fplane = spriteA;
			enemy = spriteB;

		}
		else if (spriteB->getName() == "fplane"&&(spriteA->getName() == "JuniorEnemy"|| spriteA->getName() == "boss"))
		{
			fplane = spriteB;
			enemy = spriteA;
		}

		if (fplane&&enemy)
		{
			((FPlane*)fplane)->getshot(BulletType::enemy);

			log("%s 与我碰撞",enemy->getName().c_str());
			return true;
		}


		/////////////////////////////////////////////////EnemyBullet 与 MyBullet碰撞////////////////////////////////////////////////
		enemybullet = 0;
		mybullet = 0;
		if (spriteA->getName() == "mybullet"&&spriteB->getName() == "enemybullet")
		{
			mybullet = spriteA;
			enemybullet = spriteB;

		}
		else if (spriteB->getName() == "mybullet"&&spriteA->getName() == "enemybullet")
		{
			mybullet = spriteB;
			enemybullet = spriteA;
		}

		if (mybullet&&enemybullet)
		{
			enemybullet->/*removeFromParent();*/setVisible(false);
			enemybullet->getPhysicsBody()->setCategoryBitmask(0);
			enemybullet->getPhysicsBody()->setContactTestBitmask(0);

			mybullet->/*removeFromParent();*/setVisible(false);
			mybullet->getPhysicsBody()->setCategoryBitmask(0);
			mybullet->getPhysicsBody()->setContactTestBitmask(0);

			log("敌人子弹与我子弹碰撞");
			return true;
		}


		return true;
	};

	eventDispatcher->addEventListenerWithFixedPriority(contact, 1);
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(contact,this);

	/////////////////////box-2d-editor示例
	/*auto test = Sprite::create("2d-x.png");
	MyBodyParser::getInstance()->parseJsonFile("bodies.json");
	auto _body = MyBodyParser::getInstance()->bodyFormJson(test, "Name");
	_body->setCategoryBitmask(0xffffffff);
	_body->setContactTestBitmask(0xffffffff);
	test->setPhysicsBody(_body);
	rootNode->addChild(test);
	test->setPosition(100, 100);*/

	this->unscheduleUpdate();
	this->scheduleUpdate();
	//auto keyboard = EventListenerKeyboard::create();
	//keyboard->onKeyPressed = [](EventKeyboard::KeyCode keycode, Event* event)
	//{
	//	if (keycode == EventKeyboard::KeyCode::KEY_ENTER)
	//		//Director::getInstance()->pushScene();
	//	;
	//	if (keycode == EventKeyboard::KeyCode::KEY_ESCAPE)
	//		Director::getInstance()->popScene();
	//};
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboard, this);

	inittime = time(0);

	LabelAtlas* scorenumber = CCLabelAtlas::create("1:", "RunGameScene/numbers_50_67.png", 50, 67, '0');
	scorenumber->setPosition(Point(600, 500));
	scorenumber->setAnchorPoint(Point(0.5, 0.5));
	scorenumber->setName("scorenumber");
	rootNode->addChild(scorenumber);

}
;

void RunGameScene::gameend(float dt)
{
	FPlane::getInstance()->removeFromParent();
	FPlane::getInstance()->release();

	EnemyRegister::getInstance()->removeFromParent();
	EnemyRegister::getInstance()->autorelease();
	delete(EnemyRegister::getInstance());

	Director::getInstance()->popScene();
};

int RunGameScene::transformkey(EventKeyboard::KeyCode keycode)
{
	switch (keycode)
	{
	case EventKeyboard::KeyCode::KEY_UP_ARROW:case EventKeyboard::KeyCode::KEY_W:return UP; break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:case EventKeyboard::KeyCode::KEY_S:return DOWN; break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:case EventKeyboard::KeyCode::KEY_A:return LEFT; break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:case EventKeyboard::KeyCode::KEY_D:return RIGHT; break;
	default:return -1;
	}
}

void RunGameScene::update(float delta)
{
	Node::update(delta);
	for (auto dir = 0; dir < 4; dir++)
	{
		if (keystate[dir])
		{
			move(dir);
		}
	}

	auto rootNode = getChildByName("rootNode");
	auto environment = rootNode->getChildByName("environment");
	auto bloodarea = dynamic_cast<cocos2d::ui::LoadingBar*>(rootNode->getChildByName("bloodarea"));
	auto fplane = (FPlane*)rootNode->getChildByName("fplane");
	bloodarea->setPercent(fplane->getblood() / 100);

	auto skillarea = dynamic_cast<cocos2d::ui::LoadingBar*>(rootNode->getChildByName("skillarea"));
	skillarea->setPercent(fplane->getskill() / 100);

	showsmallmap();

	auto scorenumber = (LabelAtlas*)rootNode->getChildByName("scorenumber");
	char scorestring[20];
	sprintf(scorestring, "%d", fplane->score);
	scorenumber->setString(scorestring);

	auto enemyregister = EnemyRegister::getInstance();
	if (enemyregister->enemyregister.size() == 0)
	{

		if (mission != endmission)
		{
			nextroom();
			log("next missinon");
		}
		else if (environment->getChildByName("boss") == 0)
		{
			this->pause();
			auto scale = ScaleBy::create(2, 3);
			auto move = MoveTo::create(1, Point(600, 300));
			auto endanimation = Spawn::create(scale, move, 0);
			//////////////////////////////////////////////// BUG /////////////////////////////////////////////////////////
			//////游戏结束时，退出场景，销毁敌人注册者的功能，无法放在动作的回调函数中
			//////解决方法：放在了一个定时调用的函数中，在动作执行完后执行
			/*auto call = [=](Ref* s)
			{

			FPlane::getInstance()->removeFromParent();
			FPlane::getInstance()->release();

			EnemyRegister::getInstance()->removeFromParent();
			EnemyRegister::getInstance()->autorelease();
			delete(EnemyRegister::getInstance());

			Director::getInstance()->popScene();
			};

			auto endfunc = CallFuncN::create(call);*/
			auto endaction = Sequence::create(endanimation, 0);
			scorenumber->runAction(endaction);

			CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(RunGameScene::gameend), this, 2, 0, 3, false);
		}
	}
}

void RunGameScene::move(int dir)
{
	auto rootNode = getChildByName("rootNode");
	auto environment = rootNode->getChildByName("environment");

	auto background = rootNode->getChildByName("environment")->getChildByName("background");
	auto fplane = FPlane::getInstance();
	auto position = environment->convertToWorldSpace(background->getPosition());
	auto environmentposition = environment->getPosition();
	auto fplaneposition = fplane->getPosition();
	float dy = 10, dx = 10;

	auto size = background->getContentSize();

	switch (dir)
	{
	case UP:
		//飞机在移动框内
		if (fplaneposition.y<480) { fplane->setPosition(fplaneposition.x, fplaneposition.y + dy); break; }
		//飞机在移动框上，但背景图还没有到达边缘
		else if (size.height / 2 + position.y >= 600+dy) { environment->setPosition(environmentposition.x, environmentposition.y - dy); break; }
		//飞机到了边框外面
		else if (fplaneposition.y>600) { fplane->setPosition(fplaneposition.x, fplaneposition.y - dy); break; }
		//飞机在移动框上，背景已经到达边缘
		//或者飞机在移动框外
		else { fplane->setPosition(fplaneposition.x, fplaneposition.y + dy); break; }
	case DOWN:
		if (fplaneposition.y>120) { fplane->setPosition(fplaneposition.x, fplaneposition.y - dy); break; }
		else if (position.y <= size.height / 2-dy) { environment->setPosition(environmentposition.x, environmentposition.y + dy); break; }
		else if (fplaneposition.y<0) { fplane->setPosition(fplaneposition.x, fplaneposition.y + dy); break; }
		else { fplane->setPosition(fplaneposition.x, fplaneposition.y - dy); break; }
	case LEFT:
		if (fplaneposition.x>200) { fplane->setPosition(fplaneposition.x - dx, fplaneposition.y); break; }
		else if (position.x <= size.width / 2-dx) { environment->setPosition(environmentposition.x + dx, environmentposition.y); break; }
		else if (fplaneposition.x<0) { fplane->setPosition(fplaneposition.x + dx, fplaneposition.y); break; }
		else { fplane->setPosition(fplaneposition.x - dx, fplaneposition.y); break; }
	case RIGHT:
		if (fplaneposition.x<1000) { fplane->setPosition(fplaneposition.x + dx, fplaneposition.y); break; }
		else if (size.width / 2 + position.x >= 1200+dx) { environment->setPosition(environmentposition.x - dx, environmentposition.y); break; }
		else if (fplaneposition.x>1200) { fplane->setPosition(fplaneposition.x - dx, fplaneposition.y); break; }
		else { fplane->setPosition(fplaneposition.x + dx, fplaneposition.y); break; }
	}
}

void RunGameScene::showsmallmap()
{

	auto smallman = getChildByName("rootNode")->getChildByName("smallman");

	switch (mission)
	{
	case 1:smallman->setPosition(1011, 600 - 111); break;
	case 2:smallman->setPosition(1031, 600 - 111); break;
	case 3:smallman->setPosition(1031, 600 - 133); break;
	case 4:smallman->setPosition(1054, 600 - 133); break;
	case 5:smallman->setPosition(1054, 600 - 151); break;
	case 6:smallman->setPosition(1074, 600 - 151); break;
	default:break;

	}

	//auto rootNode = getChildByName("rootNode");
	//auto environment = rootNode->getChildByName("environment");
	//auto background = environment->getChildByName("background");
	//auto smallmap = rootNode->getChildByName("smallmap");
	//auto backgroundsize = background->getContentSize();
	//auto smallmapsize = smallmap->getContentSize();


	//////////////////////////////////////////        FPlane 的位置		////////////////////////////////////////////
	//auto fplane = rootNode->getChildByName("fplane");
	//if (fplane)
	//{
	//	auto smallplane = smallmap->getChildByName("smallplane");
	//	auto planeposition = fplane->getPosition();
	//	auto smallfplaneposition = background->convertToNodeSpace(planeposition);
	//	auto newplaneposition = Point(smallfplaneposition.x*smallmapsize.width / backgroundsize.width, smallfplaneposition.y*smallmapsize.height / backgroundsize.height);
	//	smallplane->setPosition(newplaneposition);
	//}

	//////////////////////////////////////////        Boss 的位置		///////////////////////////////////////////////
	//auto boss = environment->getChildByName("boss");
	//if (boss)
	//{
	//	auto smallboss = smallmap->getChildByName("smallboss");
	//	auto bossposition = boss->getPosition();
	//	auto smallbossposition = background->convertToNodeSpace(environment->convertToWorldSpace(bossposition));
	//	auto newbossposition = Point(smallbossposition.x*smallmapsize.width / backgroundsize.width, smallbossposition.y*smallmapsize.height / backgroundsize.height);
	//	smallboss->setPosition(newbossposition);
	//}
	//


	//////////////////////////////////////////        Enemy 的位置		///////////////////////////////////////////////
	//auto &enemyregister = EnemyRegister::getInstance()->enemyregister;
	//auto i = EnemyRegister::getInstance();
	//auto keys = enemyregister.keys();

	//for (auto enemy : keys)
	//{
	//	if (enemy&&enemy->getblood()>0)
	//	{
	//		auto smallenemy = enemyregister.at(enemy);
	//		auto enemyposition = enemy->getPosition();
	//		auto smallenemyposition = background->convertToNodeSpace(environment->convertToWorldSpace(enemyposition));
	//		auto newenemyposition = Point(smallenemyposition.x*smallmapsize.width / backgroundsize.width, smallenemyposition.y*smallmapsize.height / backgroundsize.height);
	//		smallenemy->setPosition(newenemyposition);
	//	}		
	//}
}

void RunGameScene::loadmissioninfo()
{
	map();

}

void RunGameScene::nextroom()
{
	auto rootNode = getChildByName("rootNode");
	auto environment = rootNode->getChildByName("environment");
	auto fplane = rootNode->getChildByName("fplane");

	mission++;

	//切换动画
	auto fadeout = FadeOut::create(1);
	auto fadein = FadeIn::create(1);
	auto pa = [=](Node* s)
	{
		fplane->pause();

		for (auto enemy : environment->getChildren())
		{
			enemy->pause();
		}
	};
	auto re = [=](Node* s)
	{
		fplane->resume();

		for (auto enemy : environment->getChildren())
		{
			enemy->resume();
		}
	};
	auto pausesprite = CallFuncN::create(pa);
	auto resumesprite = CallFuncN::create(re);
	auto seq = Sequence::create(pausesprite, fadeout, fadein, resumesprite, 0);
	/*this->pause();

	auto re = [=](float dt)
	{
	this->resume();
	};

	this->scheduleOnce(ccSchedulerFunc(re), 2,"resume");
	*/



	environment->runAction(seq);
	rootNode->runAction(seq);

	/*for (auto i : enviros)
	{
	i->runAction(fadein);
	}
	environment->runAction(fadein);*/



	//重新生成敌机

	auto &enemyregister = EnemyRegister::getInstance()->enemyregister;

	auto smallmap = rootNode->getChildByName("smallmap");

	if (mission == endmission)
	{
		auto boss = Boss::create(BossFrameName, BossBlood);
		environment->addChild(boss);
		boss->setName("boss");
		boss->setZOrder(0);
	}

	/*auto number = missioninfo[mission];

	for (auto i = 1;i<=number;i++)
	{
	auto enemy = JuniorEnemy::create(senior, seniorbullet);
	environment->addChild(enemy);
	auto a = random();
	auto position = Point( bksize.width*(1.0*random()/RAND_MAX-0.5), bksize.height*(1.0*random() / RAND_MAX - 0.5));
	enemy->setPosition(position);
	enemyregister.pushBack(enemy);
	};*/

	auto background = environment->getChildByName("background");
	auto bksize = background->getContentSize();

	auto thismission = missionmap[mission];
	for (auto i = 1; i <= thismission->enemy1number; i++)
	{
		auto enemy = JuniorEnemy::create(thismission->enemy1, seniorbullet);
		environment->addChild(enemy);
		auto a = random();
		auto position = Point(bksize.width*(1.0*random() / RAND_MAX - 0.5), bksize.height*(1.0*random() / RAND_MAX - 0.5));
		enemy->setPosition(position);
		enemyregister.pushBack(enemy);
	}

	for (auto i = 1; i <= thismission->enemy2number; i++)
	{
		auto enemy = JuniorEnemy::create(thismission->enemy2, seniorbullet);
		environment->addChild(enemy);
		auto a = random();
		auto position = Point(bksize.width*(1.0*random() / RAND_MAX - 0.5), bksize.height*(1.0*random() / RAND_MAX - 0.5));
		enemy->setPosition(position);
		enemyregister.pushBack(enemy);
	}

	for (auto i = 1; i <= thismission->enemy3number; i++)
	{
		auto enemy = JuniorEnemy::create(thismission->enemy3, seniorbullet);
		environment->addChild(enemy);
		auto a = random();
		auto position = Point(bksize.width*(1.0*random() / RAND_MAX - 0.5), bksize.height*(1.0*random() / RAND_MAX - 0.5));
		enemy->setPosition(position);
		enemyregister.pushBack(enemy);
	}

	if (thismission->HaveAHero)
	{
		auto hero = Boss::create(thismission->heroframename, 10000);
		environment->addChild(hero);
		auto a = random();
		auto position = Point(bksize.width*(1.0*random() / RAND_MAX - 0.5), bksize.height*(1.0*random() / RAND_MAX - 0.5));
		hero->setPosition(position);
		enemyregister.pushBack((JuniorEnemy*)hero);
	}
}

void RunGameScene::map()
{
	if (mapNumber == 1)
	{
		BossFrameName = "Enemy/boss.png";
		BossBlood = 2000000;
		Enemy1 = junior;
		Enemy2 = senior;
		Enemy3 = super;

		BGMFileName = "bgm/black.mp3";

		missionmap[1] = new missioninfoma(false, "", junior, 1, super, 1, senior, 1);
		missionmap[2] = new missioninfoma(false, "", junior, 2, super, 3, senior, 7);
		missionmap[3] = new missioninfoma(false, "", junior, 5, super, 6, senior, 3);
		missionmap[4] = new missioninfoma(false, "", junior, 1, super, 6, senior, 7);
		missionmap[5] = new missioninfoma(false, "", junior, 5, super, 3, senior, 7);
		missionmap[6] = new missioninfoma(false, "", junior, 5, super, 6, senior, 7);

		missionmap[1]->retain();
		missionmap[2]->retain();
		missionmap[3]->retain();
		missionmap[4]->retain();
		missionmap[5]->retain();
		missionmap[6]->retain();

		endmission = 6;

		//missioninfoma *missioninfos[6];
		//missionarray = missioninfos;

		//missioninfos[0] = new missioninfoma(false, "", junior, 5, super, 6, senior, 7);
		//missioninfos[1] = new missioninfoma(false, "", junior, 5, super, 6, senior, 7);
		//missioninfos[2] = new missioninfoma(false, "", junior, 5, super, 6, senior, 7);
		//missioninfos[3] = new missioninfoma(false, "", junior, 5, super, 6, senior, 7);
		//missioninfos[4] = new missioninfoma(false, "", junior, 5, super, 6, senior, 7);
		//missioninfos[5] = new missioninfoma(false, "", junior, 5, super, 6, senior, 7);
		//
		//missioninfos[0]->retain();
		//missioninfos[1]->retain();
		//missioninfos[2]->retain();
		//missioninfos[3]->retain();
		//missioninfos[4]->retain();
		//missioninfos[5]->retain();

		/*endmission = 6;
		for (int i = 1; i <= endmission; i++)
		{
		missioninfo[i] = 10;

		}*/
	}

	else if (mapNumber == 2)
	{
		BossFrameName = "Enemy/boss.png";
		BossBlood = 5000000;
		Enemy1 = junior;
		Enemy2 = junior;
		Enemy3 = junior;

		BGMFileName = "bgm/Danza Kuduro.mp3";


		missionmap[1] = new missioninfoma(false, "", junior, 1, super, 2, senior, 3);
		missionmap[2] = new missioninfoma(false, "", junior, 2, super, 3, senior, 7);
		missionmap[3] = new missioninfoma(false, "", junior, 5, super, 6, senior, 3);
		missionmap[4] = new missioninfoma(false, "", junior, 1, super, 6, senior, 7);
		missionmap[5] = new missioninfoma(false, "", junior, 5, super, 3, senior, 7);
		missionmap[6] = new missioninfoma(false, "", junior, 5, super, 6, senior, 7);

		missionmap[1]->retain();
		missionmap[2]->retain();
		missionmap[3]->retain();
		missionmap[4]->retain();
		missionmap[5]->retain();
		missionmap[6]->retain();

		endmission = 6;
	}

	else if (mapNumber == 3)
	{
		BossFrameName = "Enemy/boss.png";
		BossBlood = 8000000;

		BGMFileName = "bgm/He's a Pirate .mp3";

		missionmap[1] = new missioninfoma(false, "", junior, 1, super, 0, senior, 0);
		missionmap[2] = new missioninfoma(false, "", junior, 0, super, 1, senior, 0);
		missionmap[3] = new missioninfoma(false, "", junior, 0, super, 0, senior, 1);
		missionmap[4] = new missioninfoma(false, "", junior, 1, super, 0, senior, 0);
		missionmap[5] = new missioninfoma(false, "", junior, 1, super, 0, senior, 0);
		missionmap[6] = new missioninfoma(false, "", junior, 1, super, 0, senior, 0);

		missionmap[1]->retain();
		missionmap[2]->retain();
		missionmap[3]->retain();
		missionmap[4]->retain();
		missionmap[5]->retain();
		missionmap[6]->retain();

		endmission = 6;
	}

	else if (mapNumber == 4)
	{
		BossFrameName = "Enemy/boss.png";
		BossBlood = 2000000;
		Enemy1 = junior;
		Enemy2 = junior;
		Enemy3 = junior;

		BGMFileName = "bgm/Rock House Jail.mp3";

		missionmap[1] = new missioninfoma(false, "", junior, 1, super, 2, senior, 3);
		missionmap[2] = new missioninfoma(false, "", junior, 2, super, 3, senior, 7);
		missionmap[3] = new missioninfoma(false, "", junior, 5, super, 6, senior, 3);
		missionmap[4] = new missioninfoma(false, "", junior, 1, super, 6, senior, 7);
		missionmap[5] = new missioninfoma(false, "", junior, 5, super, 3, senior, 7);
		missionmap[6] = new missioninfoma(false, "", junior, 5, super, 6, senior, 7);

		missionmap[1]->retain();
		missionmap[2]->retain();
		missionmap[3]->retain();
		missionmap[4]->retain();
		missionmap[5]->retain();
		missionmap[6]->retain();

		endmission = 6;
	}

	else if (mapNumber == 5)
	{
		BossFrameName = "Enemy/boss.png";
		BossBlood = 5000000;
		Enemy1 = junior;
		Enemy2 = junior;
		Enemy3 = junior;

		BGMFileName = "bgm/She Is My Sin.mp3";

		missionmap[1] = new missioninfoma(false, "", junior, 1, super, 2, senior, 3);
		missionmap[2] = new missioninfoma(false, "", junior, 2, super, 3, senior, 7);
		missionmap[3] = new missioninfoma(false, "", junior, 5, super, 6, senior, 3);
		missionmap[4] = new missioninfoma(false, "", junior, 1, super, 6, senior, 7);
		missionmap[5] = new missioninfoma(false, "", junior, 5, super, 3, senior, 7);
		missionmap[6] = new missioninfoma(false, "", junior, 5, super, 6, senior, 7);

		missionmap[1]->retain();
		missionmap[2]->retain();
		missionmap[3]->retain();
		missionmap[4]->retain();
		missionmap[5]->retain();
		missionmap[6]->retain();

		endmission = 6;
	}

	else
	{
		log("mapNumber didn't init");
		Director::getInstance()->end();
	}
}
