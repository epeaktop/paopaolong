#include "BubbleLayer.h"
#include "GameScene.h"
#include "UserData.h"
#include "SimpleAudioEngine.h"
#include "PropLayer.h"
#include <thread>
#include "HelpScene.h"
#include "GameResult.h"
#include "NDKHelper.h"
struct PosData
{
	int x;
	int y;
	Vec2 pos;
};
const int BT_OK = 2401;

using namespace CocosDenshion;
using namespace cocostudio::timeline;
using namespace std;

static float waitTime = 0.1f;
static int sameSum = 0;

/*
 进入设计模式（实验室）
 google视频广告
 facebook接入
 更多的展示广告
 增加些道具
   *【钢球】按照一条直线碰到全部消失
 领取每日奖励（Daily Rewards）
 花金币就可以增加游戏的时间并且弹出广告
 没有金币看奖励广告就可以得到金币
 Fun and Simple time killer no complicated nonsense… Litterally shoot bubbles! Perfect
 画上切换球的图标
 透明泡泡,碰撞后透明泡泡会消失
 将三消游戏上传上来
 给ads账号充值
 打开游戏出现logo，然后出现进度条
 界面切换时候出现新手引导
*/
void debugLog(Bubble* obj, int index, int i, int j)
{
	if (obj && i < MAX_ROWS && j < MAX_COLS && i >= 0 && j >= 0)
		log("item%d not nullpte, %d,%d,(%f,%f)", index, i, j, obj->getPosition().x, obj->getPosition().y);
}
Scene *BubbleLayer::scene()
{
    Scene *scene = Scene::create();
    BubbleLayer *layer = BubbleLayer::create();
    scene->addChild(layer);
    return scene;
}

void BubbleLayer::calcRetainMap()
{
    retainMap_.clear();
    for (int i = 0; i < MAX_ROWS; ++i)
    {
        for (int j = 0; j < MAX_COLS; ++j)
        {
            if (!board[i][j])
            {
                continue;
            }
            int key = (int)board[i][j]->getType();
            if (key > 0)
            {
                retainMap_[key] = 1;
            }
        }
    }
    retainVec_.clear();
    for (auto iter = retainMap_.begin(); iter != retainMap_.end(); ++iter)
    {
        int key = iter->first;
        if (key > 0)
        {
            retainVec_.push_back(key);
        }
    }
    
}

// 显示连击
void BubbleLayer::showHits(int num)
{
    auto m = MoveTo::create(1, Vec2(500, 300));
    auto m2 = MoveTo::create(1,Vec2(1380,300));
    auto d = DelayTime::create(0.7);
    auto seq = Sequence::create(m,d,m2, NULL);
    stringstream s("");
    s << num << " hits";
    hitedNumLabel_->setString(s.str().c_str());
    hitedNumLabel_->runAction(seq);
}

bool BubbleLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    _level = UserData::getInstance()->getSelLevel();
    
    UserData::getInstance()->setScore(0);
    _listener = EventListenerTouchOneByOne::create();
    _listener->setSwallowTouches(true);
    _listener->onTouchBegan = CC_CALLBACK_2(BubbleLayer::onTouchBegan, this);
    _listener->onTouchMoved = CC_CALLBACK_2(BubbleLayer::onTouchMoved, this);
    _listener->onTouchEnded = CC_CALLBACK_2(BubbleLayer::onTouchEnded, this);

    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_listener, this);

    initTheBoard(UserData::getInstance()->getSelLevel());
    calcRetainMap();
    initWaitPaoPao();
    initReadyPaoPao();
    hitedNumLabel_ = Label::createWithSystemFont("0 hits", "Arial", 30);
    addChild(hitedNumLabel_, 1000);
    hitedNumLabel_->setPosition(1380, 300);
    this->setMoveNumber(0);
    moveLabel_ = TI()->addLabel(this, std::string("Moves:"), 1000.0f, 50.0f, 1000);
    moveNumberLabel_ = TI()->addLabel(this, std::string("0"), 1100.0f, 50.0f, 1000);
    return true;
}


bool BubbleLayer::initTheBoard(int level)
{
    bool bRet = false;

    for (int i = 0; i < MAX_ROWS; ++i)
    {
        for (int j = 0; j < MAX_COLS; ++j)
        {
            board[i][j] = NULL;
        }
        bRet = true;
    }

    for (int i = 0; i < MAX_ROWS; i++)
    {
        for (int j = 0; j < MAX_COLS; ++j)
        {
            if ((i % 2 && j == MAX_COLS - 1) || customs[level][i][j] == 0)
            {
                continue;
            }

            if (customs[level][i][j] == -1)
            {
                board[i][j] = randomPaoPao(1);
            }
            else if (customs[level][i][j] != 0)
            {
                board[i][j] = Bubble::initWithType((BubbleType)customs[level][i][j]);
            }
            board[i][j]->setFlag((i % 2) == 0);
          
            board[i][j]->setString(i,j);
            
            addChild(board[i][j]);
            initBubbleAction(board[i][j], i, j);
        }
    }

    return bRet;
}

