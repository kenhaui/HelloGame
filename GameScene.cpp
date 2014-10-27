#include "GameScene.h"
#include "PauseMenuScene.h"
#include "GameOverScene.h"
#include "Definitions.h"

USING_NS_CC;


Level GameScene::level = EASY;



Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask( PhysicsWorld::DEBUGDRAW_ALL );
	scene->getPhysicsWorld()->setGravity( Vect( 0.0f, 0.0f ) );
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();
	layer->setPhysicsWorld( scene->getPhysicsWorld() );

    // add layer as a child to scene
	 scene->addChild(layer);
	 //add layer Plane
	 scene->addChild( layer->initPlane(), 1 );

	 scene->addChild( layer->initHanhtinh(),2 );


    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
	level = EASY;

	visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

    auto pauseItem = MenuItemImage::create( "GameScreen/Pause_Button.png",
									"GameScreen/Pause_Button(Click).png",
									CC_CALLBACK_1(GameScene::GoToPauseMenuScene, this));

	pauseItem->setPosition( Point( pauseItem->getContentSize().width - pauseItem->getContentSize().width /4 + origin.x,
		visibleSize.height - pauseItem->getContentSize().height + pauseItem->getContentSize().width /4 + origin.y ) );

	auto menu = Menu::create( pauseItem, NULL );
	menu->setPosition( Point::ZERO );
	this->addChild( menu, 1000 );


	for (int i = 0; i< 2 ;i++)
	{
		spriteBackgroundArray[i] = Sprite::create("GameScreen/Game_Screen_Background.png");
		spriteBackgroundArray[i]->setPosition(Point((-1 * visibleSize.width * i) + (visibleSize.width /2 ), ( visibleSize.height/2)));
		this->addChild(spriteBackgroundArray[i], -2 );

		float rX = visibleSize.width / spriteBackgroundArray[i]->getContentSize().width;
		float rY = visibleSize.height / spriteBackgroundArray[i]->getContentSize().height;

		// set the scaling factor to the background image

		spriteBackgroundArray[i]->setScaleX( rX );
		spriteBackgroundArray[i]->setScaleY( rY );
	}

	
	

	
	this->scheduleUpdate();

	// moi 1s thi sinh ra cac hanh tinh
	//this->schedule( schedule_selector(GameScene::addEnemy));
	this->schedule(schedule_selector(GameScene::addEnemy),2.0f);
	//this->schedule( schedule_selector(GameScene::spawn_pipe), 1.0 );

	
	//this->schedule( schedule_selector(GameScene::spawn_hanhtinh), 1.0f );
	
	this->schedule( schedule_selector(GameScene::startShoot) );
//	this->schedule( schedule_selector(GameScene::startMutiShoot) );
	this->schedule ( schedule_selector(GameScene::addVatPham), 15 );
	//this->schedule ( schedule_selector(GameScene::bulletBossMoveFinished), 0.3f, kRepeatForever, 0 );
	//this->schedule( schedule_selector(GameScene::startShootBoss), 1 );

	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = CC_CALLBACK_2( GameScene::onTouchesBegan, this );
	listener->onTouchesMoved = CC_CALLBACK_2( GameScene::onTouchesMoved, this );
	listener->onTouchesEnded = CC_CALLBACK_2( GameScene::onTouchesEnded, this );

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority( listener, this );

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1( GameScene::onContactBegin, this );
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	//Label tinh mang
	_live = 3;
	_liveEnemy =30;

	
	
	

	__String *templeLive = __String::createWithFormat("%i", _live);
	liveLabel = Label::createWithTTF(templeLive->getCString(), "fonts/Marker Felt.ttf", visibleSize.height* 0.1f);
	liveLabel->setColor( Color3B::WHITE );
	liveLabel->setPosition( Point(liveLabel->getContentSize().width, visibleSize.height/2 + liveLabel->getContentSize().height) );
	this->addChild( liveLabel, 1000 );
	

	//Label tinh diem 

	score = 0;

	__String *templeScore = __String::createWithFormat("%i", score);
	scoreLabel = Label::createWithTTF(templeScore->getCString(), "fonts/Marker Felt.ttf", visibleSize.height* 0.1f);
	scoreLabel->setColor( Color3B::GRAY );
	scoreLabel->setPosition( Point( visibleSize.width - scoreLabel->getContentSize().width , 
		visibleSize.height - scoreLabel->getContentSize().height ) );
	this->addChild( scoreLabel, 1000 );



	isShowBoss = true;

    return true;
}

