#include "MainMenuScene.h"
#include "GameScene.h"

USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);


    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

  

	//Add menuTitle

	auto menuTitle = MenuItemImage::create("MainMenuScreen/Game_Title.png",
		"MainMenuScreen/Game_Title.png" );

	//add play buttom MainMenuScene to GameScene
	auto playItem = MenuItemImage::create("MainMenuScreen/Play_Button.png", 
		"MainMenuScreen/Play_Button(Click).png",
		CC_CALLBACK_1(MainMenuScene::GoToGameScene, this)
		);


	auto menu = Menu::create( menuTitle , playItem, NULL );
	menu->alignItemsVerticallyWithPadding(visibleSize.height / 5);
	this->addChild( menu );

	//add logo

	auto logo = Sprite::create("Logo_2.png");
	logo->setPosition( Point( visibleSize.width /2 ,40 ) );
	this->addChild( logo, 1 );

	this->scheduleUpdate();
	/*auto backgroundSprite = Sprite::create("MainMenuScreen/Background.png");
	backgroundSprite->setPosition( Point( visibleSize.width /2 + origin.x , visibleSize.height /2 + origin.y ) );
	this->addChild( backgroundSprite, -1 );*/

	for (int i = 0; i < 2; i++)
	{
		bgMainMenuArray[i] = Sprite::create("MainMenuScreen/Background.png");
		bgMainMenuArray[i]->setPosition(Point(visibleSize.width /2 , visibleSize.height /2));
		this->addChild(bgMainMenuArray[i], -1);
		float rX = visibleSize.width / bgMainMenuArray[i]->getContentSize().width;
		float rY = visibleSize.height / bgMainMenuArray[i]->getContentSize().height;

		// set the scaling factor to the background image

		bgMainMenuArray[i]->setScaleX( rX );
		bgMainMenuArray[i]->setScaleY( rY );

	}

	
	

    return true;
}

void MainMenuScene::update( float dt )
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	for (int i = 0; i < 2; i ++)
	{
		if (bgMainMenuArray[i]->getPosition().x > visibleSize.width + (visibleSize.width / 2)-1)
		{
			bgMainMenuArray[i]->setPosition(Point( (-1 * visibleSize.width) + (visibleSize.width /2 ), ( visibleSize.height/2)));
		}
	}

	/*for (int i = 0 ; i < 2; i ++)
	{
	bgMainMenuArray[i]->setPosition(Point(bgMainMenuArray[i]->getPosition().x  + (0.1 * visibleSize.width * dt), 
	bgMainMenuArray[i]->getPosition().y));
	}*/
}


void MainMenuScene::GoToGameScene( cocos2d::Ref* sender )
{
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(scene);
}