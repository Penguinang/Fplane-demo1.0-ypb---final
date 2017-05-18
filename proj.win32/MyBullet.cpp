#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "MyBullet.h"
#include"MyBodyParser.h"
USING_NS_CC;

Bullet::Bullet()
{

}

Bullet::Bullet(float x, float y, float dir)
{
	this->x = x;
	this->y = y;
	this->direction = dir;
};

MyBullet::MyBullet(const std::string &framename, float x, float y, float dir) :Bullet(x, y, dir)
{

};

MyBullet::MyBullet()
{

};

//std::map<int, MyBullet*> MyBullet::list;


MyBullet* MyBullet::create(const std::string& framename, float x, float y, float dir)
{
	auto bullet = new MyBullet(framename, x, y, dir);


	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Bullet/Bullet.plist");
	bullet->initWithSpriteFrameName("Bullet/"+framename);

	bullet->setName("mybullet");
	//bullet->autorelease();
	bullet->unscheduleUpdate();
	bullet->scheduleUpdate();

	//////////////////////////////////////////////////////////////////////////////////////////////
	/////////���ӵ����ø���


	MyBodyParser::getInstance()->parseJsonFile("bodies/SuperBullet.json");
	auto body = MyBodyParser::getInstance()->bodyFormJson(bullet, "SuperBullet");
	body->setCategoryBitmask(0x00001110);
	body->setContactTestBitmask(0x11100000);
	body->setCollisionBitmask(0x11111110);
	bullet->setPhysicsBody(body);

	return bullet;

	///////���ڲ�����sprite�����֮ǰ�趨λ�ã������ҵĽ�������ǣ���sprite�����һ��spritechild����spritechild���λ��
	////////////��spritechild��ӳ�ʼλ�ã���sprite��Ӹı�λ��
	//bullet->direction = dir;
	//bullet->x = x + 200 * cos(CC_DEGREES_TO_RADIANS(dir));
	//bullet->y = y - 200 * sin(CC_DEGREES_TO_RADIANS(dir));

	//bullet->sprite.addChild(spritechild,1,10);
	//spritechild->setRotation(bullet->direction);
	//spritechild->setPosition(bullet->x, bullet->y);


	///////////���ӵ�map��β���м���ոմ������ӵ�
	/*MyBullet::list.insert(std::map<int, MyBullet*>::value_type(list.end()->first, bullet));*/
	//return bullet;
}

//void MyBullet::addBullet(Node* bullet)
//{
//	MyBullet::list.insert(std::map<int, Node*>::value_type(list.end()->first, bullet));
//};
//
//int MyBullet::getListTail()
//{
//	return list.end()->first;
//};
//
//
//Sprite* MyBullet::getbullet()
//{
//	return &sprite;
//}

void MyBullet::update(float dt)
{
	float len = 10;
	float dx = len * cos(CC_DEGREES_TO_RADIANS(direction));
	float dy = -len*sin(CC_DEGREES_TO_RADIANS(direction));
	setPosition(getPosition() + Point(dx, dy));

	auto environment = this->getParent();

	auto x = environment->convertToWorldSpace(getPosition()).x;
	auto y = environment->convertToWorldSpace(getPosition()).y;
	if (x < 0 || x>1200 || y < 0 || y>600)
	{
		removeFromParent();
	}
}

MyBullet::~MyBullet()
{

}



EnemyBullet::EnemyBullet(const std::string &framename, float x, float y, float dir) :x(x),y(y),direction(dir)
{

};

EnemyBullet::EnemyBullet()
{

};

EnemyBullet* EnemyBullet::create(const std::string& framename, float x, float y, float dir)
{
	auto bullet = new EnemyBullet(framename, x, y, dir);

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Bullet/Bullet.plist");
	bullet->initWithSpriteFrameName("Bullet/" + framename);

	bullet->setName("enemybullet");


	///////////�ӵ��������fplane�������ӵ�����ײ��Ϣ
	auto body = PhysicsBody::createBox(bullet->getContentSize());

	body->setCategoryBitmask(0x00110000);
	body->setContactTestBitmask(0x00000011);
	bullet->setPhysicsBody(body);

	bullet->autorelease();
	bullet->unscheduleUpdate();
	bullet->scheduleUpdate();
	return bullet;
}

void EnemyBullet::update(float dt)
{
	float len = 10;
	float dx = len * cos(CC_DEGREES_TO_RADIANS(direction));
	float dy = -len*sin(CC_DEGREES_TO_RADIANS(direction));
	setPosition(getPosition() + Point(dx, dy));

	auto environment = this->getParent();
	auto position = environment->convertToWorldSpace(getPosition());
	if (position.x < 0 || position.x>1200 || position.y < 0 || position.y>600)
	{
		removeFromParent();
	}
}

EnemyBullet::~EnemyBullet()
{

}