//Ham khoi tao Plane
Plane* GameScene::initPlane()
{
	this->plane = Plane::create();
	plane->playerSprite->setPosition(Point(0, visibleSize.height /2 ));
	auto move_Sprite = MoveTo::create(2, Point( 100, visibleSize.height /2 ));
	auto blink = Blink::create(1,3);

	auto sq = Sequence::create(move_Sprite, blink, NULL);

	plane->playerSprite->runAction(sq);
	return this->plane;

}
//Ham khoi tao cac hah tinh
Hanhtinh* GameScene::initHanhtinh()
{
	this->_hanhtinh = Hanhtinh::create();
	return this->_hanhtinh;
}


void GameScene::GoToPauseMenuScene( cocos2d::Ref* sender )
{
	auto scene = PauseMenuScene::createScene();
	Director::getInstance()->pushScene( TransitionMoveInR::create(1, scene) );
}
void GameScene::GoToGameOverScene( cocos2d::Ref* sender )
{
	auto scene = GameOverScene::createScene( score );
	Director::getInstance()->replaceScene( scene );
}

void GameScene::update( float dt )
{

	if (level == EASY && score >= 100)
	{
		level = MIDDLE;
	}
	else if (level == MIDDLE && score >= 300)
	{
		level = HARD;
	}


	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	/*
	if (score == 20 )
	{
		startMutiShoot();
		stopShoot();
	}
	else
	{
		startShoot();
	}*/
	

	for (int i = 0; i < 2; i ++)
	{
		if (spriteBackgroundArray[i]->getPosition().x > visibleSize.width + (visibleSize.width / 2)-1)
		{
			spriteBackgroundArray[i]->setPosition(Point( (-1 * visibleSize.width) + (visibleSize.width /2 ), ( visibleSize.height/2)));
		}
	}

	for (int i = 0 ; i < 2; i ++)
	{
		spriteBackgroundArray[i]->setPosition(Point(spriteBackgroundArray[i]->getPosition().x  + (0.1 * visibleSize.width * dt), 
			spriteBackgroundArray[i]->getPosition().y));
	}


	for( int i = 0 ; i < _hanhtinh->hanhtinh.size(); i++)
	{
	
			//Di chuyen cac hanh tinh theo truc x man hinh
			

			switch (GameScene::getCurLevel())
			{
			case EASY:
				_hanhtinh->hanhtinh[i]->setPosition(Point(_hanhtinh->hanhtinh[i]->getPosition().x  +
					(-0.25 * visibleSize.width * dt) , _hanhtinh->hanhtinh[i]->getPosition().y  ));
				
				break;
			case MIDDLE:

				_hanhtinh->hanhtinh[i]->setPosition(Point(_hanhtinh->hanhtinh[i]->getPosition().x  + 
					(-0.3 * visibleSize.width * dt) , _hanhtinh->hanhtinh[i]->getPosition().y  ));
				break;
				
			case HARD:
				_hanhtinh->hanhtinh[i]->setPosition(Point(_hanhtinh->hanhtinh[i]->getPosition().x  + 
					(-0.4 * visibleSize.width * dt) , _hanhtinh->hanhtinh[i]->getPosition().y  ));
				break;

			default:
				_hanhtinh->hanhtinh[i]->setPosition(Point(_hanhtinh->hanhtinh[i]->getPosition().x  + 
					(-0.25 * visibleSize.width * dt) , _hanhtinh->hanhtinh[i]->getPosition().y  ));
				break;
			}
			//hanhtinh[i]->setPosition( Point(hanhtinh[i]->getPosition().x , hanhtinh[i]->getPosition().y + (+0.25 * visibleSize.height *dt) ) );
		
		//kiem tra hanh tinh di chuyen khoi man hinh
		if (_hanhtinh->hanhtinh[i]->getPosition().x > visibleSize.width * 2)
		{
			this->removeChild(_hanhtinh->hanhtinh[i]);// xoa bo hanh tinh
			_hanhtinh->hanhtinh.erase(_hanhtinh->hanhtinh.begin() + i);// xoa khoi vector
		}
	
		//if (score >=100) may bay xuat hien theo hai huong cua man hinh

	}

	
	
		

	//if ((score >=10) && (score <=11))
	//{

	//	//Add boss
	//	boss = Sprite::create("GameScreen/enemy3.png");
	//	boss->setPosition( Point( visibleSize.width + 150, visibleSize.height/2 ) );
	//	auto body_boss = PhysicsBody::createCircle( boss->getContentSize().width/2 );
	//	body_boss->setContactTestBitmask(true);
	//	body_boss->setDynamic(true);
	//	boss->setPhysicsBody( body_boss );
	//	boss->setTag( 4 );
	//	this->addChild( boss, 100 );
	//	auto boss_move = MoveTo::create( 3, Point( visibleSize.width- boss->getContentSize().width/2 , visibleSize.height/2 ) );
	//	boss->runAction( boss_move );

	//}


			
	if (_live <= 0) { // Kiểm tra không còn mạng nào thì game Over
		plane->playerSprite->stopAllActions();
		plane->playerSprite->setVisible(false);
		mWorld->removeBody(plane->playerSprite->getPhysicsBody());
		auto scene = GameOverScene::createScene( score );
		Director::getInstance()->replaceScene( TransitionMoveInR::create(1,scene));// Game Over
	} 


	

	
	if (_liveEnemy <=0 )
	{
		


		//boss->setVisible(false);
		Vector<SpriteFrame*> aniFrame;
			aniFrame.reserve(5);
			aniFrame.pushBack( SpriteFrame::create("GameScreen/enemy3_down1.png", Rect(0, 0, 300, 200)) );
			aniFrame.pushBack( SpriteFrame::create("GameScreen/enemy3_down2.png", Rect(0, 0, 300, 200)) );
			/*aniFrame.pushBack( SpriteFrame::create("GameScreen/enemy3_down3.png", Rect(0, 0, 216, 165)) );
			aniFrame.pushBack( SpriteFrame::create("GameScreen/enemy3_down4.png", Rect(0, 0, 216, 165)) );
			aniFrame.pushBack( SpriteFrame::create("GameScreen/enemy3_down5.png", Rect(0, 0, 216, 165)) );
			*/
			Animation *animation = Animation::createWithSpriteFrames(aniFrame, 0.1);
			Animate *animate = Animate::create(animation);

			Hide *hide = Hide::create();
			DelayTime *dl = DelayTime::create(3);
			boss->runAction(Sequence::create(animate, dl,  NULL));




		mWorld->removeBody(boss->getPhysicsBody());
		//mWorld->removeBody(bulletBoss->getPhysicsBody());
		//boss->stopAllActions();
	}


}


