
#include"FPlane.h"
#include "MyBullet.h"
#include"MyBodyParser.h"
#include"GameOverScene.h"
#include"Enemy.h"

USING_NS_CC;

FPlane::FPlane()
{

}

FPlane::~FPlane()
{

}

FPlane* FPlane::FPlaneInstance;

FPlane* FPlane::create(Node* rootNode)
{
	//初始化静态的FPLaneInstance指针，将fplane指针指向文件中的飞机
	auto fplane = new FPlane();

	fplane->setName("fplane"); 
	
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("FPlane/fplane.plist");
	fplane->initWithSpriteFrameName("fplane.png");
	//////////////////////////////////////////////////
	//!!!!!!!!!!!!!!!!!!!!1为什么我只用autorealease（） 这个实例就会被销毁，点击鼠标时，程序就会报错!!!!!!!!!!!!!!!!!!!!!!!!!
	//所以我用了一个retain（）
	//////////////////////////////////////////////////

	MyBodyParser::getInstance()->parseJsonFile("bodies/plane.json");
	auto fplanebody = MyBodyParser::getInstance()->bodyFormJson(fplane, "FPlane");
	fplanebody->setCategoryBitmask(0x00000001);
	fplanebody->setContactTestBitmask(0x00010000);
	fplanebody->setCollisionBitmask(0);

	fplane->setPhysicsBody(fplanebody);

	////FPlane的血量
	fplane->blood = 10000;
	fplane->skill = 10000;

	FPlaneInstance = fplane;
	fplane->parent = rootNode;

	fplane->schedule(schedule_selector(FPlane::update), 1);
	return fplane;
	///////////////鼠标响应
	//auto mouse = EventListenerMouse::create();
	///////鼠标点击，飞机射击
	//mouse->onMouseDown = [=](EventMouse* event)
	//{
	//	FPlane::getInstance()->shoot(superbullet);


	//	/*auto fplane = rootNode->getChildByName("fplane");
	//	auto dir = fplane->getRotation();
	//	auto pos = fplane->getPosition();

	//	auto bullet = MyBullet::create("bullet/MyBullet_1.png", pos.x, pos.y, dir);
	//	rootNode->addChild(bullet);
	//	bullet->setPosition(pos);
	//	bullet->setRotation(dir);*/
	//	log("mouseDown Found!!!!!!");
	//};
	//FPlaneInstance->_eventDispatcher->addEventListenerWithSceneGraphPriority(mouse, FPlaneInstance);

};

FPlane* FPlane::getInstance()
{
	//返回当前存在的FPlane实例
	return FPlaneInstance;
};

//cocos2d::Node* FPlane::getFPlane()
//{
//	return getInstance()->fplane;
//}

cocos2d::Node* FPlane::getParent()
{
	return parent;
}

void FPlane::shoot(BulletType bullettype)
{
	auto rootNode = FPlane::getInstance()->getParent();
	auto environment = rootNode->getChildByName("environment");
	auto x =  getPosition().x;
	auto y =  getPosition().y;
	auto dir =  getRotation();
	MyBullet* bullet;
	switch (bullettype)
	{
	case normalbullet:bullet = MyBullet::create("MyBullet_2.png", x, y, dir); break;
	case seniorbullet:bullet = MyBullet::create("MyBullet_1.png", x, y, dir); break;
	case superbullet:default:
		bullet = MyBullet::create("MyBullet_3.png", x, y, dir); break;
	}

	///////////子弹不会接受fplane或其他子弹的碰撞消息
	//auto body = PhysicsBody::createBox(bullet->getContentSize());

	//body->setCategoryBitmask(0x00000001);
	//body->setContactTestBitmask(0x00000010);
	//bullet->setPhysicsBody(body);

	environment->addChild(bullet);
	bullet->setPosition(environment->convertToNodeSpace(Point(x,y)));
	bullet->setRotation(dir);

};

void FPlane::getshot(BulletType bullettype)
{
	if (!this->protecting)
	{

		switch (bullettype)
		{
		case normalbullet:blood -= 100; break;
		case seniorbullet:blood -= 150; break;
		case superbullet:blood -= 500; break;
		case enemy:blood -= 50; break;
		default:;
		}

		if (bullettype == superbullet)
		{
			auto animation = Animation::create();

			for (int i = 1; i <= 12; i++)
			{
				auto framename = String::createWithFormat("Bullet/fplanegetshot/exp_%d.png", i);
				animation->addSpriteFrameWithFile(framename->getCString());
			}
			animation->setDelayPerUnit(0.1f);
			animation->setRestoreOriginalFrame(true);

			auto defunc = [=](Node* sender)
			{
				sender->removeFromParent();
			};
			auto destroy = CallFuncN::create(defunc);

			auto action = Sequence::create(Animate::create(animation), destroy, 0);
			auto fire = Sprite::create();
			fire->setName("fire");

			this->addChild(fire);
			fire->setAnchorPoint(Point(0, 0));
			fire->runAction(action);
		};

		
	}

	if (blood <= 0)
		Director::getInstance()->replaceScene(GameOverScene::createScene());
}

float FPlane::getblood()
{
	return blood;
}

float FPlane::getskill()
{
	return skill;
}

void FPlane::thunder()
{
	if (this->skill < 3000)
		return;
	this->skill -= 2000;

	auto thunder = Thunder::create();
	parent->addChild(thunder);
	thunder->setPosition(600, 300);
	thunder->setAnchorPoint(Vec2(0.5, 0.5));

	thunder->attack();
	
}

void FPlane::protect()
{
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("FPlane/fplane.plist");

	if (this->skill < 500)
	{
		return;
	}
	else
	{
		this->skill -= 500;
		this->initWithSpriteFrameName("FPlane/fplane_protected.png");

		protecting = 1;

		auto endprotect = [=](float dt)
		{
			this->endprotect();

		};
		this->scheduleOnce(ccSchedulerFunc(endprotect), 2.0f, "endprotect");
	}
}

