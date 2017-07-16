#include "Cards.h"



Cards::Cards()
{
}


Cards::~Cards()
{
}
Cards * Cards::createCards(int number, int wight, int height, float CardX, float CardY) 
{
	Cards *enemy = new Cards();
	if (enemy&&enemy->init()) 
	{
		enemy->autorelease();
		enemy->enemyInit(number,wight,height,CardX,CardY);
		return enemy;
	}
	CC_SAFE_DELETE(enemy);
	return enemy;
}

bool Cards::init() 
{
	if (!Sprite::init())
	{
		return false;
	}
	return true;
}

void Cards::enemyInit(int number, int wight, int height, float CardX, float CardY)
{
	//��ʼ������
	this->number = number;
	//���뿨Ƭ������ɫ
	colorBackground = LayerColor::create(Color4B(200, 190, 180, 255), wight - 15, height - 15);//Ĭ�ϵ���ɫ�ʹ�С
	colorBackground->setPosition(Point(CardX, CardY));//λ��
	//�ж��������0����ʾ������Ͳ���ʾ
	if (number > 0)
	{
		labelCardNumber = LabelTTF::create(__String::createWithFormat("%i", number)->getCString(), "Consolas", 100);
		labelCardNumber->setPosition(Point(colorBackground->getContentSize().width / 2, colorBackground->getContentSize().height / 2));
		labelCardNumber->setTag(8);
		colorBackground->addChild(labelCardNumber);
	}
	else
	{
		labelCardNumber = LabelTTF::create("", "Consolas", 100);
		labelCardNumber->setPosition(Point(colorBackground->getContentSize().width / 2, colorBackground->getContentSize().height / 2));
		labelCardNumber->setTag(8);
		colorBackground->addChild(labelCardNumber);
	}
	this->addChild(colorBackground);
}

int Cards::getNumber()
{
	return number;
}

void Cards::setNumber(int num)
{
	number = num;
	if (num > 0)
	{
		labelCardNumber->setString(__String::createWithFormat("%i", number)->getCString());
	}
	else
	{
		labelCardNumber->setString("");
	}
	if (number >= 0)
	{
		labelCardNumber->setFontSize(100);
	}
	if (number >= 16)
	{
		labelCardNumber->setFontSize(90);
	}
	if (number >= 128)
	{
		labelCardNumber->setFontSize(60);
	}
	if (number >= 1024)
	{
		labelCardNumber->setFontSize(40);
	}
	if (number == 0)
	{
		colorBackground->setColor(Color3B(200, 190, 180));
	}
	if (number == 2)
	{
		colorBackground->setColor(Color3B(240, 230, 220));
	}
	if (number == 4)
	{
		colorBackground->setColor(Color3B(240, 220, 200));
	}
	if (number == 8)
	{
		colorBackground->setColor(Color3B(240, 180, 120));
	}
	if (number == 16)
	{
		colorBackground->setColor(Color3B(240, 140, 90));
	}
	if (number == 32)
	{
		colorBackground->setColor(Color3B(240, 120, 90));
	}
	if (number == 64)
	{
		colorBackground->setColor(Color3B(240, 90, 60));
	}
	if (number == 128)
	{
		colorBackground->setColor(Color3B(240, 90, 60));
	}
	if (number == 256)
	{
		colorBackground->setColor(Color3B(240, 200, 70));
	}
	if (number == 512)
	{
		colorBackground->setColor(Color3B(240, 200, 70));
	}
	if (number == 1024)
	{
		colorBackground->setColor(Color3B(0, 130, 0));
	}
	if (number == 2048)
	{
		colorBackground->setColor(Color3B(0, 130, 0));
	}
}



