#pragma once
#include "cocos2d.h"


#include"MyDefine.h"

class Bullet :public cocos2d::Sprite
{
	////////x,y 是位置，dir是弧度方向

protected:
	float x = 0.0;
	float y = 0.0;
	float direction = 0.0;
public:
	Bullet();
	Bullet(float x, float y, float dir);
	void move();
	void show();

};

class MyBullet :public Bullet
{

public:
	MyBullet();
	MyBullet(const std::string& filename, float x, float y, float dir);
	static MyBullet* create(const std::string& filename, float x, float y, float dir);
	~MyBullet();
	virtual void update(float dt);

};


class EnemyBullet :public cocos2d::Sprite
{
private:
		float x;
		float y;
		float direction;

public:
	EnemyBullet();
	EnemyBullet(const std::string& filename, float x, float y, float dir);
	static EnemyBullet* create(const std::string& filename, float x, float y, float dir);
	~EnemyBullet();
	virtual void update(float dt);

	BulletType type;

	Sprite* realbullet;
};

