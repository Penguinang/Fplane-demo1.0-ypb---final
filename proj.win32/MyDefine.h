#pragma once

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

#define SMALLENEMY 100

enum BulletType
{
	normalbullet = 0,		//��ͨ�ӵ�
	seniorbullet = 1,		//�߼��ӵ�
	superbullet = 2,		//�����ӵ�	
	thunderskill = 3,		//����
	drop = 4,				//ˮ��
	enemy = 5,				//����
};

enum EnemyType
{
	junior = 0,
	senior = 1,
	super = 2
};;