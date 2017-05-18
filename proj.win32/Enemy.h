#pragma once


#include "cocos2d.h"
using namespace std;

#include"MyDefine.h"



class Boss :public cocos2d::Sprite
{
public:
	Boss();
	~Boss();
	//static void getOriginInstance(Node* rootNode,string enemyname);
	static Boss* create(string& BossFrameName,int BossBlood);
	virtual void update(float dt);
	void shoot(BulletType bullettype);
	void getshot(BulletType bullettype);
	void shotresume(BulletType bullettype);

	int thunderring = 0;

	//void getdroped();					//被水滴攻击
	short droping = 0;

	//Node* getbosssprite();
private:
	//static Node* OriginInstance;
	int blood;
	int initblood;
	/*Node* bosssprite;*/

};


class JuniorEnemy :public cocos2d::Sprite
{
public:
	JuniorEnemy();
	JuniorEnemy(JuniorEnemy& origin);
	~JuniorEnemy();

	virtual void onEnter();
	static JuniorEnemy* create(EnemyType enemytype,BulletType bulletype);

	virtual void update(float dt);
	void shootupdate(float dt);

	void shoot(BulletType bullettype);
	void getshot(BulletType bullettype);
	void shotresume(BulletType bullettype);

	int thunderring = 0;

	short droping = 0;
	//void getdroped();					//被水滴攻击
	void dropresume(float dt);

	int getblood();
private:
	EnemyType enemytype;
	BulletType bullettype;
	int blood;
	int initblood;

}; 

class EnemyRegister :public cocos2d::Node
{
public:
	static void create()
	{
		Instance = new EnemyRegister(); 
		Instance->retain();
	};

	static EnemyRegister* getInstance()
	{
		return Instance;
	};

	//cocos2d::Map < JuniorEnemy*, int > enemyregister;
	cocos2d::Vector<JuniorEnemy*> enemyregister;
private:
	static EnemyRegister* Instance;

};
