#pragma once

#include "cocos2d.h"

class ExitScene :public cocos2d::Layer
{

public:

	static cocos2d::Scene* createScene();


	virtual bool init();


	CREATE_FUNC(ExitScene);

	void turn();
	void back();
	void enter();

}; 
