/**
 * desc : 关卡编辑页面, 打开 DESIGN_MODE宏定义,进入关卡的是编辑界面
 * auth ： jiangxf@2019.3.22
 */

#include "BubbleLayer2.h"
#include "GameScene.h"
#include "UserData.h"
#include "SimpleAudioEngine.h"
#include "PropLayer.h"
#include <thread>
#include "HelpScene.h"
#include "GameResult.h"
#include "NDKHelper.h"

const int BT_OK = 2401;

using namespace CocosDenshion;
using namespace cocostudio::timeline;
using namespace std;

static float waitTime = 0.1f;
static int sameSum = 0;


Scene *BubbleLayer2::scene()
{
    Scene *scene = Scene::create();
    BubbleLayer2 *layer = BubbleLayer2::create();
    scene->addChild(layer);
    return scene;
}

void BubbleLayer2::calcRetainMap()
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
void BubbleLayer2::showHits(int num)
{
}

bool BubbleLayer2::init()
{
    if (!Layer::init())
    {
        return false;
    }
    _level = UserData::getInstance()->getSelLevel();
    
    UserData::getInstance()->setScore(0);
    _listener = EventListenerTouchOneByOne::create();
    _listener->setSwallowTouches(true);
    _listener->onTouchBegan = CC_CALLBACK_2(BubbleLayer2::onTouchBegan, this);
    _listener->onTouchMoved = CC_CALLBACK_2(BubbleLayer2::onTouchMoved, this);
    _listener->onTouchEnded = CC_CALLBACK_2(BubbleLayer2::onTouchEnded, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_listener, this);

    calcRetainMap();
    initWaitPaoPao();
    initReadyPaoPao();
    hitedNumLabel_ = Label::createWithSystemFont("0 hits", "Arial", 30);
    addChild(hitedNumLabel_, 1000);
    hitedNumLabel_->setPosition(1380, 300);
    this->setMoveNumber(0);
    moveLabel_ = TI()->addLabel(this, std::string("Moves:"), 1000.0f, 50.0f, 1000);
    moveNumberLabel_ = TI()->addLabel(this, std::string("0"), 1100.0f, 50.0f, 1000);
    selectedBubble_ = TI()->addLabel(this, std::string("选择球的颜色"), 50.0f, 450.0f, 1000);
    showSelectedBubble_ = TI()->addLabel(this, std::string("0"), 150.0f, 450.0f, 1000);
    return true;
}


bool BubbleLayer2::initTheBoard(int level)
{
    return true;
}

Bubble *BubbleLayer2::randomPaoPao(int flag)
{
    Bubble *pRet = NULL;
    BubbleType type = (BubbleType)currentColor_;
    pRet = Bubble::initWithType(type);
    ready = pRet;
    return pRet;
}

// 根据行、列确定球的位置
Point BubbleLayer2::getPointByRowAndCol(int row, int col)
{
    bool flag = (row % 2 == 0);
    Size winSize = Director::getInstance()->getWinSize();
    auto x = (col * 2 + 1) * (R + 1) + (flag ? 0 : R);
    auto y = TOUCH_TOP * winSize.height - row * (R * 2 - 5) - R;
    
    return Point(x,y);
}

Vec2 BubbleLayer2::getRowAndColByPoint(Point target)
{
    Size winSize = Director::getInstance()->getWinSize();
    int x = (TOUCH_TOP * winSize.height - target.y) / (R * 2 - 5);
    int y = ((target.x - (x % 2) * R) / ((R + 1) * 2));
    
    return Vec2(x, y);
}
void BubbleLayer2::initWaitPaoPao()
{
    for (int i = 0; i < MAX_WAIT_PAOPAO; ++i)
    {
        Bubble *obj = randomPaoPao();
        obj->setPosition(WAIT_PAOPAO_POS);
        wait[i] = obj;
        this->addChild(obj);
    }
}
void BubbleLayer2::initReadyPaoPao()
{
    ready = randomPaoPao();
    ready->setPosition(READY_PAOPAO_POS);
    this->addChild(ready);
}

void BubbleLayer2::onTouch(Point target)
{
    if(clickDesignArea(target))
    {
        auto a = getRowAndColByPoint(target);
        int i = a.x;
        int j = a.y;
        if(board[i][j] == nullptr)
        {
            board[i][j] = Bubble::initWithType((BubbleType)currentColor_, 1);
            board[i][j]->setPosition(getPointByRowAndCol(i,j));
            board[i][j]->setFlag((i % 2) == 0);
            addChild(board[i][j]);
        }
        else
        {
            removeChild(board[i][j]);
            board[i][j] = nullptr;
        }
    }
    
    this->scheduleUpdate();
}
void BubbleLayer2::setEnable()
{
    _listener->setEnabled(true);
}
void BubbleLayer2::setDisable()
{
    _listener->setEnabled(false);
}

