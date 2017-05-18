#pragma once

#include "cocos2d.h"

class Introduction_1Scene :public cocos2d::Layer
{

public:

	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(Introduction_1Scene);

	void back();
	void right();
};


class Introduction_2Scene :public cocos2d::Layer
{

public:

	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(Introduction_2Scene);

	void back();
	void left();
	void right();
};


class Introduction_3Scene :public cocos2d::Layer
{

public:

	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(Introduction_3Scene);

	void back();
	void left();
};