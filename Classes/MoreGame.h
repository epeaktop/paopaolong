//
//  MoreGame.hpp
//  paopaolong
//
//  Created by jiangxf on 2017/9/25.
//
//

#ifndef MoreGame_hpp
#define MoreGame_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "cocos-ext.h"
using namespace cocos2d;
using namespace cocos2d::extension;

class MoreGameLayer : public Layer
{
public :
    CREATE_FUNC(MoreGameLayer);
	virtual bool init();
    void regTouch();
    
    
public:
    
    bool onTouchBegan(Touch *touch, Event *unused_event);
	void onTouchMoved(Touch *touch, Event *unused_event);
	void onTouchEnded(Touch *touch, Event *unused_event);
    
public:
	EventListenerTouchOneByOne* _listener;
};
#endif /* MoreGame_hpp */
