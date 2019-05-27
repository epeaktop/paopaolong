#ifndef PROP_LAYER_H_
#define PROP_LAYER_H_

#include "cocos2d.h"

USING_NS_CC;

class PropLayer : public Layer
{
public:
	CREATE_FUNC(PropLayer);
	virtual bool init();
	CC_SYNTHESIZE(float, _time, Time);
	void AddScoreLabel(int var);
	void setCannonAngle(Point target);
	void setCannonAction(Point target);
	void setBombNum();
	void setColorBubbleNum();
    bool _isPause; 
	Node* _propLayer;
	void buttonCallback(Ref* pSender);
    void showOpenBoxAnimi(int flag);

private:

	
	void timeCallFunc();
	void menuBombCallBack(Ref* Psender);
	void menuHourglassCallBack(Ref* Psender);
	void menuPauseCallBack(Ref* Psender);
	void menuColorBubbleCallBack(Ref* Psender);
	void update(float delta);
    void initShooter();
    /**
     * 初始化分数label
     */
    void initScoreLabel();
    /**
     * 初始化换球的图片
     */
    void initChangeBubbleSprite();
    void initLevelLabel();
    void initLevelNumLabel();
    MenuItemImage* initPauseButton();
    /**
     * 显示剩余球数
     */
    void showMoveNumbers();
    /**
     * 初始化剩余步骤数
     */
    void initMoveNumbers();
    
    void subMoveNumber()
    {
        if(moveNumber_ > 0)
        {
            moveNumber_ -= 1;
        }
    }
    void addMoveNumber(int n)
    {
        moveNumber_ += n;
    }
private:
    /**
     * 当前剩余步骤
     */
    int moveNumber_ = 0;
    /**
     * 分数label
     */
    Label *scoreLabel_ = nullptr;
};






#endif
