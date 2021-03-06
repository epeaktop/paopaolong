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
#include <queue>


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
	bool isTransparentObj(Bubble* obj);
	void transparentAction(Bubble* obj);
	void initReady();
private:

	Bubble *board[MAX_ROWS][MAX_COLS]; 
	Bubble *wait[MAX_WAIT_PAOPAO]; 	   
public:
	Bubble *ready;
public:
	
	CC_SYNTHESIZE(Vec2, real, Real);
	CC_SYNTHESIZE(int, _level, Level);
	bool _havePass = false;

	EventListenerTouchOneByOne* _listener;
	bool initTheBoard(int level = 0);
	Bubble *randomPaoPao(int flag = 0);
	Point getPointByRowAndCol(int row, int col);
	Point getRowAndColByPoint(Point target);
	void initWaitPaoPao(); 
	void initReadyPaoPao();
	void setEnable();
	void setDisable();
	bool isCollideBorder();
	bool checkCollideBorder();
	void changeWaitToReady();
	void showDebugString();
	void correctReadyPosition();
	Vec2 getStopPosition();
	bool getFirstRowFlag();
	bool isCircleCollision(Point pos1, float radius1, Point pos2, float radius2);
	void findTheSameBubble(int i, int j, bool flag, BubbleType type);
	void bubbleBlast(int i, int j, bool flag);
	void moveTheBubble(int i, int j, bool flag, float distance);
	void deleteTheSameBubble(int i, int j, bool flag);
	void bubbleAction(Bubble *obj);
	void bubbleColorAction(int i, int j);
	void callbackRemoveBubble(Node *obj);
	void downBubbleActionCallBack(Node *obj);
	void downLeftBubbleActionCallBack(Node *obj);
	void jumpActionCallBack();
	void resetAllPass();
	void checkDownBubble();
	void downBubble();

	void gameWin();
	void showTime();

	void downBubbleAction(Bubble* obj);
	/**
	 *	专门处理遗留下球的函数
	 */
	void downLeftBubbleAction(Bubble* obj);
	void initBubbleAction(Bubble *obj, int i, int j);
	void gameOver(bool over = false);
	void setReadyAngle(Point target);
	bool isGameOver();
	void movementPassCallBack(Armature * armature, MovementEventType type, const std::string &name);
	void moveParantCallBack(Armature * armature, MovementEventType type, const std::string &name);
	void readyAction();
    void playColorAnim();

	void colorBlast(int row, int col, bool isDouble);
	bool onTouchBegan(Touch *touch, Event *unused_event);
	void onTouchMoved(Touch *touch, Event *unused_event);
	void onTouchEnded(Touch *touch, Event *unused_event);
    void calcRetainMap();
    void showWinAnim(Vec2& pos);
    void starCallback(Ref* obj);
    void showHitNumsAnim();
    void showHits(int num);
	void cleanRoundTransparent(Bubble* obj, int i, int j);
	void showTimeShootBubble();
	/**
	 *	show time call back function. call xx times to show win ui
	 */
	void showTimeCallBack();
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
    void addScore(Bubble* obj);
	
	void setTouchWich(Vec2 v);
	
public:
	Vector<Sprite*> _auxiliary;
	/**
	 *	可以摆放球的点
	 */
	bool canPut(Bubble* sp);
	void colorBubble();
	void swapBubble();
	void bombBubble();
	void biaoBubble();
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
	bool isTouch1 = false;
	bool isTouch2 = false;
	bool isTouch3 = false;
	bool isTouch4 = false;
	/**
	 *	遗留下来球的数量
	 */
	int leftNum = 0;
	/**
	 *	curLeftNum ++ in callback
	 */
	int curLeftNum = 0;
	/**
	 *	call back show time times
	 */
	int showTimeCalledTimes = 0;
	
	vector<FiniteTimeAction*> actionList;
	/**
	 *	Waiting for the ball to disappear
	 */
	queue<Bubble*> bubbleList;
	/**
	 * 	Placed with colored bubbles
	 */
	vector<Bubble*> coloredList;
};

#endif /* defined(__paopaolong__MainLayer__) */
