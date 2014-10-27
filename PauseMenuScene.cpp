#include "PauseMenuScene.h"
#include "GameScene.h"
#include "MainMenuScene.h"
USING_NS_CC;

Scene* PauseMenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = PauseMenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool PauseMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

   auto resumeItem = MenuItemImage::create("PauseScreen/Resume_Button.png", 
	   "PauseScreen/Resume_Button(Click).png", 
	   CC_CALLBACK_1(PauseMenuScene::Resume, this));

   auto retryItem = MenuItemImage::create("PauseScreen/Retry_Button.png", 
	  "PauseScreen/Retry_Button(Click).png", 
	   CC_CALLBACK_1(PauseMenuScene::Retry, this));


   auto mainMenu = MenuItemImage::create("PauseScreen/Menu_Button.png", 
	   "PauseScreen/Menu_Button(Click).png", 
	   CC_CALLBACK_1(PauseMenuScene::GoToMainMenuScene, this));

   auto menu = Menu::create( resumeItem, retryItem, mainMenu, NULL );
   menu->alignItemsVerticallyWithPadding(visibleSize.height /4 );
   this->addChild( menu );


    return true;
}

void PauseMenuScene::Resume(cocos2d::Ref* sender)
{
	Director::getInstance()->popScene();
}

void PauseMenuScene::GoToMainMenuScene(cocos2d::Ref* sender)
{
	auto scene = MainMenuScene::createScene();
	Director::getInstance()->popScene();
	Director::getInstance()->replaceScene(scene);

}


void PauseMenuScene::Retry(cocos2d::Ref* sender)
{
	auto scene = GameScene::createScene();
	Director::getInstance()->popScene();
	Director::getInstance()->replaceScene(scene);

}