//Phuong thuc spawn may bay
void GameScene::addEnemy(float dt )
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	auto tempEnemy = Sprite::create( "GameScreen/enemy1.png" );


	tempEnemy->setPosition(Point( visibleSize.width /2 +100, -30 ));
	enemy.push_back(tempEnemy);

	auto enemy_body = PhysicsBody::createCircle( enemy[enemy.size() -1 ]->getContentSize().width/2 );
	enemy_body->setContactTestBitmask(true);
	enemy_body->setDynamic(false);
	enemy[enemy.size() -1 ]->setPhysicsBody( enemy_body );
	this->addChild( enemy[enemy.size() -1 ] );
	enemy[enemy.size() -1]->setTag(TAG_ENEMY);
		
		PhysicsBody* body_boss;
		switch (GameScene::getCurLevel())
		{
		case EASY:
			break;
		case MIDDLE:
	
				if (isShowBoss)
				{
					boss = Sprite::create("GameScreen/enemy3.png");
					boss->setPosition(visibleSize.width - boss->getContentSize().width/2 , visibleSize.height/2);
					body_boss = PhysicsBody::createCircle(boss->getContentSize().width/2);
					body_boss->setContactTestBitmask(true);
					boss->setPhysicsBody( body_boss );
					boss->setTag(TAG_BOSS);
					this->addChild( boss, 100);
					startShootBoss();
					boss_move = MoveBy::create(3, Point( -100, 0 ));
					boss->runAction(boss_move);
				}
				else
				{
					break;
				}
				isShowBoss =!isShowBoss;
			
			
			
			/*boss_move = MoveTo::create(1, Point( visibleSize.width -boss->getContentSize().width/2, visibleSize.height/2 ));
			boss->runAction( boss_move );*/
			break;
		case HARD:

			if (isShowBoss)
				{
					boss = Sprite::create("GameScreen/enemy3.png");
					boss->setPosition(visibleSize.width - boss->getContentSize().width/2 , visibleSize.height/2);
					body_boss = PhysicsBody::createCircle(boss->getContentSize().width/2);
					body_boss->setContactTestBitmask(true);
					boss->setPhysicsBody( body_boss );
					boss->setTag(TAG_BOSS);
					this->addChild( boss, 100);
					startShootBoss();
					boss_move = MoveBy::create(3, Point( -100, 0 ));
					boss->runAction(boss_move);
				}
				else
				{
					break;
				}
				isShowBoss =!isShowBoss;

			break;
		default:
			break;
		}

	

		for (int i= 0; i < enemy.size() ;i++)
		{
			if ( (score >=5 ) && ( score <=20) ){

				
				ccBezierConfig config;
				config.controlPoint_1 = Point(-600, 300);
				config.controlPoint_2 = Point(-600, 350 );
				config.endPosition = Point(visibleSize.width/2, visibleSize.height + 200);
				auto bz = BezierBy::create( dt, config);
				auto delay = DelayTime::create(4);
				enemy[i]->runAction(Sequence::create(bz, delay, NULL));
				/*enemy[i]->setPosition( Point( enemy[i]->getPosition().x + (-0.25 * visibleSize.width * dt), enemy[i]->getPosition().y ) );
				enemy[i]->setPosition( Point( enemy[i]->getPosition().x, enemy[i]->getPosition().y + (+0.25 * visibleSize.height* dt) ) );*/

			if (( enemy[i]->getPosition().x > visibleSize.width*2 ) || ( score ==20 ))
			{
				this->removeChild( enemy[i], true );
				enemy.erase(enemy.begin() + i);
			}

		}
			
		}
		
	

}

