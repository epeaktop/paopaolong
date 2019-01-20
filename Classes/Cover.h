#ifndef __popstart__Cover__
#define __popstart__Cover__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "MoreGame.h"

USING_NS_CC;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated"
using namespace CocosDenshion;

class Cover : public Layer
{
public:
    Cover(): isSoundOn_(true),sound_(NULL),sound2_(NULL),someNumber(0){}
    virtual ~Cover() {}
    static Scene *scene();
    virtual bool init();
    virtual void onExit();
    virtual void onEnter();
    void showEffect(CCPoint p, int type);
    void update(float dt);
public:
    void newCallback(Ref *pSender);
    void exitCallback(Ref *pSender);
    void resumeCallback(Ref *pSender);
    void soundCallBack(Ref *pSender);
    void showSoundButton();
    void showMoreGame();
    bool onTouchBegan(Touch *touch, Event *unused_event);
	void onTouchMoved(Touch *touch, Event *unused_event);
	void onTouchEnded(Touch *touch, Event *unused_event);

    void regTouch();
    MenuItemImage* addRateButton();
public:
    bool isSoundOn_;
    MenuItemImage *sound_;
    MenuItemImage *sound2_;
    
    int someNumber;
    CREATE_FUNC(Cover);
    
//    MoreGameLayer *moreGameLayer_ = nullptr;
    bool moreGameLayerShow = false;
    EventListenerTouchOneByOne* _listener;
};

#endif /* defined(__popstart__Cover__) */
