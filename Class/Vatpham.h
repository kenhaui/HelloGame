#ifndef __PLANE_H__
#define __PLANE_H__

#include "cocos2d.h"
USING_NS_CC;
using namespace cocos2d;

class Plane : public Layer

{
public:
	~Plane();

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static Plane* create();

	virtual bool init();

	cocos2d::Size visibleSize;
	cocos2d::Point origin;

	Sprite* playerSprite;
	Point playerSpritePosition;
		Point bulletPosition;

	
};

#endif // __PLANE_H__