void GameScene::addButlletBoss_1( float dt )
{
	bulletBoss = Sprite::create( "GameScreen/bomb.png" );
	this->addChild( bulletBoss );
	Point bossPosition = boss->getPosition();
	Point bulletBossPosition = Point(bossPosition.x - boss->getContentSize().width /2 , bossPosition.y);

	bulletBoss->setPosition(bulletBossPosition);

	float length = Director::getInstance()->getWinSize().width + bulletBoss->getContentSize().width/2 + bulletBossPosition.x;
	float velocity = 320/1;//320pixel/sec
	float realMoveDuration = length/velocity;

	//
	auto actionMove = MoveTo::create(realMoveDuration, Point(-300,bulletBossPosition.y));
	auto actionDone = CallFuncN::create( CC_CALLBACK_1( GameScene::bulletBossMoveFinished, this ) );

	auto sq = Sequence::create( actionMove, actionDone, NULL );

	bulletBoss->runAction(sq);

}

Point GameScene::touchTopoint( Touch* touch )
{
	// convert the touch object to a position in our cocos2d space
	return Director::getInstance()->convertToGL( touch->getLocationInView() );
}

bool GameScene::touchingSprite( Touch* touch )
{
	return (this->plane->playerSprite->getPosition().getDistance(this->touchTopoint(touch)) < 70.0f);
}


void GameScene::onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event)
{
	// reset touch offset

	touchOffset = Point::ZERO;

	for (auto touch : touches)
	{
		if (touch && this->touchingSprite(touch))
		{
			touchOffset = plane->playerSprite->getPosition() - touchTopoint(touch);
		}
	}

}

void GameScene::onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event)
{
	for (auto touch : touches)
	{
		if (touch && touchOffset.x && touchOffset.y)
		{
			this->plane->playerSprite->setPosition( this->touchTopoint(touch) + this->touchOffset );
		}
	}

}

