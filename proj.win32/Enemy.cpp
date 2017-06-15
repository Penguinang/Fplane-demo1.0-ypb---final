
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include"Enemy.h"
#include"MyBullet.h"
#include"MyBodyParser.h"
#include"FPlane.h"
#include"RunGameScene.h"

using namespace cocos2d;
using namespace cocos2d::ui;

EnemyRegister* EnemyRegister::Instance;

Boss::Boss()
{

};

Boss::~Boss()
{

};

//void Boss::getOriginInstance(Node*  environment, string enemyname)
//{
//	OriginInstance = environment->getChildByName(enemyname);
//}

Boss* Boss::create(string& BossFrameName, int BossBlood)
{
	//auto bosssprite = Sprite::createWithSpriteFrame(((Sprite*)OriginInstance)->getSpriteFrame());	

	//auto boss = new Boss();
	////boss->retain();
	//boss->autorelease();


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////BUG
	/////不能将自己定义的类对象使用addchild加入节点中，加入之后总是会自动释放
	/*auto en = OriginInstance->getParent();
	en->addChild(boss);
	boss->retain();*/
	//boss->bosssprite = bosssprite;


	auto boss = new Boss();
	boss->setName("boss");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Enemy/enemy.plist");
	boss->initWithSpriteFrameName(BossFrameName);

	boss->initblood = BossBlood;
	boss->blood = BossBlood;

	auto bloodTexture = TextureCache::sharedTextureCache()->addImage("Enemy/bloodbar.png");
	auto bloodbar = LoadingBar::create("Enemy/bloodbar.png");
	bloodbar->setScaleX(powf(BossBlood / 2000000, 0.3333));
	
	bloodbar->setPercent(100);
	bloodbar->setPosition(Point(0, 120));
	bloodbar->setName("bloodbar");
	boss->addChild(bloodbar);


	MyBodyParser::getInstance()->parseJsonFile("bodies/Boss.json");
	auto bossbody = MyBodyParser::getInstance()->bodyFormJson(boss, "Boss");

	bossbody->setCategoryBitmask(0x10010000);
	bossbody->setContactTestBitmask(0x00001001);

	boss->setPhysicsBody(bossbody);
	boss->setPosition(500, 500);

	boss->unscheduleUpdate();
	CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(Boss::update), boss, 0.1, false);
	//boss->scheduleUpdate();
	return boss;
}

void Boss::update(float dt)
{
	Node::update(dt);

	auto environment =  getParent();

	auto bossposition = environment->convertToWorldSpace( getPosition());

	auto rootNode = environment->getParent();
	auto fplane = rootNode->getChildByName("fplane");
	/////////////////////////////////////////////////////////////////////////////////////////////////
	//////boss AI
	/////////////第一步，自动飞到FPlane的位置

	auto dx = 10;

	auto position = fplane->getPosition();
	if (position.x > bossposition.x + 200)
		 setPosition(environment->convertToNodeSpace(bossposition + Point(dx, 0)));
	else
		if (position.x > bossposition.x - 200);
		else
			 setPosition(environment->convertToNodeSpace(bossposition + Point(-dx, 0)));

	bossposition = environment->convertToWorldSpace( getPosition());
	if (position.y > bossposition.y + 200)
		 setPosition(environment->convertToNodeSpace(bossposition + Point(0, dx)));
	else if (position.y > bossposition.y - 200);
	else
		 setPosition(environment->convertToNodeSpace(bossposition + Point(0, -dx)));


	///////////第二步，用屁股对准FPlane 后射击
	auto fplaneposition = fplane->getPosition();
	auto dir = CC_RADIANS_TO_DEGREES(atan2((bossposition.y - fplaneposition.y), (fplaneposition.x - bossposition.x)));
	auto rotation =  getRotation();

	if (rotation - dir > 5)
		 setRotation(rotation - 3);
	else if (rotation - dir < -5)
		 setRotation(rotation + 3);
	else shoot(superbullet);


	if (blood <= 0)
	{
		/*auto smallboss = getParent()->getParent()->getChildByName("smallmap")->getChildByName("smallboss");
		smallboss->removeFromParent();*/

		this->removeFromParent();

	}
	else
	{
		auto bloodbar = dynamic_cast<LoadingBar*>(this->getChildByName("bloodbar"));
		bloodbar->setPercent(this->blood*100 / this->initblood);

		bloodbar->setRotation(-this->getRotation());
		bloodbar->setPosition(this->convertToNodeSpace(environment->convertToWorldSpace(getPosition() + Point(0, 120))));
		
	}
};


