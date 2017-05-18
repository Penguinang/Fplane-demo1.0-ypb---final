#pragma once

#include "cocos2d.h"

class SelectMapScene :public cocos2d::Layer
{
	
public:

	static cocos2d::Scene* createScene();


	virtual bool init();

	//virtual void onEnter();
	int mapNumber = 1;

	CREATE_FUNC(SelectMapScene);

	void menuCloseCallback(Ref* pSender);

	void addzero(Ref* pSender);
	void addone(Ref* pSender);
	void addtwo(Ref* pSender);
	void addthree(Ref* pSender);
	void addfour(Ref* pSender);
};