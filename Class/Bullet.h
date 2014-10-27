#ifndef __BULLET_H__
#define __BULLET_H__

#include "cocos2d.h"
#include "Plane.h"
USING_NS_CC;
using namespace cocos2d;

class Bullet : public Layer

{
public:
	~Bullet();

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static Bullet* create();

	virtual bool init();

	cocos2d::Size visibleSize;
	cocos2d::Point origin;


	Sprite* bullet;
	Plane* initPlane();
	Plane* _plane;
	void addBullet( float dt);
	void bulletMoveFinished (Node* pSender);
	void startShoot( float delay = 0.0f );
	void stopShoot(  );
	
};

#endif // __BULLET_H__
