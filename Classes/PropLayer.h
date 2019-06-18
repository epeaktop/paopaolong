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
	void menuBiaoCallBack(Ref* pSender);
	void addMoveNumberForOpenBox(Ref* Psender);
	void menuPauseCallBack(Ref* Psender);
	void menuColorBubbleCallBack(Ref* Psender);
	void update(float delta);
    void initShooter();
	void showBuyAds();
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
    
    void initBox();
	/**
	 *	初始化道具按钮
	 */
	void initItemBtn();
	/**
	 *	show item icon
	 *  args: 
	 *    haveNumowner number
	 *    pos position
	 */
	void showItemIcon(MenuItemImage*item, int haveNum, Vec2 pos, int tag);
	/**
	 *	Set the text on the icon
	 */
	void setTextOnIcon(Node* icon, const int tag, int haveNum);
public:
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
	int getMoveNumber()
	{
		return moveNumber_;
	}
    bool hadFinished_ = false;
	/**
	 *	显示颜色按钮
	 */
	void initColorBtn();
	/**
	 *	选择具体颜色按钮回调
	 */

	void colorBtn(Ref* pSender);
private:
	bool notShowBuy = false;
    /**
     * 当前剩余步骤
     */
    int moveNumber_ = 0;
    /**
     * 分数label
     */
    Label *scoreLabel_ = nullptr;
    int flag = 0;
    int openBoxFlag = 0;
    bool isOpenBoxInGame = false;
public:	
	/**
	 *	时候处于编辑关卡模式
	 */
	static bool isDesign;
};






#endif