void FPlane::endprotect()
{
	protecting = 0;

	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("FPlane/fplane.plist");
	this->initWithSpriteFrameName("fplane.png");
}

void FPlane::drop()
{
	if (this->skill < 3000)
		return;
	this->skill -= 1000;

	auto drop = Drop::create();
	auto environment = parent->getChildByName("environment");
	environment->addChild(drop);
	drop->setPosition(environment->convertToNodeSpace(this->getPosition()));

	drop->attack();
}

void FPlane::update(float dt)
{
	if (skill >= 10000);
	else
	{
		skill += 5;
	}
	
}

Thunder::Thunder()
{

}
void Thunder::destroy(float dt)
{
	auto &enemyregister = EnemyRegister::getInstance()->enemyregister;
	auto a = this->getParent();
	auto environment = getParent()->getChildByName("environment");

	for (auto enemy : enemyregister)
	{
		//auto position = environment->convertToWorldSpace(enemy->getPosition());
		//if (position.x > 0 && position.x < 1200 && position.y>0 && position.y < 600)
		//{
		//	enemy->shotresume();
		//	/*enemy->pause();
		//	auto fire = ParticleFire::create();
		//	fire->setPosition(enemy->getPosition());
		//	environment->addChild(fire);*/
		//}
		if (enemy->thunderring)
		{
			enemy->shotresume(thunderskill);
		}
	}

	auto boss = (Boss*)environment->getChildByName("boss");
	if (boss&&boss->thunderring)
	{
		boss->shotresume(thunderskill);
	}

	/*auto fplane = (FPlane*)environment->getParent()->getChildByName("fplane");
	fplane->endprotect();*/

	this->removeFromParent();
}
void Thunder::attack()
{
	auto &enemyregister = EnemyRegister::getInstance()->enemyregister;
	auto a = this->getParent();
	auto environment = getParent()->getChildByName("environment");

	for (auto enemy : enemyregister)
	{
		auto position = environment->convertToWorldSpace(enemy->getPosition());
		if (position.x > 0 && position.x < 1200 && position.y>0 && position.y < 600)
		{
			enemy->getshot(thunderskill);
			/*enemy->pause();
			auto fire = ParticleFire::create();
			fire->setPosition(enemy->getPosition());
			environment->addChild(fire);*/
		}
	}

	auto boss = environment->getChildByName("boss");
	if (boss)
	{
		auto position = environment->convertToWorldSpace(boss->getPosition());
		if (position.x > 0 && position.x < 1200 && position.y>0 && position.y < 600)
		{
			((Boss*)boss)->getshot(thunderskill);
		}		
	}
}
;


Thunder* Thunder::create()
{
	auto thunder = new Thunder;
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("FPlane/fplane.plist");
	thunder->initWithSpriteFrameName("FPlane/thunder.png");

	//CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(Thunder::destroy), thunder, 2, false);
	thunder->scheduleOnce(schedule_selector(Thunder::destroy), 2);
	return thunder;
}

Drop::Drop()
{
}

void Drop::attack()
{
	auto &enemyregister = EnemyRegister::getInstance()->enemyregister;
	auto environment = getParent();

	for (auto enemy : enemyregister)
	{
		auto position = environment->convertToWorldSpace(enemy->getPosition());
		if (position.x > 0 && position.x < 1200 && position.y>0 && position.y < 600)
		{
			enemy->pause();
			enemy->droping = 1;
			auto moveto = MoveTo::create(0.1, enemy->getPosition());
			attacklist.pushBack(moveto);
		}
	}

	auto boss = (Boss*)environment->getChildByName("boss");
	if (boss)
	{
		auto position = environment->convertToWorldSpace(boss->getPosition());
		if (position.x > 0 && position.x < 1200 && position.y>0 && position.y < 600)
		{
			boss->pause();
			boss->droping = 1;
			auto moveto = MoveTo::create(0.1, boss->getPosition());
			attacklist.pushBack(moveto);
		}
	}

	auto animations = Sequence::create((cocos2d::Vector<FiniteTimeAction*>&) attacklist);

	auto call = CallFunc::create(this,callfunc_selector(Drop::destroy));

	auto actions = Sequence::create(animations, call,NULL);

	this->runAction(actions);

}

void Drop::destroy()
{
	auto &enemyregister = EnemyRegister::getInstance()->enemyregister;
	auto environment = getParent();
	Node::onEnter();

	for (auto enemy : enemyregister)
	{
		if (enemy->droping)
		{
			enemy->getshot(drop);
		}
	}

	auto boss = (Boss*)environment->getChildByName("boss");
	if (boss&&boss->droping)
	{
		boss->getshot(drop);
	}

	auto pauseForSenconds = [=](float dt)
	{
		for (auto enemy : enemyregister)
		{
			if (enemy->droping)
			{
				enemy->resume();
				enemy->droping = 0;
			}
		}

		if (boss&&boss->droping)
		{
			boss->resume();
			boss->droping = 0;
		}
	};

	this->scheduleOnce(ccSchedulerFunc(pauseForSenconds), 0.5f, "pauseforseconds");
	
	this->setVisible(false);

	auto remove = [=](float dt)
	{
		this->removeFromParent();
	};


	this->scheduleOnce(ccSchedulerFunc(remove), 2.0f, "remove");
	//this->removeFromParent();
}

Drop * Drop::create()
{
	auto drop = new Drop();
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Bullet/Bullet.plist");
	drop->initWithSpriteFrameName("Bullet/drop.png");

	//CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(Thunder::destroy), thunder, 2, false);
	return drop;
}