void BubbleLayer2::update(float fDelta)
{
}
// 是否碰撞了边界
bool BubbleLayer2::isCollideBorder()
{
    Size size = Director::getInstance()->getWinSize();
    Point pos = ready->getPosition();
    return (pos.x + R > size.width || pos.x - R / 2 < 0);
}

// 检查是否碰撞到附近的球，在update中如果碰不到附近的球，球就一直运动
// 碰到附近的球了就停止运动
bool BubbleLayer2::checkCollideBorder()
{
    bool bRet = false;
    auto winSize = Director::getInstance()->getVisibleSize();
    auto point = ready->getPosition();

    /* 底部的边界 */
    if (point.y < TOUCH_DOWN * winSize.height)
    {
        return false;
    }

    if (ready->getPosition().y > TOUCH_TOP * winSize.height - R)
    {
        if (ready->getType() == BUBBLE_TYPE_COLOR)
        {
            BubbleType type = (BubbleType)((int)(CCRANDOM_0_1() * 7 + 1));
            ready->setType(type);
            ready->initWithSpriteFrameName(StringUtils::format(BUBBLE_NAME.c_str(), type));
        }
        bRet = true;
    }

    std::vector<Vec2> rowCol;
    rowCol.push_back(getRowAndColByPoint(Point(point.x, point.y + R)));
    rowCol.push_back(getRowAndColByPoint(Point(point.x - R, point.y)));
    rowCol.push_back(getRowAndColByPoint(Point(point.x + R, point.y)));

    for (auto & ti : rowCol)
    {
        if (board[int(ti.x)][int(ti.y)] != nullptr)
        {
            return true;
        }
    }
    return bRet;
}

void BubbleLayer2::changeWaitToReady()
{
    ready = wait[0];
    auto jumpAction = JumpTo::create(0.1f, READY_PAOPAO_POS, 30.0f, 1);
    auto callFunc = CallFunc::create(CC_CALLBACK_0(BubbleLayer2::jumpActionCallBack, this));
    auto seq = Sequence::create(jumpAction, callFunc, nullptr);
    ready->runAction(seq);
}

// 正在运动球停止了，摆正这个球的位置
void BubbleLayer2::correctReadyPosition()
{
}
// 摆正位置后，才会真正消除掉球
void BubbleLayer2::readyAction()
{
}

bool BubbleLayer2::getFirstRowFlag()  //得到第一行是否左缺 不缺为true
{
    return true;
}

bool BubbleLayer2::isCircleCollision(Point pos1, float radius1, Point pos2, float radius2)
{
    return true;
}

void BubbleLayer2::findTheSameBubble(int i, int j, bool flag, BubbleType type)
{
}
void BubbleLayer2::bubbleBlast(int i, int j, bool flag)
{
}
void BubbleLayer2::moveTheBubble(int i, int j, bool flag, float distance)
{
}

void BubbleLayer2::deleteTheSameBubble(int i, int j, bool flag)
{
}
/**
 * 显示连击动画
 */
void BubbleLayer2::showHitNumsAnim()
{
    
}

void BubbleLayer2::bubbleAction(Bubble *obj)
{
    auto gameSceme = (GameScene *)this->getParent();
    gameSceme->_propLayer->AddScoreLabel(5);
    SimpleAudioEngine::getInstance()->playEffect("Music/Remove.mp3");

    obj->runAction(Sequence::create(FadeOut::create(waitTime), CallFunc::create([ = ]()
    {
        obj->removeFromParent();
        setEnable();
    }), NULL));
}

void BubbleLayer2::callbackRemoveBubble(cocos2d::Node *obj)
{
    auto bubble = dynamic_cast<Bubble *>(obj);
    if (bubble != nullptr)
    {
        Armature *armature = Armature::create("paopaolong");
        armature->getAnimation()->play("daojubaozha");
        obj->addChild(armature);
        armature->setPosition(obj->getContentSize() / 2);
        armature->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_3(BubbleLayer2::moveParantCallBack, this));
    }

}
void BubbleLayer2::movementPassCallBack(Armature *armature, MovementEventType type, const std::string &name)
{
}

void BubbleLayer2::moveParantCallBack(Armature *armature, MovementEventType type, const std::string &name)
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
void BubbleLayer2::jumpActionCallBack()
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
void BubbleLayer2::resetAllPass()
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

void BubbleLayer2::checkDownBubble()
{
}

