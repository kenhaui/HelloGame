#include "Hanhtinh.h"
#include "Definitions.h"
USING_NS_CC;


Hanhtinh::~Hanhtinh()
{

}

Hanhtinh* Hanhtinh::create()
{
	Hanhtinh* layer = new Hanhtinh();
	layer->init();
	return layer;

}


bool Hanhtinh::init()
{
	if (!Layer::init())
	{
		return false;

	}



	this->schedule( schedule_selector(Hanhtinh::spawn_hanhtinh), 1.0f );
	this->scheduleUpdate();
	return true;


}


void Hanhtinh::spawn_hanhtinh( float dt )
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	int hanhtinh_index = (rand() % 2) + 1;
	__String* hanhtinh_String = __String::createWithFormat("GameScreen/Asteroid_%i.png", hanhtinh_index);
	Sprite* tempHanhtinh = Sprite::create(hanhtinh_String->getCString());

	int yRandomPosition = (rand() % (int)(visibleSize.height - (tempHanhtinh->getContentSize().height / 2))) + 
		(tempHanhtinh->getContentSize().height / 2);

	//int xRandomPosition =  (rand() % (int)(visibleSize.width/2));

	tempHanhtinh->setPosition(Point( visibleSize.width, yRandomPosition ));
	hanhtinh.push_back(tempHanhtinh);

	auto hanhtinh_body = PhysicsBody::createCircle( hanhtinh[hanhtinh.size() -1 ]->getContentSize().width /2 );
	hanhtinh_body->setContactTestBitmask(true);
	hanhtinh_body->setDynamic(true);
	hanhtinh[hanhtinh.size() -1 ]->setPhysicsBody(hanhtinh_body);
	hanhtinh[hanhtinh.size() -1]->setTag(TAG_HANHTINH);
	this->addChild(hanhtinh[hanhtinh.size() - 1], -1);

}

void Hanhtinh::update( float dt )
{

}




