#ifndef __HANH_TINH_H__
#define __HANH_TINH_H__

#include "cocos2d.h"
USING_NS_CC;
using namespace cocos2d;

class Hanhtinh : public Layer

{
public:
	~Hanhtinh();

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static Hanhtinh* create();

	virtual bool init();

	cocos2d::Size visibleSize;
	cocos2d::Point origin;
	//Tao vector luu tru cac hanh tinh
	std::vector< cocos2d::Sprite *> hanhtinh;
	void spawn_hanhtinh( float dt );
	void update( float dt );

	
};

#endif // __HANH_TINH_H__
