#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include"Enemy.h"
#include"FPlane.h"

class missioninfoma :public cocos2d::Node
{
public:
	missioninfoma(bool hero, char* heroframe, EnemyType enemy1, int enemy1number, EnemyType enemy2, int enemy2number,
		EnemyType enemy3, int enemy3number) :HaveAHero(hero), heroframename(heroframe), enemy1(enemy1), enemy1number(enemy1number),
		enemy2(enemy2), enemy2number(enemy2number),
		enemy3(enemy3), enemy3number(enemy3number)
	{};


	EnemyType enemy1 = junior;
	int enemy1number = 0;

	EnemyType enemy2 = junior;
	int enemy2number = 0;

	EnemyType enemy3 = junior;
	int enemy3number = 0;

	bool HaveAHero = 0;
	string heroframename;
};


class RunGameScene :public cocos2d::Layer
{

public:

	static cocos2d::Scene* createScene();


	virtual bool init();

	CREATE_FUNC(RunGameScene);

	virtual void onEnter();

	int mapNumber = 3;

	void gameend(float dt);

private:
	bool keystate[4];
	int transformkey(cocos2d::EventKeyboard::KeyCode keycode);
	void update(float delta);
	void move(int dir);
	void showsmallmap();
	//cocos2d::Map < JuniorEnemy*, cocos2d::Sprite* > enemyregister;

	void loadmissioninfo();
	int mission;
	int endmission;
	//std::map<int, int> missioninfo;
	string smallmappic;

	time_t inittime;


	void nextroom();
	std::map<int, missioninfoma*> missionmap;

	/////////////////////////////////////////////	地图信息	///////////////////////////////////////////////////////
	void map();

	string BkcsbFileName;			//背景信息
	string BossFrameName;			//boss图片
	int BossBlood;					//boss血量
	EnemyType Enemy1;
	EnemyType Enemy2;
	EnemyType Enemy3;				//3种敌人图片

	string BGMFileName;				//BGM 路径

};
