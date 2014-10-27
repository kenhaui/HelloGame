#include "Plane.h"
USING_NS_CC;


Plane::~Plane()
{

}

Plane* Plane::create() 
{ 
	Plane *layer = new Plane();
	layer->init();
	return layer;
	
}

bool  Plane::init()
{
	if (!Layer::init())
	{
		return false;
	}

	// Them sprite player
	playerSprite = Sprite::create("GameScreen/Space_Pod.png");
	
	
	auto player_body = PhysicsBody::createCircle( playerSprite->getContentSize().width /2 );
	player_body->setContactTestBitmask(true);
	player_body->setDynamic(true);
	player_body->setGravityEnable(true);
	playerSprite->setPhysicsBody( player_body );
	playerSprite->setTag(1);

	playerSpritePosition = playerSprite->getPosition();
	bulletPosition = Point(playerSpritePosition.x + playerSprite->getContentSize().width /2 , 
		playerSpritePosition.y);

	this->addChild(playerSprite);

	/*auto move_Sprite = MoveTo::create(2, Point( 100, visibleSize.height /2 ));
	auto blink = Blink::create(1,3);

	auto sq = Sequence::create(move_Sprite, blink, NULL);

	playerSprite->runAction(sq);*/



	return true;
}