Bubble *BubbleLayer::randomPaoPao(int flag)
{
    Bubble *pRet = NULL;
    
    BubbleType type;
    if (flag != 0 )
    {
        type = static_cast<BubbleType>(rand() % BUBBLE_COUNT + 1);
    }
   	else
    {
        calcRetainMap();
        if (retainVec_.size() ==0 )
        {
            type = BUBBLE_TYPE1;
        }
        else
        {
            int i = rand() % (retainVec_.size());
            type = static_cast<BubbleType>(retainVec_[i]);
        }
    }
    
    pRet = Bubble::initWithType(type);
    return pRet;
}

// 根据行、列确定球的位置
Point BubbleLayer::getPointByRowAndCol(int row, int col)
{
    bool flag = (row % 2 == 0);
    Size winSize = Director::getInstance()->getWinSize();
    auto x = (col * 2 + 1) * (R + 1) + (flag ? 0 : R);
    auto y = TOUCH_TOP * winSize.height - row * (R * 2 - 5) - R;
    
    return Point(x,y);
}

Vec2 BubbleLayer::getRowAndColByPoint(Point target)
{
    Size winSize = Director::getInstance()->getWinSize();
    int x = (TOUCH_TOP * winSize.height - target.y) / (R * 2 - 5);
    int y = ((target.x - (x % 2) * R) / ((R + 1) * 2));
    
    return Vec2(x, y);
}
void BubbleLayer::initWaitPaoPao()
{
    for (int i = 0; i < MAX_WAIT_PAOPAO; ++i)
    {
        Bubble *obj = randomPaoPao();
        obj->setPosition(WAIT_PAOPAO_POS);
        wait[i] = obj;
        this->addChild(obj);
    }
}
void BubbleLayer::initReadyPaoPao()
{
    ready = randomPaoPao();
    ready->setPosition(READY_PAOPAO_POS);
    this->addChild(ready);
}
void BubbleLayer::onTouch(Point target)
{
    this->real = (target - ready->getPosition()).getNormalized();
    auto gameScene = (GameScene *)this->getParent();
    auto proplayer = (PropLayer *)gameScene->_propLayer;

    switch (ready->getType())
    {
    case BUBBLE_TYPE_COLOR:
        UserData::getInstance()->addColorBubble(-1);
        proplayer->setColorBubbleNum();
        break;

    case BUBBLE_TYPE_BOMB:
        UserData::getInstance()->addBomb(-1);
        proplayer->setBombNum();
        break;

    default:
        break;
    }
    this->addMoveNumber(1);
    this->scheduleUpdate();
}


void BubbleLayer::setEnable()
{
    _listener->setEnabled(true);
}

void BubbleLayer::setDisable()
{
    _listener->setEnabled(false);
}

void BubbleLayer::update(float fDelta)
{
    
    if (isCollideBorder())
    {
        log("[撞到边缘]%f", real.x);
        real.x = -real.x;
    }

    setDisable();
    Point pos = ready->getPosition();
    int flag = 2;
    if(updateTimes++ > 1)
        flag = 1;
    auto newPos = Point(pos.x + real.x * PAOPAO_SPEED* flag, pos.y + real.y * PAOPAO_SPEED*flag);
    ready->setPosition(newPos);
    Vec2 s = getRowAndColByPoint(newPos);
    log("<update>(%d,%d)-->(%d,%d):row(%d),col(%d),%f",int(pos.x),int(pos.y), int(newPos.x),int(newPos.y),int(s.x), int(s.y),fDelta);
    if (checkCollideBorder())
    {
        SimpleAudioEngine::getInstance()->playEffect("Music/Hit.mp3");
        this->unscheduleUpdate();
        updateTimes = 0;
        real = Point::ZERO;
        correctReadyPosition();
        return;
    }
}
// 是否碰撞了边界
bool BubbleLayer::isCollideBorder()
{
    bool bRet = false;
    Size size = Director::getInstance()->getWinSize();
    Point pos = ready->getPosition();

    if (pos.x + R > size.width || pos.x - R / 2 < 0)
    {
        bRet = true;
    }

    return bRet;
}

