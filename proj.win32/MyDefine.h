#pragma once

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

#define SMALLENEMY 100

enum BulletType
{
	normalbullet = 0,		//普通子弹
	seniorbullet = 1,		//高级子弹
	superbullet = 2,		//超级子弹	
	thunderskill = 3,		//闪电
	drop = 4,				//水滴
	enemy = 5,				//敌人
};

enum EnemyType
{
	junior = 0,
	senior = 1,
	super = 2
};;