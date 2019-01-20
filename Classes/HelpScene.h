// jiangxf @ 2019.1.20
#ifndef xzdd_HelpScene_h
#define xzdd_HelpScene_h
#include "cocos2d.h"
using namespace cocos2d;

class HelpScene : public Layer
{
    Sprite * bjSprite;
private:
	float y_begin;//触摸开始时y位置
	float y_batch_location_begin;//触摸开始时成就batch位置
	float y_end;//触摸结束时y位置
    float y_max;
    float y_min;
    
    float moveSpeed;            //移动速度    
    bool enableMove;            //允许自动移动
    float y_last;               //上一帧 y的位置
    
    Sprite* sliver_ = nullptr;
    Label*  sliverNumber_ = nullptr;
    
    Sprite* hp_ = nullptr;
    Sprite* star_ = nullptr;
    Sprite* quit_ = nullptr;
    Label* hpNumber_ = nullptr;
    Label* starNumber_ = nullptr;
    int starNum_ = 0;
    /* 模式：0代表冒险模式;1 代表经典模式 */
    int mode_ = 0;
public:
    void setClassicsMode(bool mode)
    {
        if(mode)
            mode_ = 1;
        else
            mode_ = 0;
    }
    bool isClassicsMode() const { return mode_ == 1; }
    bool isAdventureMode() const { return mode_ == 0; }
	virtual bool init();
    virtual void onExit();
	static Scene* scene();
    Layer* helpLayer;

	virtual void menuBackCallback(Ref* pSender);
    virtual void lockBackCallback(Ref* pSender);

	CREATE_FUNC(HelpScene);
    
	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchEnded(Touch* touch, Event* event);
	virtual void onTouchMoved(Touch* touch, Event* event);
    void buttonCallback(Node *pNode);
    void undateState(float dt);
    
    void showSliver();
    void showHp();
    void showStar();
    int getStarNumbers();
    void showQuit();
    bool touchQuit(Vec2 v);
};

#endif
