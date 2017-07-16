#pragma once
//#include "C:\Cocos\Cocos2d-x\cocos2d-x-3.10\cocos\2d\CCSprite.h"
#include "cocos2d.h"
USING_NS_CC;
class Cards :
	public Sprite
{
public:
	Cards();
	~Cards();
	static Cards * createCards(int number, int wight, int height, float CardX, float CardY);
	virtual bool init();
	void enemyInit(int number, int wight, int height, float CardX, float CardY);
	int getNumber();
	void setNumber(int num);
private:
	int number;
	LabelTTF * labelCardNumber;
	LayerColor * colorBackground;

};