void GameScene::onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event)
{
	for (auto touch : touches)
	{
		if (touch && touchOffset.x && touchOffset.y)
		{
			this->plane->playerSprite->setPosition( this->touchTopoint(touch) + this->touchOffset );
		}
	}


}

void GameScene::spawn_pipe( float dt )
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	auto topPipe = Sprite::create( "GameScreen/pipe_top.png" );
	auto bottomPipe = Sprite::create( "GameScreen/pipe_bottom.png" );

	auto toppipe_body = PhysicsBody::createEdgeBox( topPipe->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT );
	toppipe_body->setContactTestBitmask(true);
	topPipe->setPhysicsBody( toppipe_body );


	//auto topPipePosition = (visibleSize.height  ) + ( topPipe->getContentSize().height/2 );

	topPipe->setPosition( Point(visibleSize.width/2 + 300, visibleSize.height - 30) );

	bottomPipe->setPosition( Point( visibleSize.width/2 + 300, 30) );

	this->addChild(topPipe);
	this->addChild(bottomPipe);

	auto topPipeAction = MoveBy::create( 0.01 * visibleSize.width, Point( -visibleSize.width *1.5, 0 ) );
	auto bottomPipeAction = MoveBy::create( 0.01 * visibleSize.width, Point( -visibleSize.width* 1.5, 0 ) );

	topPipe->runAction( topPipeAction );
	bottomPipe->runAction( bottomPipeAction );
}

void GameScene::startShoot( float delay )
{
	
	this->schedule(schedule_selector(GameScene::addBullet), 0.3f, kRepeatForever, delay );
}

void GameScene::stopShoot()
{

	this->unschedule( schedule_selector(GameScene::addBullet) );
}

void GameScene::addBullet(float dt)
{
	bullet = Sprite::create( "GameScreen/bullet1.png " );
	
	auto bullet_body = PhysicsBody::createCircle( bullet->getContentSize().width /2 );
	bullet_body->setContactTestBitmask(true);
	bullet_body->setDynamic(true);

	bullet->setPhysicsBody( bullet_body );
	bullet->setTag(TAG_BULLET);
	this->addChild( bullet );
	Point playerSpritePosition = plane->playerSprite->getPosition();
	Point bulletPosition = Point(playerSpritePosition.x + plane->playerSprite->getContentSize().width /2 , playerSpritePosition.y);
	bullet->setPosition(bulletPosition);
	/*float velocity;
	switch (GameScene::getCurLevel())
	{
	case EASY:
		velocity = 320/1;
		break;
	case MIDDLE:
		velocity = 620/1;
		break;
	case HARD:
		velocity = 100/1;

	default:
		velocity = 320/1;
		break;
	}*/


	float length = Director::getInstance()->getWinSize().width + bullet->getContentSize().width/2 - bulletPosition.x;
	float velocity = 320/1;//320pixel/sec
	float realMoveDuration = length/velocity;


	


	auto actionMove = MoveTo::create(realMoveDuration, Point(Director::getInstance()->getWinSize().width + 
		bullet->getContentSize().width/2,bulletPosition.y));
	auto actionDone = CallFuncN::create( CC_CALLBACK_1( GameScene::bulletMoveFinished, this ) );

	auto sq = Sequence::create( actionMove, actionDone, NULL );

	bullet->runAction(sq);

	}


void GameScene::startShootBoss( float delay)
{
	this->schedule( schedule_selector(GameScene::addButlletBoss_1), 0.3f, kRepeatForever, delay );
}

void GameScene::stopShootBoss()
{
	this->unschedule( schedule_selector(GameScene::addButlletBoss_1) );
}


void GameScene::bulletBossMoveFinished( Node* pSender )
{
	auto bulletBoss =(Sprite*)pSender;
	this->removeChild( bulletBoss, true );
}



void GameScene::bulletMoveFinished(Node* pSender)
{
	auto bullet =(Sprite*)pSender;
	
	
	this->removeChild( bullet, true );

}



