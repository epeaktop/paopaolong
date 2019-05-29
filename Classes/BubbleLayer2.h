#ifndef BUBBLE_LAYER2_H_
#define BUBBLE_LAYER2_H_

#include "cocos2d.h"
#include "Bubble.h"
#include "GameConst.h"
#include "GameEnum.h"
#include "ui/CocosGUI.h"
#include "editor-support/cocostudio/CocoStudio.h"
#include "Tools.h"

#include <map>


USING_NS_CC;
using namespace cocostudio;

class BubbleLayer2 : public Layer
{
public:
    virtual bool init();
    static cocos2d::Scene* scene();
	void onTouch(Point target);
	CREATE_FUNC(BubbleLayer2);
	virtual void update(float delta);
private:
	Bubble *board[MAX_ROWS][MAX_COLS]; 	 //泡泡棋盘
	Bubble *wait[MAX_WAIT_PAOPAO]; 	    // 等待的泡泡
public:
	Bubble *ready;  // 将会发射的泡泡
public:
	CC_SYNTHESIZE(Vec2, real, Real);
	CC_SYNTHESIZE(int, _level, Level);
	bool _havePass = false;

	EventListenerTouchOneByOne* _listener;
	bool initTheBoard(int level = 0);  //初始化关卡
	Bubble *randomPaoPao(int flag = 0); //获取随机泡泡
	Point getPointByRowAndCol(int row, int col); //根据行列及是否左缺确定位置
	Point getRowAndColByPoint(Point target);
	void initWaitPaoPao(); //初始化等待的泡泡
	void initReadyPaoPao(); //初始化准备发射的泡泡
	void setEnable();	//设置触摸有效
	void setDisable();	//设置触摸无效
	bool isCollideBorder();
	bool checkCollideBorder();
	void changeWaitToReady();
	void correctReadyPosition();
	bool getFirstRowFlag();
	bool isCircleCollision(Point pos1, float radius1, Point pos2, float radius2);
	void findTheSameBubble(int i, int j, bool flag, BubbleType type);
	void bubbleBlast(int i, int j, bool flag);
	void moveTheBubble(int i, int j, bool flag, float distance);
	void deleteTheSameBubble(int i, int j, bool flag);
	void bubbleAction(Bubble *obj);
	void callbackRemoveBubble(Node *obj);
	void downBubbleActionCallBack(Node *obj);
	void jumpActionCallBack();
	void resetAllPass();
	void checkDownBubble();
	void downBubble();
	void downBubbleAction(Bubble *obj);
	void initBubbleAction(Bubble *obj, int i, int j);
	void gameOver(bool over = false);
	void setReadyAngle(Point target);
	void throwBallAction();
	bool isPass();
	void movementPassCallBack(Armature * armature, MovementEventType type, const std::string &name);
	void moveParantCallBack(Armature * armature, MovementEventType type, const std::string &name);
	void readyAction();

	bool onTouchBegan(Touch *touch, Event *unused_event);
	void onTouchMoved(Touch *touch, Event *unused_event);
	void onTouchEnded(Touch *touch, Event *unused_event);
    void calcRetainMap();
    void showWinAnim(Vec2& pos);
    void starCallback(Ref* obj);
    void showHitNumsAnim();
    void dump();
    /*  序列化  */
    void save();
    /* 反序列化, 序列化成功证明有过设计的关卡，就是读取的关卡设计 */
    bool load();
    const int const_line = 8;

    /* 获取当前移动的步数 */
    CC_SYNTHESIZE_ADD(int, _moveNumbers, MoveNumber);
    bool clickSelectButton(Point p)
    {
        return (p.y <= TOUCH_DOWN * Director::getInstance()->getVisibleSize().height && p.x <= 200);
    }
    bool clickDesignArea(Point p)
    {
        return !clickSelectButton(p);
    }
	/**
	 *	标识ui层为设计模式
	 */
	void markDesign();

public:
	Vector<Sprite*> _auxiliary;
	void colorBubble();
	void swapBubble();
	void bombBubble();
	void auxiliaryLine(Point tagrat);
    void buttonCallback(Node* obj);
    std::map<int, int> retainMap_;    // 用来计算还剩下那些颜色的泡泡
    std::vector<int>   retainVec_;    // 将计算结果转换成数组
    /**
     * 连击数
     */
    unsigned int hitNums_ = 0;
    /**
     * 上次发射泡泡是否击中泡泡
     */
    bool lastHited_ = false;
    Label *hitedNumLabel_ = nullptr;
    Label *moveNumberLabel_ = nullptr;
    Label *moveLabel_ = nullptr;
    /**
     * 当前选择颜色的值
     */
     int currentColor_ = 1;
};

#endif /* defined(__paopaolong__MainLayer__) */