// 检查是否碰撞到附近的球，在update中如果碰不到附近的球，球就一直运动
// 碰到附近的球了就停止运动
bool BubbleLayer::checkCollideBorder()
{
    auto winSize = Director::getInstance()->getVisibleSize();
    auto point = ready->getPosition();

    /* 底部的边界 */
    if (point.y < TOUCH_DOWN * winSize.height)
    {
        return false;
    }
    /* 顶部边界 */
    if (ready->getPosition().y > TOUCH_TOP * winSize.height - R)
    {
        if (ready->getType() == BUBBLE_TYPE_COLOR)
        {
            BubbleType type = (BubbleType)((int)(CCRANDOM_0_1() * 7 + 1));
            ready->setType(type);
            ready->initWithSpriteFrameName(StringUtils::format(BUBBLE_NAME.c_str(), type));
        }
        // 确定当前的行，列
        curFindRow = 0;
        curFindCol = getRowAndColByPoint(point).y;
        return true;
    }
    
    std::vector<Vec2> rowCol;
     rowCol.push_back(getRowAndColByPoint(Point(point.x, point.y)));
    rowCol.push_back(getRowAndColByPoint(Point(point.x, point.y + R))); // 当前点的上面
    rowCol.push_back(getRowAndColByPoint(Point(point.x - R, point.y))); // 当前点的左边
    rowCol.push_back(getRowAndColByPoint(Point(point.x + R, point.y))); // 当前点的右边

    for (auto & ti : rowCol)
    {
        if(int(ti.y) >= MAX_COLS)
            continue;
        if(int(ti.x) >= MAX_ROWS)
            continue;
        if (board[int(ti.x)][int(ti.y)] != nullptr)
        {
            log("[@@@@]%d,%d", int(ti.x), int(ti.y));
#ifdef DEBUG
            if(board[curFindRow][curFindCol]!=nullptr)
            {
                board[curFindRow][curFindCol]->setColor(Color3B(255,255,255));
            }
#endif
            curFindRow = int(ti.x);
            curFindCol = int(ti.y);
#ifdef DEBUG
            board[int(ti.x)][int(ti.y)]->setColor(Color3B::RED);
#endif
            return true;
        }
    }
    return false;
}
// 调整后的点和发现有球的点是同一个点
void BubbleLayer::changeWaitToReady()
{
    ready = wait[0];
    auto jumpAction = JumpTo::create(0.1f, READY_PAOPAO_POS, 30.0f, 1);
    auto callFunc = CallFunc::create(CC_CALLBACK_0(BubbleLayer::jumpActionCallBack, this));
    auto seq = Sequence::create(jumpAction, callFunc, nullptr);
    ready->runAction(seq);
}



// 正在运动球停止了，摆正这个球的位置
void BubbleLayer::correctReadyPosition()
{
    int row = -1, col = -1;
    // 注意，这个ready的表诉并不清楚；应该是正在运动的球的位置
    Point pos = ready->getPosition();
    Vec2 rowCol = getRowAndColByPoint(pos);
    
    int i = curFindRow;
    int j = curFindCol;
    auto item1 = board[i][j-1];
    auto item2 = board[i][j+1];
    auto item3 = board[i+1][j-1];
    auto item4 = board[i+1][j];
    auto item5 = board[i+1][j+1];
    
    vector<PosData> a;
    debugLog(item1, 1, i, j-1);
    debugLog(item2, 2,i, j+1);
    debugLog(item3, 3,i+1,j-1 );
    debugLog(item4, 4,i+1,j);
    debugLog(item5, 5,i+1,j+1);
    
    if(j > 0 && item1 == nullptr)
    {
        PosData pd1;
        pd1.x = i;
        pd1.y = j-1;
        pd1.pos = getPointByRowAndCol(i,j-1);
        a.push_back(pd1);
    }
    if(j+1< MAX_COLS&& item2 == nullptr)
    {
        PosData pd1;
        pd1.x = i;
        pd1.y = j+1;
        pd1.pos = getPointByRowAndCol(i,j+1);
        a.push_back(pd1);
    }
    if(i+1 <MAX_ROWS&& item4 == nullptr)
    {
        PosData pd1;
        pd1.x = i+1;
        pd1.y = j;
        pd1.pos = getPointByRowAndCol(i+1,j);
        a.push_back(pd1);
    }
    
    if(i+1 <MAX_ROWS && j+ 1 < MAX_COLS && item5 == nullptr)
    {
        PosData pd1;
        pd1.x = i+1;
        pd1.y = j+1;
        pd1.pos = getPointByRowAndCol(i+1,j+1);
        a.push_back(pd1);
    }
    
    if(i+1 <MAX_ROWS && j-1 >= 0 && item3 == nullptr)
    {
        PosData pd1;
        pd1.x = i+1;
        pd1.y = j-1;
        pd1.pos = getPointByRowAndCol(i+1,j-1);
        a.push_back(pd1);
    }
    float dis = 100000;
    for(auto obj : a)
    {
        auto dis2 = obj.pos.distance(pos);
        if(dis2 < dis)
        {
            dis = dis2;
            row = obj.x;
            col = obj.y;
        }
    }
    // 上边界直接设置
    if(curFindRow==0 && board[curFindRow][curFindCol]==nullptr)
    {
        row = curFindRow;
        col = curFindCol;
    }
    
    board[row][col] = ready;
    board[row][col]->setString(row, col);
    board[row][col]->setFlag(row%2==0);
    if (getPointByRowAndCol(row, col).y <= TOUCH_DOWN * (Director::getInstance()->getVisibleSize().height))
    {
        return gameOver(true);
    }

    if(row == -1)
    {
        return gameOver(true);
    }


    std::thread moveBubble(&BubbleLayer::moveTheBubble, this, row, col, (row % 2==0), MOVE_DISTANCE);
    moveBubble.join();
    auto newPos = getPointByRowAndCol(row, col);
    log("[调整后的位置]%f,%f,%d,%d",newPos.x,newPos.y,row,col);
    ready->runAction(Sequence::create(MoveTo::create(0.2f, newPos),CallFunc::create(CC_CALLBACK_0(BubbleLayer::readyAction, this)), nullptr));

}
// 摆正位置后，才会真正消除掉球
void BubbleLayer::readyAction()
{
    setDisable();
    Vec2 RowAndCol = getRowAndColByPoint(ready->getPosition());
    int row = RowAndCol.x;
    int col = RowAndCol.y;
    bool tempFlag;
    if (row % 2 == 0) {
        tempFlag = true;
    } else {
        tempFlag = false;
    }

    if (row < 0)
    {
        row = 0;
    }

    if (col < 0)
    {
        col = 0;
    }

    if (ready->getType() == BUBBLE_TYPE_BOMB)
    {
        bubbleBlast(row, col, tempFlag);
        bubbleBlast(row - 1, col, tempFlag);
        //bubbleBlast(row - 2, col, tempFlag);
    }
    else
    {
        sameSum = 0;
        waitTime = 0.1f;

        if (board[row][col])
        {
            findTheSameBubble(row, col, tempFlag, board[row][col]->getType());
            deleteTheSameBubble(row, col, tempFlag);
        }
    }

    resetAllPass();
    checkDownBubble();
    downBubble();
    changeWaitToReady();
}

