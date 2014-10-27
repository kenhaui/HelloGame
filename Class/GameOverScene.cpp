#include "GameOverScene.h"
#include "MainMenuScene.h"
#include "GameScene.h"

USING_NS_CC;

unsigned int score;

Scene* GameOverScene::createScene( unsigned int tempScore )

{
	score = tempScore;
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameOverScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameOverScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

	auto bgGameOverScene = Sprite::create("GameOverScreen/Game_Over_Screen_Background.png");
	bgGameOverScene->setPosition(Point(visibleSize.width/2 + origin.x , visibleSize.height /2 + origin.y));
	this->addChild( bgGameOverScene, -1 );

	float rX = visibleSize.width / bgGameOverScene->getContentSize().width;
	float rY = visibleSize.width / bgGameOverScene->getContentSize().height;

	bgGameOverScene->setScaleX(rX);
	bgGameOverScene->setScaleY(rY);


	auto gameOverTitle = MenuItemImage::create("GameOverScreen/Game_Over.png","GameOverScreen/Game_Over.pnga");

	auto retry = MenuItemImage::create("GameOverScreen/Retry_Button.png", 
		"GameOverScreen/Retry_Button(Click).png", 
		CC_CALLBACK_1(GameOverScene::GoToGameScene, this));

	auto mainMenu = MenuItemImage::create("GameOverScreen/Menu_Button.png",
		"GameOverScreen/Menu_Button(Click).png" ,
		CC_CALLBACK_1(GameOverScene::GoToMainMenuScene, this));

	auto menu = Menu::create(gameOverTitle, retry, mainMenu, NULL);
	menu->alignItemsVerticallyWithPadding(visibleSize.height /6);

	this->addChild( menu );

	UserDefault* def = UserDefault::getInstance();
	auto hightScore = def->getIntegerForKey("HIGHTSCORE PLANE", 0);

	if (score > hightScore )
	{
		hightScore = score;
		def->setIntegerForKey("HIGHTSCORE PLANE", hightScore);
	}

	def->flush();
	

   __String* tempScore = __String::createWithFormat("%i", score);
   auto cureentScore = LabelTTF::create(tempScore->getCString(),"fonts/Marker Felt.ttf", visibleSize.height* 0.1f);
   cureentScore->setPosition( Point( visibleSize.width/2, visibleSize.height/2 ) );
   this->addChild( cureentScore );
    
   __String* tempHightScore = __String::createWithFormat("%i", hightScore);
   auto hightScoreLabel = LabelTTF::create(tempHightScore->getCString(),"fonts/Marker Felt.ttf", visibleSize.height* 0.1f);
   hightScoreLabel->setPosition( Point(visibleSize.width/2, 100) );
   hightScoreLabel->setColor(Color3B::YELLOW );
   this->addChild( hightScoreLabel );

    return true;
}


void GameOverScene::GoToGameScene( cocos2d::Ref* sender )
{
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

void GameOverScene::GoToMainMenuScene( cocos2d::Ref* sender )
{
	/*auto scene = MainMenuScene::createScene();
	Director::getInstance()->replaceScene(scene);*/
	MessageBox("Xin chao!", "Thong bao");
}