#ifndef __PAUSE_MENU_SCENE_H__
#define __PAUSE_MENU_SCENE_H__

#include "cocos2d.h"

class PauseMenuScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    void Resume (cocos2d::Ref* sender);
	void GoToMainMenuScene (cocos2d::Ref* sender);
	void Retry (cocos2d::Ref* sender);

    // implement the "static create()" method manually
    CREATE_FUNC(PauseMenuScene);
};

#endif // __PAUSE_MENU_SCENE_H__