bool BubbleLayer::getFirstRowFlag()  //得到第一行是否左缺 不缺为true
{
    for (int i = 0; i < MAX_COLS; ++i)
    {
        if (board[0][i])
        {
            return board[0][i]->getFlag();
        }
    }

    return true;
}

bool BubbleLayer::isCircleCollision(Point pos1, float radius1, Point pos2, float radius2)
{
    if (pos1.getDistance(pos2) > (radius1 + radius2 - 10) || pos2.y > pos1.y)
    {
        return false;
    }

    return true;
}

void BubbleLayer::findTheSameBubble(int i, int j, bool flag, BubbleType type)
{
    setDisable();

    if (i < 0 || i >= MAX_ROWS || j < 0 || j >= MAX_COLS)
    {
        return;
    }

    if (board[i][j] == nullptr)
    {
        return;
    }

    if (board[i][j]->getType() != type)
    {
        return;
    }

    if (board[i][j]->getIsSame())
    {
        return;
    }

    /*
    首先将自己isSame设置为true，并且增加theSame
    从当前位置左上，右上，左下，右下，左，右六个方向进行寻找
    */
    board[i][j]->setIsSame(true);
    ++sameSum;

    if (flag && j > 0 && i > 0)
    {
        findTheSameBubble(i - 1, j - 1, !flag, type);
    }
    else if (!flag && i > 0)
    {
        findTheSameBubble(i - 1, j, !flag, type);
    }

    if (flag && i > 0)
    {
        findTheSameBubble(i - 1, j, !flag, type);
    }
    else if (!flag && i > 0 && j < MAX_COLS - 1)
    {
        findTheSameBubble(i - 1, j + 1, !flag, type);
    }

    if (flag && j > 0 && i < MAX_ROWS)
    {
        findTheSameBubble(i + 1, j - 1, !flag, type);
    }
    else if (!flag && i < MAX_ROWS)
    {
        findTheSameBubble(i + 1, j, !flag, type);
    }

    if (flag && i < MAX_ROWS)
    {
        findTheSameBubble(i + 1, j, !flag, type);
    }
    else if (!flag && i < MAX_ROWS && j < MAX_COLS - 1)
    {
        findTheSameBubble(i + 1, j + 1, !flag, type);
    }

    if (j > 0)
    {
        findTheSameBubble(i, j - 1, flag, type);
    }

    if (j < MAX_COLS)
    {
        findTheSameBubble(i, j + 1, flag, type);
    }

    if (sameSum >= 5)
    {
        waitTime += 0.05f;
        Bubble *obj = board[i][j];
        obj->runAction(Sequence::create(FadeOut::create(waitTime), CallFunc::create([ = ]()
        {
            addScore(obj);
            obj->removeFromParent();
        }), nullptr));
    }
}
void BubbleLayer::bubbleBlast(int i, int j, bool flag)
{
    bubbleAction(board[i][j]);
    board[i][j] = nullptr;
    ready = nullptr;

    if (flag && j > 0 && i > 0 && board[i - 1][j - 1])
    {
        bubbleAction(board[i - 1][j - 1]);
        board[i - 1][j - 1] = nullptr;
    }
    else if (!flag && i > 0 && board[i - 1][j])
    {
        bubbleAction(board[i - 1][j]);
        board[i - 1][j] = nullptr;
    }

    if (flag && i > 0 && board[i - 1][j])
    {
        bubbleAction(board[i - 1][j]);
        board[i - 1][j] = nullptr;
    }
    else if (!flag && i > 0 && j < MAX_COLS - 1 && board[i - 1][j + 1])
    {
        bubbleAction(board[i - 1][j + 1]);
        board[i - 1][j + 1] = nullptr;
    }

    if (flag && j > 0 && i < MAX_ROWS && board[i + 1][j - 1])
    {
        bubbleAction(board[i + 1][j - 1]);
        board[i + 1][j - 1] = nullptr;
    }
    else if (!flag && i < MAX_ROWS && board[i + 1][j])
    {
        bubbleAction(board[i + 1][j]);
        board[i + 1][j] = nullptr;
    }

    if (flag && i < MAX_ROWS && board[i + 1][j])
    {
        bubbleAction(board[i + 1][j]);
        board[i + 1][j] = nullptr;
    }
    else if (!flag && i < MAX_ROWS && j < MAX_COLS - 1 && board[i + 1][j + 1])
    {
        bubbleAction(board[i + 1][j + 1]);
        board[i + 1][j + 1] = nullptr;
    }

    if (j > 0 && board[i][j - 1])
    {
        bubbleAction(board[i][j - 1]);
        board[i][j - 1] = nullptr;
    }

    if (j < MAX_COLS && board[i][j + 1])
    {
        bubbleAction(board[i][j + 1]);
        board[i][j + 1] = nullptr;
    }
}

