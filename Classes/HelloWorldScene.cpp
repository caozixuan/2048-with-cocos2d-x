#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    /**  you can create scene with following comment code instead of using csb file.
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    **/
    
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

    //auto rootNode = CSLoader::createNode("MainScene.csb");

    //addChild(rootNode);
	auto layerColorBG = LayerColor::create(Color4B(100, 90, 100, 255));
	this->addChild(layerColorBG);
	createCards(visibleSize);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);


	auto listenerKeyboard = EventListenerKeyboard::create();
	listenerKeyboard->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKeyboard, this);

	auto cardNumberTitle = LabelTTF::create("Score", "Consolas", 80);
	cardNumberTitle->setPosition(Point(visibleSize.width / 2 + 340, visibleSize.height / 2 + 130));
	addChild(cardNumberTitle);

	score = 0;
	cardNumberTTF = LabelTTF::create("0", "Consolas", 70);
	cardNumberTTF->setPosition(Point(visibleSize.width / 2 + 340, visibleSize.height / 2 + 60));
	addChild(cardNumberTTF);
	createCardNumber();
	createCardNumber();
    return true;
}

bool HelloWorld::onTouchBegan(Touch * touch, Event * unused_event)
{
	Point beginTouch = touch->getLocation();
	beginX = beginTouch.x;
	beginY = beginTouch.y;

	return true;
}

void HelloWorld::onTouchEnded(Touch * touch, Event * unused_event)
{
	Point endTouch = touch->getLocation();
	endX = beginX - endTouch.x;
	endY = beginY - endTouch.y;
	if (abs(endX)>abs(endY))
	{
		if (endX + 5 > 0)
		{
			OperationLeft();
			createCardNumber();
			operationCheck();
			setScore();
		}
		else
		{
			OperationRight();
			createCardNumber();
			operationCheck();
			setScore();
		}
	}
	else //否则是上下移动
	{
		if (endY + 5 > 0)
		{
			OperationDown();
			createCardNumber();
			operationCheck();
			setScore();
		}
		else
		{
			OperationUp();
			createCardNumber();
			operationCheck();
			setScore();
		}
	}
}

bool HelloWorld::OperationLeft()
{
    CCLOG("left");
	bool isMove = false;
	
	for (int y = 0;y < 4; y++)//行
	{
		for (int x = 0; x < 4; x++) {//列
			for (int x1 = x + 1; x1 < 4; x1++)
			{
				if (cardArray[x1][y]->getNumber() > 0)
				{
					if (cardArray[x][y]->getNumber() <= 0)
					{
						cardArray[x][y]->setNumber(cardArray[x1][y]->getNumber());
						cardArray[x1][y]->setNumber(0);
						x--;
						isMove = true;
					}
					//两个数字相同，进行相加
					else if (cardArray[x][y]->getNumber() == cardArray[x1][y]->getNumber())
					{
						cardArray[x][y]->setNumber(cardArray[x][y]->getNumber() * 2);
						cardArray[x1][y]->setNumber(0);
						score += cardArray[x][y]->getNumber();
						isMove = true;
					}
				}
				break;
			}
		}
	}


    return isMove;
}

bool HelloWorld::OperationRight()
{
    CCLOG("right");

	bool isMove = false;

	for (int y = 0; y < 4; y++)//行
	{
		for (int x = 3; x >=0; x--) {//列
			for (int x1 = x - 1; x1 >= 0; x1--)
			{
				if (cardArray[x1][y]->getNumber() > 0)
				{
					if (cardArray[x][y]->getNumber() <= 0)
					{
						cardArray[x][y]->setNumber(cardArray[x1][y]->getNumber());
						cardArray[x1][y]->setNumber(0);
						x++;
						isMove = true;
					}
					//两个数字相同，进行相加
					else if (cardArray[x][y]->getNumber() == cardArray[x1][y]->getNumber())
					{
						cardArray[x][y]->setNumber(cardArray[x][y]->getNumber() * 2);
						cardArray[x1][y]->setNumber(0);
						score += cardArray[x][y]->getNumber();
						isMove = true;
					}
				}
				break;
			}
		}
	}
 	return isMove;
}

