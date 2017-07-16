#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include"Cards.h"
class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
	bool onTouchBegan(Touch *touch, Event *unused_event);

	void onTouchEnded(Touch *touch, Event *unused_event);

	bool OperationLeft();
	bool OperationRight();
	bool OperationUp();
	bool OperationDown();

	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	

	void operationCheck();

	
private:
	void createCards(Size size);
	void createCardNumber();
	void setScore();
	Cards * cardArray[4][4];
	int beginX, beginY, endX, endY;
	int score;
	LabelTTF * cardNumberTTF;
};

#endif // __HELLOWORLD_SCENE_H__