void BubbleLayer::moveTheBubble(int i, int j, bool flag, float distance)
{

    if (distance <= 1.0f)
    {
        return;
    }

    if (i < 0 || i >= MAX_ROWS || j < 0 || j >= MAX_COLS)
    {
        return;
    }

    if (board[i][j] == nullptr)
    {
        return;
    }

    if (board[i][j]->getIsMove())
    {
        return;
    }

    board[i][j]->setIsMove(true);

    auto dir = (((Vec2)getPointByRowAndCol(i, j) - ready->getPosition()).getNormalized()) * distance;
    auto moveBy = MoveBy::create(0.1f, dir);
    auto seq = Sequence::create(moveBy, moveBy->reverse(), nullptr);
    board[i][j]->runAction(seq);

    if (flag && j > 0 && i > 0)
    {
        moveTheBubble(i - 1, j - 1, !flag, distance - 5);
    }
    else if (!flag && i > 0)
    {
        moveTheBubble(i - 1, j, !flag, distance - 5);
    }

    if (flag && i > 0)
    {
        moveTheBubble(i - 1, j, !flag, distance - 5);
    }
    else if (!flag && i > 0 && j < MAX_COLS - 1)
    {
        moveTheBubble(i - 1, j + 1, !flag, distance - 5);
    }

    if (flag && j > 0 && i < MAX_ROWS)
    {
        moveTheBubble(i + 1, j - 1, !flag, distance - 5);
    }
    else if (!flag && i < MAX_ROWS)
    {
        moveTheBubble(i + 1, j, !flag, distance - 5);
    }

    if (flag && i < MAX_ROWS)
    {
        moveTheBubble(i + 1, j, !flag, distance - 5);
    }
    else if (!flag && i < MAX_ROWS && j < MAX_COLS - 1)
    {
        moveTheBubble(i + 1, j + 1, !flag, distance - 5);
    }

    if (j > 0)
    {
        moveTheBubble(i, j - 1, flag, distance - 5);
    }

    if (j < MAX_COLS)
    {
        moveTheBubble(i, j + 1, flag, distance - 5);
    }
}
void BubbleLayer::addScore(Bubble* obj)
{
    auto gameSceme = (GameScene *)this->getParent();
    curDownNum_++;
    int num = 5 << curDownNum_;
    if(num > 10000)
        num = 10000;
    
	auto label = Label::createWithSystemFont("+ 10", "Arial", 25);
	//obj->addChild(label);
	label->setPosition(obj->getPosition());
	auto fadeout = FadeOut::create(1);
	label->runAction(Sequence::create(fadeout, nullptr));
	addChild(label);
    gameSceme->_propLayer->AddScoreLabel(5 + num);
}
void BubbleLayer::deleteTheSameBubble(int i, int j, bool flag)
{
    if (sameSum < 3)
    {
        for (int i = 0; i < MAX_ROWS; ++i)
        {
            for (int j = 0; j < MAX_COLS; ++j)
            {
                if (board[i][j] != nullptr && board[i][j]->getIsSame())
                {
                    board[i][j]->setIsSame(false);
                    sameSum--;
                }
            }
        }

        setEnable();
        lastHited_ = false;
        hitNums_ = 0;
    }
    else
    {
        
        SimpleAudioEngine::getInstance()->playEffect("Music/Remove.mp3");
        for (int i = 0; i < MAX_ROWS; ++i)
        {
            for (int j = 0; j < MAX_COLS; ++j)
            {
                if (board[i][j] != nullptr && board[i][j]->getIsSame())
                {
                    Bubble *obj = board[i][j];
                    waitTime += 0.05f;
                    ArmatureDataManager::getInstance()->addArmatureFileInfo("BubbleSpecial/baozha.ExportJson");
                    Armature *armature = Armature::create("baozha");
                    obj->addChild(armature);
                    armature->setPosition(R, R);
                    armature->getAnimation()->play("daojubaozha");
                    obj->runAction(Sequence::create(FadeOut::create(waitTime), CallFunc::create([ = ]()
                    {
                        addScore(obj);
                        obj->removeFromParent();
                        setEnable();
                    }), nullptr));
                    board[i][j] = NULL;
                }
            }
        }
        if(lastHited_)
        {
            hitNums_++;
            showHits(hitNums_);
        }
        lastHited_ = true;
        if( hitNums_ > 1)
        {
            showHitNumsAnim();
        }
    }
}

