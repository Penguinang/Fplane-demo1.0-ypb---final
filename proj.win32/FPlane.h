#pragma once


#include "cocos2d.h"
using namespace std;
using namespace cocos2d;

#include"MyDefine.h"

class FPlane : public cocos2d::Sprite
{

	/*********************************************************************************
	*我的飞机
	*采用单例模式
	**********************************************************************************/
public:
	FPlane();
	~FPlane();

	static FPlane* create(Node* rootNode);
	static FPlane* getInstance();			//返回当前唯一存在的 FPlane 实例
	//Node* getFPlane();				//返回当前 FPlane 实例，在rootNode中存在的飞机实体
	Node* getParent();
	void shoot(BulletType);

	void getshot(BulletType bullettype);
	float getblood();
	float getskill();

	void thunder();						//雷电

	void protect();						//金身
	void endprotect();					//结束金身
	short protecting = 0;

	void drop();						//水滴
	void update(float dt);

	int score = 0;
private:
	static FPlane* FPlaneInstance;
	Node* fplane;
	Node* parent;

	int blood;
	int skill;
};

class Thunder : public cocos2d::Sprite
{
public:
	Thunder();
	void destroy(float dt);
	void attack();

	static Thunder* create();
};

class Drop :public cocos2d::Sprite
{
public:
	Drop();

	void attack();
	void destroy();

	static Drop* create();

	cocos2d::Vector<MoveTo*> attacklist;
};