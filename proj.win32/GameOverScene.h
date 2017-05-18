#pragma once


#include "cocos2d.h"
using namespace std;
using namespace cocos2d;
#include"MyDefine.h"

class GameOverScene :public cocos2d::Layer
{

public:

	static cocos2d::Scene* createScene();


	virtual bool init();


	CREATE_FUNC(GameOverScene);

	void end(Ref* psender);
	void restart(Ref* psender);
};