/**
 * 显示连击动画
 */
void BubbleLayer::showHitNumsAnim()
{
    
}

void BubbleLayer::bubbleAction(Bubble *obj)
{
    if(!obj)
        return;
    SimpleAudioEngine::getInstance()->playEffect("Music/Remove.mp3");
    
    
    obj->runAction(Sequence::create(FadeOut::create(waitTime), CallFunc::create([ = ]()
    {
        addScore(obj);
        obj->removeFromParent();
        setEnable();
    }), NULL));
}

void BubbleLayer::callbackRemoveBubble(cocos2d::Node *obj)
{
    auto bubble = dynamic_cast<Bubble *>(obj);

    if (bubble != nullptr)
    {
        Armature *armature = Armature::create("paopaolong");
        armature->getAnimation()->play("daojubaozha");
        obj->addChild(armature);
        armature->setPosition(obj->getContentSize() / 2);
        armature->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_3(BubbleLayer::moveParantCallBack, this));
    }

}
void BubbleLayer::movementPassCallBack(Armature *armature, MovementEventType type, const std::string &name)
{
    if (type == COMPLETE)
    {
        if (name == "gongxiguoguan")
        {
            this->removeChild(armature);
            _level++;

            if (_level >= MAX_CUS)
            {
                return;
            }

            this->initTheBoard(_level);
            UserData::getInstance()->addLevel(1);
            _havePass = false;
        }

    }
}

void BubbleLayer::moveParantCallBack(Armature *armature, MovementEventType type, const std::string &name)
{
    if (type == COMPLETE)
    {
        {
            auto bubble = (Bubble *)armature->getParent();
            bubble->removeFromParentAndCleanup(true);
            sameSum--;

            if (sameSum == 0)
            {
                setEnable();
            }
        }
    }
}
void BubbleLayer::jumpActionCallBack()
{
    for (int i = 0; i < MAX_WAIT_PAOPAO - 1; ++i)
    {
        wait[i] = wait[i + 1];
    }

    wait[MAX_WAIT_PAOPAO - 1] = randomPaoPao();
    this->addChild(wait[MAX_WAIT_PAOPAO - 1], -1);

    for (int i = 0; i < MAX_WAIT_PAOPAO; ++i)
    {
        wait[i]->setPosition(Point(WAIT_PAOPAO_POS));
    }
}
void BubbleLayer::resetAllPass()
{
    for (int i = 0; i < MAX_ROWS; ++i)
    {
        for (int j = 0; j < MAX_COLS; ++j)
        {
            if (board[i][j])
            {
                board[i][j]->setIsPass(false);
                board[i][j]->setIsMove(false);
            }
        }
    }
}

void BubbleLayer::checkDownBubble()
{
    for (int i = 0; i < MAX_COLS; ++i)
    {
        if (board[0][i])
        {
            board[0][i]->setIsPass(true);
        }
    }

    for (int i = 0; i < MAX_ROWS; ++i)
    {
        // 当第一次的时候横着只关心右边，第二次的时候横着只关心左边剩下关心与自己相关的下面两个
        for (int j = 0; j < MAX_COLS; ++j)
        {
            if (board[i][j] && board[i][j]->getIsPass()) // 第一排已经设置为true，否则这里进入不了
            {
                if (j < MAX_COLS - 1 && board[i][j + 1]) // 同一排右边直接设为true
                {
                    board[i][j + 1]->setIsPass(true);
                }
                if (i < MAX_ROWS - 1)
                {
                    if (board[i][j]->getFlag() && j > 0 && board[i + 1][j - 1])
                    {
                        board[i + 1][j - 1]->setIsPass(true); // 有标记的，右侧移动了一点，第二排左边设为TRUE
                    }
                    else if (!(board[i][j]->getFlag()) && board[i + 1][j])
                    {
                        board[i + 1][j]->setIsPass(true);
                    }

                    if (board[i][j]->getFlag() && board[i + 1][j])
                    {
                        board[i + 1][j]->setIsPass(true);
                    }
                    else if (!(board[i][j]->getFlag()) && j < MAX_COLS - 1 && board[i + 1][j + 1])
                    {
                        board[i + 1][j + 1]->setIsPass(true);
                    }
                }
            }
        }

        for (int j = MAX_COLS - 1; j >= 0; --j)
        {
            if (board[i][j] && board[i][j]->getIsPass())
            {
                if (j > 0 && board[i][j - 1])
                {
                    board[i][j - 1]->setIsPass(true);
                }

                if (i < MAX_ROWS - 1)
                {
                    if (board[i][j]->getFlag() && j > 0 && board[i + 1][j - 1])
                    {
                        board[i + 1][j - 1]->setIsPass(true);
                    }
                    else if (!(board[i][j]->getFlag()) && board[i + 1][j])
                    {
                        board[i + 1][j]->setIsPass(true);
                    }

                    if (board[i][j]->getFlag() && board[i + 1][j])
                    {
                        board[i + 1][j]->setIsPass(true);
                    }
                    else if (!(board[i][j]->getFlag()) && j < MAX_COLS - 1 && board[i + 1][j + 1])
                    {
                        board[i + 1][j + 1]->setIsPass(true);
                    }
                }
            }
        }
    }
}