//Node* Boss::OriginInstance;
//
//Node* Boss::getbosssprite()
//{
//	return OriginInstance;
//}


void Boss::shoot(BulletType bullettype)
{
	auto environment =  getParent();
	auto x =  getPosition().x;
	auto y =  getPosition().y;
	auto dir =  getRotation();


	EnemyBullet* bullet;
	switch (bullettype)
	{
	case normalbullet:bullet = EnemyBullet::create("MyBullet_2.png", x, y, dir); break;
	case seniorbullet:bullet = EnemyBullet::create("MyBullet_1.png", x, y, dir); break;
	case superbullet:default:
		bullet = EnemyBullet::create("MyBullet_3.png", x, y, dir); break;
	}

	bullet->type = bullettype;

	///////////子弹不会接受fplane或其他子弹的碰撞消息
	//auto body = PhysicsBody::createBox(bullet->getContentSize());

	//body->setCategoryBitmask(0x00000001);
	//body->setContactTestBitmask(0x00000010);
	//bullet->setPhysicsBody(body);

	environment->addChild(bullet);
	bullet->setPosition(x, y);
	bullet->setRotation(dir);
}

void Boss::getshot(BulletType bullettype)
{
	auto fplane = FPlane::getInstance();

	if (bullettype == thunderskill)
	{
		this->pause();
		auto thunder = CSLoader::createNode("Bullet/thunder.csb");
		thunder->setPosition(100, 50);
		thunder->setName("thunder");
		this->addChild(thunder);

		auto action = CSLoader::createTimeline("Bullet/thunder.csb");
		this->runAction(action);

		action->gotoFrameAndPlay(0, 15, true);
		blood -= 400000;
		thunderring = 1;
		fplane->score += 1000;
		return;
	}

	if (bullettype == drop)
	{
		this->blood -= 200000;
		auto fplane = FPlane::getInstance();
		fplane->score += 2000;

		auto fire = ParticleSystemQuad::create("Bullet/NBoom/Resources/particle/dust/dustBurst.plist");
		fire->setPosition(0, 0);
		fire->setDuration(0.1);

		this->addChild(fire);
		return;
	}


	fplane->score += 100;
	blood -= 100000;
	
};

void Boss::shotresume(BulletType bullettype)
{
	if (bullettype == thunderskill)
	{
		thunderring = 0;
		this->stopAllActions();
		this->removeChildByName("thunder");
		this->resume();
	}
	//fire->removeFromParent();
}

//void Boss::getdroped()
//{
//	this->blood -= 500000;
//	auto fplane = FPlane::getInstance();
//	fplane->score += 2000;
//
//	auto fire = ParticleSystemQuad::create("Bullet/NBoom/Resources/particle/dust/dustBurst.plist");
//	fire->setPosition(0, 0);
//	fire->setDuration(0.1);
//
//	this->addChild(fire);
//}

JuniorEnemy::JuniorEnemy()
{

};
JuniorEnemy::~JuniorEnemy()
{

};
JuniorEnemy::JuniorEnemy(JuniorEnemy& origin) :enemytype(origin.enemytype), bullettype(origin.bullettype)
{

}


void JuniorEnemy::onEnter()
{
	Node::onEnter();
}

