#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HomeScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(HomeScene);

	void left1();
	void left2();
	void left3();
	void left4();

	void right1();
	void right2();
	void right3();
	void right4();
	
	void enter1();
	void enter2();
	void enter3();
	void enter4();

};

#endif // __HELLOWORLD_SCENE_H__
