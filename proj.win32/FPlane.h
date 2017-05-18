#pragma once


#include "cocos2d.h"
using namespace std;
using namespace cocos2d;

#include"MyDefine.h"

class FPlane : public cocos2d::Sprite
{

	/*********************************************************************************
	*�ҵķɻ�
	*���õ���ģʽ
	**********************************************************************************/
public:
	FPlane();
	~FPlane();

	static FPlane* create(Node* rootNode);
	static FPlane* getInstance();			//���ص�ǰΨһ���ڵ� FPlane ʵ��
	//Node* getFPlane();				//���ص�ǰ FPlane ʵ������rootNode�д��ڵķɻ�ʵ��
	Node* getParent();
	void shoot(BulletType);

	void getshot(BulletType bullettype);
	float getblood();
	float getskill();

	void thunder();						//�׵�

	void protect();						//����
	void endprotect();					//��������
	short protecting = 0;

	void drop();						//ˮ��
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