JuniorEnemy* JuniorEnemy::create(EnemyType enemytype, BulletType bullettype)
{
	auto enemy = new JuniorEnemy();
	enemy->setName("JuniorEnemy");

	enemy->autorelease();
	enemy->retain();
	enemy->scheduleUpdate();
	enemy->schedule(schedule_selector(JuniorEnemy::shootupdate), 0.4);

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Enemy/enemy.plist");

	auto EnemyFrameName = "Enemy/junior.png";
	int EnemyBlood;
	switch (enemytype)
	{
	case junior:EnemyFrameName = "Enemy/junior.png"; EnemyBlood = 50000;break;
	case senior:EnemyFrameName = "Enemy/enemy2.png"; EnemyBlood = 200000; break;
	case super:EnemyFrameName = "Enemy/enemy3.png"; EnemyBlood = 300000; break;
	default:log("EnemyType didn't get inited"); Director::getInstance()->end();
	}
	enemy->initWithSpriteFrameName(EnemyFrameName);
	enemy->initblood = EnemyBlood;
	enemy->blood = EnemyBlood;

	auto bloodTexture = TextureCache::sharedTextureCache()->addImage("Enemy/Smallbloodbar.png");
	auto bloodbar = LoadingBar::create("Enemy/Smallbloodbar.png");
	bloodbar->setScaleX(powf(EnemyBlood / 50000, 0.3333));

	bloodbar->setPercent(100);
	bloodbar->setPosition(Point(0, 60));
	bloodbar->setName("bloodbar");
	enemy->addChild(bloodbar);

	enemy->enemytype = enemytype;
	enemy->bullettype = bullettype;

	/*MyBodyParser::getInstance()->parseJsonFile("bodies/JuniorEnemy.json");
	auto body = MyBodyParser::getInstance()->bodyFormJson(enemy, "JuniorEnemy");*/
	auto body = PhysicsBody::createBox(enemy->getContentSize());
	body->setCategoryBitmask(0x01010000);
	body->setContactTestBitmask(0x00000101);
	body->setCollisionBitmask(-1);

	enemy->setPhysicsBody(body);

	return enemy;

}

