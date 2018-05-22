//
//  MoreGame.cpp
//  paopaolong
//
//  Created by jiangxf on 2017/9/25.
//
//

#include "MoreGame.h"

bool MoreGameLayer::init()
{
	auto sp = Sprite::create("more_game.png");
    addChild(sp);
    Size size = Director::getInstance()->getWinSize();
    sp->setPosition(size.width/2, size.height/2);
    regTouch();
	return true;
}

void MoreGameLayer::regTouch()
{
	_listener = EventListenerTouchOneByOne::create();
    //_listener->setSwallowTouches(true);
    _listener->onTouchBegan = CC_CALLBACK_2(MoreGameLayer::onTouchBegan, this);
    _listener->onTouchMoved = CC_CALLBACK_2(MoreGameLayer::onTouchMoved, this);
    _listener->onTouchEnded = CC_CALLBACK_2(MoreGameLayer::onTouchEnded, this);

    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_listener, this);

}

bool MoreGameLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
	return true;
}

void MoreGameLayer::onTouchMoved(Touch *touch, Event *unused_event)
{

}
void MoreGameLayer::onTouchEnded(Touch *touch, Event *unused_event)
{

}