void BubbleLayer2::downBubble()
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
    if (!isPass() || _havePass)
        return;
    if(UserData::getInstance()->getLevel() > 4)
    {
        callJava("showAds","");
    }
    _havePass = true;
    setDisable();
    auto gameScene = (GameScene *)this->getParent();
    gameScene->_propLayer->setVisible(false);

    auto cur_level = UserData::getInstance()->getSelLevel();
    auto score = UserData::getInstance()->getScore();
    int last_time = gameScene->_propLayer->getTime();

    score += last_time * 100;

    UserData::getInstance()->setScore(score);

    UserData::getInstance()->setScore(cur_level,score);

    GameResult *pl = GameResult::create("game_start.png");
    pl->setContentSize(Size(540, 960));
    pl->setTitle("", 30);
    pl->setContentText("", 33, 80, 150);
    pl->setCallbackFunc(this, callfuncN_selector(BubbleLayer2::buttonCallback));

    pl->addButton("start_bt.png", "start_bt.png", Vec2(540/2, 300), BT_OK);

    this->addChild(pl, 2000);

    if(UserData::getInstance()->getLevel() <= UserData::getInstance()->getSelLevel())
    {
        UserData::getInstance()->addLevel(1);
    }
}

void BubbleLayer2::buttonCallback(Node* obj)
{
    auto s = HelpScene::scene();
    auto t = TransitionFade::create(0.5, s);
    Director::getInstance()->replaceScene(t);
}
void BubbleLayer2::downBubbleAction(Bubble *obj)
{
    auto gameSceme = (GameScene *)this->getParent();
    gameSceme->_propLayer->AddScoreLabel(5);

    float offY = 200.0;
    Point pos = obj->getPosition();
    obj->runAction(Sequence::create(MoveTo::create((pos.y - offY) / 600.0, Point(pos.x, offY)), CallFuncN::create(CC_CALLBACK_1(BubbleLayer2::downBubbleActionCallBack, this)), NULL));
}

void BubbleLayer2::downBubbleActionCallBack(Node *obj)
{
    auto bubble = dynamic_cast<Bubble *>(obj);

    auto particle = ParticleSystemQuad::create("Particle/luoxia_lizi.plist");
    particle->setPosition(bubble->getContentSize().width / 2, 0);
    bubble->addChild(particle);
    bubble->runAction(Sequence::create(DelayTime::create(0.5f), FadeOut::create(0.1f), CallFunc::create([ = ]()
    {
        bubble->removeFromParentAndCleanup(true);
    }), nullptr));
}
void BubbleLayer2::initBubbleAction(Bubble *obj, int i, int j)
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

void BubbleLayer2::gameOver(bool over)
{
    auto gameSceme = (GameScene *)this->getParent();
    gameSceme->gameOver(over);
}

void BubbleLayer2::swapBubble()
{
    if(currentColor_++ > 6)
    {
        currentColor_ = 1;
    }
    showSelectedBubble_->setString(TI()->itos(currentColor_));
    randomPaoPao();
    changeWaitToReady();
}
void BubbleLayer2::colorBubble()
{
    ready->setType(BUBBLE_TYPE_COLOR);
    ready->setSpriteFrame(BUBBLE_COLOR_NAME.c_str());
}
void BubbleLayer2::bombBubble()
{
    ready->setType(BUBBLE_TYPE_BOMB);
    ready->initWithSpriteFrameName(BUBBLE_BOMB_NAME);
}
void BubbleLayer2::auxiliaryLine(Point tagrat)
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
void BubbleLayer2::setReadyAngle(Point target)
{
    auto angle = (target - READY_PAOPAO_POS).getAngle(Vec2(0, 1));
    ready->setRotation(CC_RADIANS_TO_DEGREES(angle));
}
void BubbleLayer2::throwBallAction()
{
    auto gameScene = (GameScene *)this->getParent();

    auto bgNode = (Node *)gameScene->_bg;
    auto bgArmature = (Armature *)bgNode->getChildByTag(63);
    bgArmature->getAnimation()->play("huanqiu");
    bgArmature->setVisible(false);

    auto propLayer = (PropLayer *)gameScene->_propLayer;
    auto propNode = (Node *)propLayer->_propLayer;
    auto propArmature = (Armature *)propNode->getChildByTag(68);
    propArmature->getAnimation()->play("huanqiushou");
    propArmature->setVisible(false);
}

bool BubbleLayer2::isPass()
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

bool BubbleLayer2::onTouchBegan(Touch *touch, Event *unused_event)
{
    return true;
}


void BubbleLayer2::showWinAnim(Vec2& pos)
{
}

void BubbleLayer2::starCallback(Ref* obj)
{
	
}

void BubbleLayer2::onTouchMoved(Touch *touch, Event *unused_event)
{
    
}

void BubbleLayer2::onTouchEnded(Touch *touch, Event *unused_event)
{
    auto gameScene = (GameScene *)this->getParent();
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

    }

}

int BubbleLayer2::getMaxMoveNumbers(int level)
{
    return 10;
}



