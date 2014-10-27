#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Plane.h"
#include "Hanhtinh.h"
USING_NS_CC;

enum Level
{
	EASY,
	MIDDLE,
	HARD,
};

class GameScene : public cocos2d::Scene
{
	
public:
	Size visibleSize;
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
	
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    void update( float dt );
	void GoToPauseMenuScene( cocos2d::Ref* sender );
	void GoToGameOverScene( cocos2d::Ref* sender );
	cocos2d::Sprite *spriteBackgroundArray[2];
	//void spawn_hanhtinh( float dt );

	void spawn_pipe ( float dt );

	void addBullet( float dt);
	void addbutlletMuti( float dt );
	void addButlletBoss_1( float dt );
	void addEnemy ( float dt );
	void addVatPham( float dt );
	void bulletMoveFinished (Node* pSender);
	void mutiBulletMoveFinished ( Node* pSender );
	void bulletBossMoveFinished ( Node* pSender );
	void vatPhamMoveFinished ( Node* pSender );

	void startMutiShoot( float delay = 0.0f );
	void stopMutiShoot();
	void startShoot( float delay = 0.0f );
	void stopShoot(  );
	void startShootBoss( float delay = 0.0f );
	void stopShootBoss(  );

	//Sprite* playerSprite;
	Sprite* bullet;
	Sprite* mutiBulletLeft;
	Sprite* mutiBulletRight;
	Sprite* bulletBoss;
	Point touchOffset;
	Sprite* boss;
	Sprite* vatPham;
	Action* boss_move;
	//Sprite* enemy;

	Plane *initPlane();

	Plane *plane;


	Hanhtinh *initHanhtinh();
	Hanhtinh *_hanhtinh;


	Point touchTopoint( Touch* touch );
	bool touchingSprite ( Touch* touch );
	bool isShowBoss;

	void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event);
	void onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event);
	void onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event);
	
	////Tao vector luu tru cac hanh tinh
	//std::vector< cocos2d::Sprite *> hanhtinh;
	//vecto luu tru enemy
	std::vector< cocos2d::Sprite* > enemy;

	cocos2d::PhysicsWorld * mWorld;
	void setPhysicsWorld( cocos2d::PhysicsWorld* world )
	{
		mWorld = world;
	}
	bool onContactBegin( const PhysicsContact& contact );


	static Level getCurLevel();// lay level hien tai
	static Level level;

	//tinh mang

	int _live;
	int _liveEnemy;
	unsigned int score;
	Label *scoreLabel;
    Label *liveLabel;
	Label *levelLabel;
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
};

#endif // __GAME_SCENE_H__
