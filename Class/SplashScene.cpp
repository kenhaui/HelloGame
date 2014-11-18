#include "MainMenuScene.h"
#include "SplashScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace std;

Scene* SplashScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SplashScene::create();

    // add layer as a child to scene
    scene->addChild(layer);


    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SplashScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

	logo = Sprite::create("Logo_2.png");
	logo->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
	this->addChild(logo);

	ani = Sprite::create();
	ani->setPosition(Point(visibleSize.width/2,visibleSize.height/2 - 100));
	this->addChild(ani);
	Vector<SpriteFrame*> aniFrame;
			aniFrame.reserve(5);
			aniFrame.pushBack( SpriteFrame::create("game_loading1.png", Rect(0, 0, 186, 38)) );
			aniFrame.pushBack( SpriteFrame::create("game_loading2.png", Rect(0, 0, 186, 38)) );
			aniFrame.pushBack( SpriteFrame::create("game_loading3.png", Rect(0, 0, 186, 38)) );
			aniFrame.pushBack( SpriteFrame::create("game_loading4.png", Rect(0, 0, 186, 38)) );

			Animation *animation = Animation::createWithSpriteFrames(aniFrame, 0.5);
			Animate *animate = Animate::create(animation);
			ani->runAction( RepeatForever::create(animate) );


  this->schedule(schedule_selector(SplashScene::GoToMainMenuScene), 4);
  LoadEffect();
	  		

    return true;
}

void SplashScene::LoadEffect()
{
	

}


void SplashScene::GoToMainMenuScene( float dt )
{
	
	auto scene = MainMenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
}