void GameScene::startMutiShoot( float delay )
{
	this->schedule(schedule_selector(GameScene::addbutlletMuti), 0.3f,kRepeatForever, delay);
}

void GameScene::stopMutiShoot()
{
	this->unschedule(schedule_selector(GameScene::addbutlletMuti));
}

void GameScene::addbutlletMuti( float dt )
{
	mutiBulletLeft = Sprite::create("GameScreen/bullet2.png ");
	mutiBulletRight = Sprite::create("GameScreen/bullet2.png ");

	auto body_bulletLeft = PhysicsBody::createCircle(mutiBulletLeft->getContentSize().width/2);
	body_bulletLeft->setContactTestBitmask(true);
	mutiBulletLeft->setPhysicsBody( body_bulletLeft );


	auto body_bulletRight = PhysicsBody::createCircle(mutiBulletRight->getContentSize().width/2);
	body_bulletRight->setContactTestBitmask(true);
	mutiBulletRight->setPhysicsBody( body_bulletRight );

	this->addChild( mutiBulletLeft );
	this->addChild( mutiBulletRight );

	auto planePosition = plane->playerSprite->getPosition();
	auto bulletLeftPosition = Point(planePosition.x+33, planePosition.y-35);
	auto bulletRightPosition = Point(planePosition.x+33, planePosition.y+35);
	mutiBulletLeft->setPosition(bulletLeftPosition);
	mutiBulletRight->setPosition(bulletRightPosition);

	float length = Director::getInstance()->getWinSize().width + mutiBulletLeft->getContentSize().width/2-bulletLeftPosition.x;
	float velocity = 420/1;//420pixel/sec
	float realMoveDuration = length/velocity;


	auto actionLeftMove = MoveTo::create(realMoveDuration, Point( Director::getInstance()->getWinSize().width +
		mutiBulletLeft->getContentSize().width/2 , bulletLeftPosition.y));
	auto actionLeftDone = CallFuncN::create(CC_CALLBACK_1(GameScene::mutiBulletMoveFinished, this));
	auto sequenceLeft = Sequence::create(actionLeftMove, actionLeftDone, nullptr);

	auto actionRightMove = MoveTo::create(realMoveDuration, Point(  Director::getInstance()->getWinSize().width+
		mutiBulletRight->getContentSize().width/2, bulletRightPosition.y));
	auto actionRightDone = CallFuncN::create(CC_CALLBACK_1(GameScene::mutiBulletMoveFinished, this));
	auto sequenceRight = Sequence::create(actionRightMove, actionRightDone, nullptr);


	mutiBulletLeft->runAction(sequenceLeft );
	mutiBulletRight->runAction(sequenceRight );

}

void GameScene::mutiBulletMoveFinished( Node* pSender )
{
	mutiBulletLeft = (Sprite*)pSender;
	mutiBulletRight = (Sprite*)pSender;
	this->removeChild( mutiBulletLeft,true );
	this->removeChild( mutiBulletRight, true );
}


void GameScene::addVatPham( float dt )
{
	vatPham = Sprite::create("GameScreen/ufo1.png");

	auto vatPhamSize = vatPham->getContentSize();
	auto winSize = Director::getInstance()->getWinSize();
	int minX = vatPhamSize.width/2;
	int maxX = winSize.width - vatPhamSize.width/2;
	int rangeX = maxX - minX;
	int actualX = (rand()%rangeX) + minX;


	vatPham->setPosition(Point(actualX, winSize.height +  vatPhamSize.height/2));
	auto vatpham_body = PhysicsBody::createCircle( vatPham->getContentSize().width/2 );
	vatpham_body->setContactTestBitmask(true);
	vatpham_body->setDynamic(true);
	vatPham->setPhysicsBody( vatpham_body );
	this->addChild(vatPham);
	vatPham->setTag(TAG_VATPHAM);
	auto move1 = MoveBy::create(1, Point(0, -150));
	auto move2 = MoveBy::create(0.5f, Point(0, 100));
	auto move3 = MoveBy::create(2, Point(0, 0 - winSize.height - vatPhamSize.height/2));

	auto moveDone = CallFuncN::create(CC_CALLBACK_1(GameScene::vatPhamMoveFinished, this));

	auto sequence = Sequence::create(move1, move2, move3, moveDone, nullptr);
	vatPham->runAction(sequence);
}

