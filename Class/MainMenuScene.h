#ifndef __MAIN_MENU_SCENE_H__
#define __MAIN_MENU_SCENE_H__

#include "cocos2d.h"

class MainMenuScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
	void GoToGameScene( cocos2d::Ref* sender );
	cocos2d::Sprite * bgMainMenuArray[2];
	void update( float dt );
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainMenuScene);
};

#endif // __MAIN_MENU_SCENE_H__