bool HelloWorld::OperationUp()
{
	CCLOG("up");

	bool isMove = false;

	for (int x = 0; x < 4; x++)//行
	{
		for (int y=3; y>=0; y--) 
		{//列
			for (int y1 = y -1; y1 >= 0; y1--)
			{
				if (cardArray[x][y1]->getNumber() > 0)
				{
					if (cardArray[x][y]->getNumber() <= 0)
					{
						cardArray[x][y]->setNumber(cardArray[x][y1]->getNumber());
						cardArray[x][y1]->setNumber(0);
						y++;
						isMove = true;
					}
					//两个数字相同，进行相加
					else if (cardArray[x][y]->getNumber() == cardArray[x][y1]->getNumber())
					{
						cardArray[x][y]->setNumber(cardArray[x][y]->getNumber() * 2);
						cardArray[x][y1]->setNumber(0);
						score += cardArray[x][y]->getNumber();
						isMove = true;
					}
				}
				break;
			}
		}
	}
	return isMove;
}

bool HelloWorld::OperationDown()
{
	CCLOG("down");

	bool isMove = false;

	for (int x = 0; x < 4; x++)//行
	{
		for (int y = 0; y<4; y++) {//列
			for (int y1 = y - 1; y1 >= 0; y1--)
			{
				if (cardArray[x][y1]->getNumber() > 0)
				{
					if (cardArray[x][y]->getNumber() <= 0)
					{
						cardArray[x][y]->setNumber(cardArray[x][y1]->getNumber());
						cardArray[x][y1]->setNumber(0);
						y--;
						isMove = true;
					}
					//两个数字相同，进行相加
					else if (cardArray[x][y]->getNumber() == cardArray[x][y1]->getNumber())
					{
						cardArray[x][y]->setNumber(cardArray[x][y]->getNumber() * 2);
						cardArray[x][y1]->setNumber(0);
						score += cardArray[x][y]->getNumber();
						isMove = true;
					}
				}
				break;
			}
		}
	}
	return isMove;
}

void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event)
{
	switch (keyCode)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_W:
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_W:
	case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
	{
		OperationUp();
		createCardNumber();
		operationCheck();
		setScore();
	}
	break;

	case cocos2d::EventKeyboard::KeyCode::KEY_S:
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_S:
	case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	{
		OperationDown();
		createCardNumber();
		operationCheck();
		setScore();
	}
	break;

	case cocos2d::EventKeyboard::KeyCode::KEY_A:
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_A:
	case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	{
		OperationLeft();
		createCardNumber();
		operationCheck();
		setScore();
	}
	break;

	case cocos2d::EventKeyboard::KeyCode::KEY_D:
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_D:
	case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	{
		OperationRight();
		createCardNumber();
		operationCheck();
		setScore();
	}
	break;
	default:
		break;
	}
}

void HelloWorld::setScore()
{

	cardNumberTTF->setString(__String::createWithFormat("%i", score)->getCString());
}

void HelloWorld::operationCheck()
{
	bool isGameOver = true;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if ((cardArray[y][x]->getNumber() == 0) || 
				(x < 3 && cardArray[x][y]->getNumber() == cardArray[x + 1][y]->getNumber())    ||
				(x > 0 && cardArray[x][y]->getNumber() == cardArray[x - 1][y]->getNumber())   ||
				(y < 3 && cardArray[x][y]->getNumber() == cardArray[x][y+1]->getNumber()) ||
				(y > 0 && cardArray[x][y]->getNumber() == cardArray[x][y-1]->getNumber()))
			{
				isGameOver = false;
			}
		}
	}
	if (isGameOver) {
		log("GameOver!!!");
		Director::getInstance()->replaceScene(TransitionCrossFade::create(1, HelloWorld::createScene()));
	}
}


void HelloWorld::createCards(Size size)
{
	//求出单元格的宽和高
	int cardSize = (size.height- 36) / 4;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++) {
			Cards *card = Cards::createCards(0, cardSize, cardSize, cardSize*i + 80, cardSize*j + 20);
			cardArray[i][j] = card;
			addChild(card);
		}
	}
}

void HelloWorld::createCardNumber()
{
	int i = CCRANDOM_0_1() * 4;
	int j = CCRANDOM_0_1() * 4;

	if (cardArray[i][j]->getNumber() > 0)
	{
		createCardNumber();
	}
	else
	{
		cardArray[i][j]->setNumber(CCRANDOM_0_1() * 10 < 1 ? 4 : 2);
	}
}
