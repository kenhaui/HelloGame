#include "Bullet.h"
USING_NS_CC;

Bullet::~Bullet()
{

}


Bullet* Bullet::create()
{
	Bullet* layer = new Bullet();
	layer->init();
	return layer;
}

bool Bullet::init()
{

	if (!Layer::init())
	{
		return false;
	}

	this->schedule( schedule_selector(Bullet::startShoot) );

	return true;
}

Plane* Bullet::initPlane()
{
	this->_plane = Plane::create();

	return this->_plane;
}

void Bullet::addBullet(float dt)
{
	bullet = Sprite::create( "GameScreen/bullet1.png " );

	auto bullet_body = PhysicsBody::createCircle( bullet->getContentSize().width /2 );
	bullet_body->setContactTestBitmask(true);
	bullet_body->setDynamic(true);

	bullet->setPhysicsBody( bullet_body );
	bullet->setTag( 3);
	this->addChild( bullet );
	//Point playerSpritePosition = _plane->playerSprite->getPosition();
	/*Point bulletPosition = Point(_plane->playerSpritePosition.x + _plane->playerSprite->getContentSize().width /2 , 
		_plane->playerSpritePosition.y);*/
	bullet->setPosition(_plane->bulletPosition);

	float length = Director::getInstance()->getWinSize().width + bullet->getContentSize().width/2 - _plane->bulletPosition.x;
	float velocity = 320/1;//320pixel/sec
	float realMoveDuration = length/velocity;


	auto actionMove = MoveTo::create(realMoveDuration, Point(Director::getInstance()->getWinSize().width + 
		bullet->getContentSize().width/2, _plane->bulletPosition.y));
	auto actionDone = CallFuncN::create( CC_CALLBACK_1( Bullet::bulletMoveFinished, this ) );

	auto sq = Sequence::create( actionMove, actionDone, NULL );

	bullet->runAction(sq);
}

void Bullet::bulletMoveFinished(Node* pSender)
{
	auto bullet = (Sprite*)pSender;
	this->removeChild( bullet, true );
}

void Bullet::startShoot( float delay)
{
	this->schedule(schedule_selector(Bullet::addBullet), 0.3f, kRepeatForever, delay );
}


void Bullet::stopShoot()
{
	this->unschedule( schedule_selector( Bullet::addBullet ) );
}