void JuniorEnemy::update(float dt)
{

	Node::update(dt);

	auto environment = getParent();
	auto rootNode = environment->getParent();

	auto thisposition = environment->convertToWorldSpace(getPosition());

	auto fplane = rootNode->getChildByName("fplane");
	/////////////////////////////////////////////////////////////////////////////////////////////////
	//////boss AI
	/////////////第一步，自动飞到FPlane的位置
	auto position = fplane->getPosition();
	if (position.x > thisposition.x + 200)
		this->setPosition(environment->convertToNodeSpace(thisposition + Point(5, 0)));
	else
		if (position.x > thisposition.x - 200);
		else
			this->setPosition(environment->convertToNodeSpace(thisposition + Point(-5, 0)));

	thisposition = environment->convertToWorldSpace(getPosition());
	if (position.y > thisposition.y + 200)
		this->setPosition(environment->convertToNodeSpace(thisposition + Point(0, 5)));
	else if (position.y > thisposition.y - 200);
	else
		this->setPosition(environment->convertToNodeSpace(thisposition + Point(0, -5)));


	/////////////第二步，用屁股对准FPlane 后射击
	auto fplaneposition = fplane->getPosition();
	auto dir = CC_RADIANS_TO_DEGREES(atan2((thisposition.y - fplaneposition.y), (fplaneposition.x - thisposition.x)));
	auto rotation = this->getRotation();

	if (rotation - dir > 5)
		this->setRotation(rotation - 3);
	else if (rotation - dir < -5)
		this->setRotation(rotation + 3);

	if (blood <= 0)
	{
		auto rootNode = environment->getParent();
		auto rungamescene = (RunGameScene*)rootNode->getParent();
		auto mission = rungamescene->mission;
		auto endmission = rungamescene->endmission;
		//auto nextroom = rungamescene->nextroom;
		auto scorenumber = (LabelAtlas*)rootNode->getChildByName("scorenumber");

		auto enemyregister = EnemyRegister::getInstance();
		/*enemyregister.at(this)->removeFromParent();*/
		enemyregister->enemyregister.eraseObject(this);

		if (enemyregister->enemyregister.size() == 0)
		{

			if (mission != endmission)
			{
				rungamescene->nextroom();
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

		this->removeFromParent();

	}
	else
	{

		auto bloodbar = dynamic_cast<LoadingBar*>(this->getChildByName("bloodbar"));
		bloodbar->setPercent(this->blood*100 / initblood);

		bloodbar->setRotation(-this->getRotation());
		bloodbar->setPosition(this->convertToNodeSpace(environment->convertToWorldSpace(getPosition() + Point(0, 60))));
	}
};

void JuniorEnemy::shootupdate(float dt)
{
	auto environment = getParent();
	auto rootNode = environment->getParent();
	auto fplane = rootNode->getChildByName("fplane");

	auto fplaneposition = fplane->getPosition();
	auto thisposition = environment->convertToWorldSpace(this->getPosition());
	auto dir = CC_RADIANS_TO_DEGREES(atan2((thisposition.y - fplaneposition.y), (fplaneposition.x - thisposition.x)));

	auto rotation = getRotation();


	if(rotation - dir <= 5&&rotation - dir >= -5)
		shoot(normalbullet);
}

void JuniorEnemy::shoot(BulletType bullettype)
{
	auto environment = getParent();
	auto x = getPosition().x;
	auto y = getPosition().y;
	auto dir = getRotation();
	EnemyBullet* bullet;
	switch (bullettype)
	{
	case normalbullet:bullet = EnemyBullet::create("MyBullet_2.png", x, y, dir); break;
	case seniorbullet:bullet = EnemyBullet::create("MyBullet_1.png", x, y, dir); break;
	case superbullet:default:
		bullet = EnemyBullet::create("MyBullet_3.png", x, y, dir); break;
	}


	environment->addChild(bullet);
	bullet->setPosition(x, y);
	bullet->setRotation(dir);
}


void JuniorEnemy::getshot(BulletType bullettype)
{
	auto fplane = FPlane::getInstance();
	if (bullettype == thunderskill)
	{
		this->pause();
		//auto fire = ParticleFire::create();
		//auto fire = ParticleExplosion::create();
		//auto fire = ParticleFireworks::create();
		/*auto fire = ParticleMeteor::create();
		
		fire->setName("fire");
		fire->setPosition(0, 0);
		this->addChild(fire); */

		auto thunder = CSLoader::createNode("Bullet/thunder.csb");
		thunder->setPosition(50, 0);
		thunder->setName("thunder");
		this->addChild(thunder);

		auto action = CSLoader::createTimeline("Bullet/thunder.csb");
		this->runAction(action);

		action->gotoFrameAndPlay(0, 15, true);


		fplane->score += 500;
		blood -= 200000;
		thunderring = 1;
		return;
	}

	if (bullettype == drop)
	{
		this->blood -= 80000;
		auto fplane = FPlane::getInstance();
		fplane->score += 500;

		auto fire = ParticleSystemQuad::create("Bullet/NBoom/Resources/particle/dust/dustBurst.plist");
		fire->setPosition(0, 0);
		fire->setDuration(0.1);

		this->addChild(fire);
		return;
	}
	
	auto fireframe = ParticleSystemQuad::create("particle/Plist/exp_2.plist");
	
	fireframe->setDuration(0.2);
	fireframe->setPosition(this->getPosition());
	this->getParent()->addChild(fireframe);

	fplane->score += 50;
	blood -= 10000;
	
}

void JuniorEnemy::shotresume(BulletType bullettype)
{
	if (bullettype == thunderskill)
	{
		this->thunderring = 0;
		this->stopAllActions();
		this->removeChildByName("thunder");
		this->resume();
	}
	
	//fire->removeFromParent();
}

//void JuniorEnemy::getdroped()
//{
//	
//	/*this->unscheduleAllSelectors();
//	this->scheduleUpdate();
//	this->schedule(schedule_selector(JuniorEnemy::shootupdate), 0.4);*/
//	/*this->scheduleOnce(schedule_selector(JuniorEnemy::dropresume), 1);*/
//	/*Node::onEnter();
//	auto a = [=](float dt)
//	{
//		this->resume();
//	};
//
//	auto b = [=](float dt)
//	{
//		this->pause();
//	};
//
//	this->scheduleOnce(ccSchedulerFunc(b), 0.0f,"pausefor2s");
//	this->scheduleOnce(ccSchedulerFunc(a), 2.0f, "dropresume");*/
//	/*CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(JuniorEnemy::dropresume), this, 1, CC_REPEAT_FOREVER, 1, false);
//	CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(JuniorEnemy::dropresume), this, 0.1, false);*/
//	//enemy->schedule(schedule_selector(JuniorEnemy::shootupdate), 0.4);
//
//	//blood -= 4000;
//	//this->resume();
//	//this->droping = 0;
//	this->blood -= 80000;
//	auto fplane = FPlane::getInstance();
//	fplane->score += 500;
//
//	//auto fire = ParticleFire::create();
//	auto fire = ParticleSystemQuad::create("Bullet/NBoom/Resources/particle/dust/dustBurst.plist");
//	fire->setPosition(0, 0);
//	fire->setDuration(0.1);
//	
//	/*fire->setEmitterMode(ParticleSystem::Mode::RADIUS );
//	fire->setPosition(0, 0);
//	fire->setDuration(0.1);
//	fire->setEndRadius(100);*/
//	this->addChild(fire);
//}

void JuniorEnemy::dropresume(float dt)
{
	this->resume();
	log("dropresume");
}

int JuniorEnemy::getblood()
{
	return blood;
}