#ifndef BUBBLE_LAYER_H_
#define BUBBLE_LAYER_H_

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

class BubbleLayer : public Layer
{
public:
    virtual bool init();
    static cocos2d::Scene* scene();
	void onTouch(Point target);
	CREATE_FUNC(BubbleLayer);
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
	bool isGameOver();
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
    void showHits(int num);

    const int const_line = 8;
    /* 目前泡泡的高度 */
    int getHowmanyLines()
    {
        int n = 0;
        for (int i = 0; i < MAX_ROWS; i++)
        {
            bool haveballs = false;
            for (int j = 0; j < MAX_COLS; ++j)
            {
                if (board[i][j] != 0)
                {
                    haveballs = true;
                }
            }
            if(haveballs)
            {
                n++;
            }
        }
        return n;
    }
    float getStart()
    {
        const float oldY = 100;
        
        int n = getHowmanyLines();
        if(n <= const_line)
        {
            return oldY;
        }
        else
        {
            n = n - const_line;
        }
        return oldY + n*2*R;
    }
    //
    void moveBoard(int n)
    {
        float dis = 2*R*n;
        for(int i = 0; i< MAX_ROWS;i++)
        {
            for(int j = 0; j< MAX_COLS;j++)
            {
                if(auto sp = board[i][j])
                {
                    auto x = sp->getPosition().x;
                    auto y = sp->getPosition().y;
                    
                    sp->setPosition(x, y + dis);
                }
            }
        }
        copyBoard(n);
    }
    
    void copyBoard(int n)
    {
        Bubble* a[MAX_ROWS + 10][MAX_COLS] = {0};
        for(int i = 0; i < MAX_ROWS; i++)
        {
            for(int j = 0; j < MAX_COLS; j++)
            {
                a[ i + n][j] =  board[i][j];
            }
        }
        for(int i = 0; i < MAX_ROWS; i++)
        {
            for(int j = 0; j < MAX_COLS; j++)
            {
                board[i][j] =  a[i][j];
            }
        }
    }
    int startLines_ = 0;
    int endLines_ = 0;
    
    int getMoveNumber()
    {// getHowmanyLines
        return startLines_ - endLines_;
    }

    void  moveObj(Sprite* obj, Vec2 targetPos)
    {
        auto moveto = MoveTo::create(0.1f, targetPos);
        obj->runAction(moveto);
    }
    /* 获取当前移动的步数 */
    CC_SYNTHESIZE_ADD(int, _moveNumbers, MoveNumber);

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
    int curFindCol = 0;
    int curFindRow = 0;
    int updateTimes = 0;
    /**
     *	当前击落的泡泡数
     */
	int curDownNum_ = 1;

};

#endif /* defined(__paopaolong__MainLayer__) */