void BubbleLayer::downBubble()
{
    for (int i = 0; i < MAX_ROWS; ++i)
    {
        for (int j = 0; j < MAX_COLS; ++j)
        {
            if (board[i][j] && !(board[i][j]->getIsPass()))
            {
                Bubble *obj = board[i][j];
                downBubbleAction(obj);
                board[i][j] = NULL;
            }
        }
        setEnable();
    }
    // 游戏开始的地方
    if (!isGameOver() || _havePass)
        return;
 
    callJava("showAds","");
    
    _havePass = true;
    setDisable();
    auto gameScene = (GameScene *)this->getParent();
    gameScene->_propLayer->setVisible(false);

    auto cur_level = UserData::getInstance()->getSelLevel();
    auto score = UserData::getInstance()->getScore();
    int last_time = gameScene->_propLayer->getMoveNumber();

    score += last_time * 100;

    UserData::getInstance()->setScore(score);

    UserData::getInstance()->setScore(cur_level,score);

    GameResult *pl = GameResult::create("game_start.png");
    pl->setContentSize(Size(540, 960));
    pl->setTitle("", 30);
    pl->setContentText("", 33, 80, 150);
    pl->setCallbackFunc(this, callfuncN_selector(BubbleLayer::buttonCallback));

    pl->addButton("start_bt.png", "start_bt.png", Vec2(540/2, 300), BT_OK);

    this->addChild(pl, 2000);

    if(UserData::getInstance()->getLevel() <= UserData::getInstance()->getSelLevel())
    {
        UserData::getInstance()->addLevel(1);
    }
}

void BubbleLayer::buttonCallback(Node* obj)
{
    auto s = HelpScene::scene();
    auto t = TransitionFade::create(0.5, s);
    Director::getInstance()->replaceScene(t);
}
void BubbleLayer::downBubbleAction(Bubble *obj)
{
 
    float offY = 200.0;
    Point pos = obj->getPosition();
    obj->runAction(Sequence::create(MoveTo::create((pos.y - offY) / 600.0, Point(pos.x, offY)), CallFuncN::create(CC_CALLBACK_1(BubbleLayer::downBubbleActionCallBack, this)), NULL));
}

void BubbleLayer::downBubbleActionCallBack(Node *obj)
{
    auto bubble = dynamic_cast<Bubble *>(obj);

    auto particle = ParticleSystemQuad::create("Particle/luoxia_lizi.plist");
    particle->setPosition(bubble->getContentSize().width / 2, 0);
    bubble->addChild(particle);
    bubble->runAction(Sequence::create(DelayTime::create(0.5f), FadeOut::create(0.1f), CallFunc::create([ = ]()
    {
        addScore(bubble);
        bubble->removeFromParentAndCleanup(true);
    }), nullptr));
}
void BubbleLayer::initBubbleAction(Bubble *obj, int i, int j)
{
    setDisable();
    auto point = getPointByRowAndCol(i, j);
    auto start = Point(point.x, 300.0f - i * R * 2);
    obj->setPosition(start);
    auto moveTo = MoveTo::create(0.4f + j * 0.1f, point);
    obj->runAction(Sequence::create(moveTo, CallFunc::create([ = ]()
    {
        setEnable();
    }), nullptr));
}

void BubbleLayer::gameOver(bool over)
{
    auto gameSceme = (GameScene *)this->getParent();
    gameSceme->gameOver(over);
}