void GameScene::vatPhamMoveFinished( Node* pSender )
{
	vatPham = (Sprite*)pSender;
	this->removeChild(vatPham, true);
	
}

bool GameScene::onContactBegin( const PhysicsContact& contact )
{
	
	//lay doi tuong va cham thu 1
	auto bullet = (Sprite*)contact.getShapeA()->getBody()->getNode();
	int tag = bullet->getTag();

	auto target = (Sprite*)contact.getShapeB()->getBody()->getNode();

	int tag1 = target->getTag();


	//Va cham giua dan don va hanh tinh
	if ((tag == TAG_BULLET & tag1 ==TAG_HANHTINH )||( tag ==TAG_HANHTINH & tag1 ==TAG_BULLET))
	{
		CCLOG("va cham");
		Vector<SpriteFrame*> aniFrame;
		aniFrame.reserve(4);
		aniFrame.pushBack( SpriteFrame::create("GameScreen/enemy1_down3.png", Rect(0, 0, 70, 100)) );
		aniFrame.pushBack( SpriteFrame::create("GameScreen/enemy1_down3.png", Rect(0, 0, 70, 100)) );
		Animation *animation = Animation::createWithSpriteFrames(aniFrame, 0.1);
		Animate *animate = Animate::create(animation);
		
		//target->runAction(animate);
		auto hide = Hide::create();

		bullet->runAction( Sequence::create(animate, hide, NULL) );

		mWorld->removeBody( bullet->getPhysicsBody() );
		//bullet->setVisible(false);
		
		mWorld->removeBody(target->getPhysicsBody());
		//target->setVisible(false);
		target->runAction( Sequence::create(animate, hide, NULL) );
		score++;
		getCurLevel();
		__String *tempScore = __String::createWithFormat( "%i",score  );
		scoreLabel->setString( tempScore->getCString() );

		
	}

	//Va cham giua dan don va may bay dich
	if((tag==TAG_BULLET && tag1==TAG_ENEMY)||(tag==TAG_ENEMY && tag1==TAG_BULLET))
	{
		mWorld->removeBody( bullet->getPhysicsBody() );
		bullet->setVisible(false);

		mWorld->removeBody(target->getPhysicsBody());
		target->setVisible(false);

		score++;
		getCurLevel();
		__String *tempScore = __String::createWithFormat( "%i",score  );
		scoreLabel->setString( tempScore->getCString() );

	}

	//Va cham giua may bay dich va player

	if ((tag==TAG_PLAYER && tag1==TAG_ENEMY)||(tag1==TAG_PLAYER && tag==TAG_ENEMY))
	{
		_live--;
		__String *tempLive = __String::createWithFormat( "%i",_live  );
		liveLabel->setString( tempLive->getCString() );
		auto blink = Blink::create(0.1f,1);
		plane->playerSprite->runAction(blink);
	}

	if ((tag == TAG_HANHTINH & tag1 ==TAG_PLAYER )||( tag ==TAG_PLAYER & tag1 ==TAG_HANHTINH))
	{
		
		stopMutiShoot();
		_live--;
		__String *tempLive = __String::createWithFormat( "%i",_live  );
		liveLabel->setString( tempLive->getCString() );
		auto blink = Blink::create(0.1f,1);
		plane->playerSprite->runAction(blink);

	}

	if ((tag ==TAG_BULLET & tag1 ==TAG_BOSS)|| ( tag==TAG_BOSS & tag1 ==TAG_BULLET ))
	{

		_liveEnemy--;
		stopShootBoss();
			score += 10;
		bullet->setVisible(false);
		mWorld->removeBody(bullet->getPhysicsBody());
		auto blink = Blink::create(0.1f,1);
		boss->runAction(blink);
	}


	if ((tag ==TAG_PLAYER & tag1 ==TAG_VATPHAM )|| ( tag==TAG_VATPHAM & tag1==TAG_PLAYER ))
	{

		//stopShoot();
		startMutiShoot();
		
	}

	return true;
}

Level GameScene::getCurLevel()
{
	return level;
}
