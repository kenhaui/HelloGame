#include "Plane.h"
#include "Definitions.h"
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
	playerSprite = Sprite::create("GameScreen/hero1.png");
	
	
	auto player_body = PhysicsBody::createCircle( playerSprite->getContentSize().width /2 );
	player_body->setContactTestBitmask(true);
	player_body->setDynamic(true);
	player_body->setGravityEnable(true);
	playerSprite->setPhysicsBody( player_body );
	playerSprite->setTag(TAG_PLAYER);

	Vector<SpriteFrame*> aniFrame;
			aniFrame.reserve(4);
			aniFrame.pushBack( SpriteFrame::create("GameScreen/hero1.png", Rect(0, 0, 126, 105)) );
			aniFrame.pushBack( SpriteFrame::create("GameScreen/hero2.png", Rect(0, 0, 126, 105)) );
			/*aniFrame.pushBack( SpriteFrame::create("move_3.png", Rect(0, 0, 100, 160)) );
			aniFrame.pushBack( SpriteFrame::create("move_.png", Rect(0, 0, 100, 160)) );*/

			Animation *animation = Animation::createWithSpriteFrames(aniFrame, 0.1);
			Animate *animate = Animate::create(animation);
			playerSprite->runAction( RepeatForever::create(animate) );


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