void BubbleLayer::swapBubble()
{
    auto readyPoint = ready->getPosition();
    auto waitPoint = wait[0]->getPosition();

    ready->runAction(MoveTo::create(0.1f, waitPoint));
    wait[0]->runAction(MoveTo::create(0.1f, readyPoint));

    auto temp = ready;
    ready = wait[0];
    wait[0] = temp;

    throwBallAction();
}
void BubbleLayer::colorBubble()
{
    ready->setType(BUBBLE_TYPE_COLOR);
    ready->setSpriteFrame(BUBBLE_COLOR_NAME.c_str());
}
void BubbleLayer::bombBubble()
{
    ready->setType(BUBBLE_TYPE_BOMB);
    ready->initWithSpriteFrameName(BUBBLE_BOMB_NAME);
}
void BubbleLayer::auxiliaryLine(Point tagrat)
{
    auto node = Node::create();
    addChild(node);
    node->setTag(100);


    auto speed = 30.0f;
    auto position = Point(READY_PAOPAO_POS.x + real.x * speed, READY_PAOPAO_POS.y + real.y * speed);
    CCLOG("%f,%f", real.x, real.y);

    while (position.y < TOUCH_TOP * Director::getInstance()->getVisibleSize().height - R)
    {
        for (int i = MAX_ROWS - 1; i >= 0; i--)
        {
            for (int j = 0; j < MAX_COLS; j++)
            {
                if (board[i][j] != nullptr)
                {
                    if ((board[i][j]->getPosition()).getDistance(position) <= R * 1.5)
                    {
                        return;
                    }
                }
            }
        }

        if (position.x <= R || position.x >= Director::getInstance()->getVisibleSize().width - R)
        {
            real.x = -real.x;
        }

        position = Point(position.x + real.x * speed, position.y + real.y * speed);
        auto line = Sprite::createWithSpriteFrameName("line.png");
        node->addChild(line);
        line->setPosition(position);
    }
}
void BubbleLayer::setReadyAngle(Point target)
{
    auto angle = (target - READY_PAOPAO_POS).getAngle(Vec2(0, 1));
    ready->setRotation(CC_RADIANS_TO_DEGREES(angle));
}
void BubbleLayer::throwBallAction()
{
}

bool BubbleLayer::isGameOver()
{
    int num = 0;
    for (int i = 0; i < MAX_ROWS; ++i)
    {
        for (int j = 0; j < MAX_COLS; ++j)
        {
            if (!board[i][j])
            {
                continue;
            }
            num++;
        }
    }
    if (num < 6)
    {
        return true;
    }
    
    return false;
}

bool BubbleLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
	curDownNum_ = 0;
	return true;
}


void BubbleLayer::showWinAnim(Vec2& pos)
{
    auto size = Director::getInstance()->getWinSize();
    
    ActionInterval* move = MoveTo::create(1.f, pos);
    ActionInterval* scale = ScaleTo::create(1.0f, 0.9f);
    ActionInterval* sineIn = EaseBackIn::create(move);
    
    FiniteTimeAction * spawn = Spawn::create(sineIn, scale, NULL);
    
    auto a = Sprite::create("star.png");
    a->setPosition(size.width*2, size.height/2);
    a->setScale(6, 6);
    addChild(a, 10);
    
    CallFuncN* callback = CallFuncN::create(CC_CALLBACK_1(BubbleLayer::starCallback, this));
    a->runAction(Sequence::create(spawn, callback, NULL));


}

void BubbleLayer::starCallback(Ref* obj)
{
	
}

void BubbleLayer::onTouchMoved(Touch *touch, Event *unused_event)
{
    
    auto gameScene = (GameScene *)this->getParent();
    if(getChildByTag(100))
        this->removeChildByTag(100);

    if (touch->getLocation().y <= TOUCH_DOWN * Director::getInstance()->getVisibleSize().height || touch->getLocation().y >= TOUCH_TOP * Director::getInstance()->getVisibleSize().height)
    {
        return;
    }

    real = (touch->getLocation() - READY_PAOPAO_POS).getNormalized();

    if (real.x <= 0.9 && real.x >= -0.9 && real != Vec2::ZERO && real.y > 0)
    {
        this->auxiliaryLine(touch->getLocation());
        this->setReadyAngle(touch->getLocation());
        gameScene->setCannonAngle(touch->getLocation());
    }

}

void BubbleLayer::onTouchEnded(Touch *touch, Event *unused_event)
{

    auto gameScene = (GameScene *)this->getParent();
    if(getChildByTag(100))
        this->removeChildByTag(100);

    if (touch->getLocation().y <= TOUCH_DOWN * Director::getInstance()->getVisibleSize().height && touch->getLocation().x <= 200)
    {
        this->swapBubble();
    }

    if (touch->getLocation().y <= TOUCH_DOWN * Director::getInstance()->getVisibleSize().height || touch->getLocation().y >= TOUCH_TOP * Director::getInstance()->getVisibleSize().height)
    {
        _listener->setEnabled(true);
        return;
    }

    real = (touch->getLocation() - READY_PAOPAO_POS).getNormalized();

    if (real.x <= 0.9 && real.x >= -0.9 && real != Vec2::ZERO && real.y > 0)
    {
        gameScene->setCannonAngle(touch->getLocation());
        this->onTouch(touch->getLocation());
        gameScene->_propLayer->setCannonAction(touch->getLocation());
        gameScene->_propLayer->subMoveNumber();
    }

}






