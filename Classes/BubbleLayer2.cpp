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
using namespace CocosDenshion;
using namespace cocostudio::timeline;
using namespace std;
static int sameSum = 0;

Scene *BubbleLayer2::scene()
{
    Scene *scene = Scene::create();
    BubbleLayer2 *layer = BubbleLayer2::create();
    scene->addChild(layer);
    return scene;
}
void BubbleLayer2::dump()
{
    log("-------------------------------------");

    for (int i = 0; i < MAX_ROWS; ++i)
    {
        string str = "";

        for (int j = 0; j < MAX_COLS; ++j)
        {
            if (j == 0)
            {
                str += "{";
            }

            if (!board[i][j])
            {
                str += "0";
            }
            else
            {
                int num = (int)board[i][j]->getType();
                str += TI()->itos(num);
            }

            if (j < MAX_COLS - 1)
            {
                str += ",";
            }

            if (j == MAX_COLS - 1)
            {
                str += "},";
            }
        }

        log(str.c_str());
    }
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


bool BubbleLayer2::init()
{
    if (!Layer::init())
    {
        return false;
    }

    markDesign();
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

    if (!load())
    {
        initTheBoard(USER()->getSelLevel());
    }

    this->scheduleUpdate();
    return true;
}

Bubble *BubbleLayer2::randomPaoPao(int flag)
{
    Bubble *pRet = NULL;
    currentColor_ = USER()->getDesignColor();
    BubbleType type = (BubbleType)currentColor_;

    if (flag == 1)
    {
        type = static_cast<BubbleType>(rand() % BUBBLE_COUNT + 1);
    }

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

    return Point(x, y);
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
        obj->setVisible(false);
        this->addChild(obj);
    }
}
void BubbleLayer2::initReadyPaoPao()
{
    ready = randomPaoPao();
    ready->setPosition(READY_PAOPAO_POS);
    ready->setVisible(false);
    this->addChild(ready);

}

void BubbleLayer2::onTouch(Point target)
{
    if (clickDesignArea(target))
    {
        auto a = getRowAndColByPoint(target);
        int i = a.x;
        int j = a.y;

        if (j >= MAX_COLS)
        {
            return;
        }

        if (i >= MAX_ROWS)
        {
            return;
        }

        if (board[i][j] == nullptr)
        {
            if ((BubbleType)currentColor_  != 8)
            {

                board[i][j] = Bubble::initWithType((BubbleType)currentColor_, 1);
                board[i][j]->setPosition(getPointByRowAndCol(i, j));
                board[i][j]->setFlag((i % 2) == 0);
                addChild(board[i][j]);
            }
        }
        else
        {
            auto obj = board[i][j];

            if (obj->getType() == (BubbleType)currentColor_ || (BubbleType)currentColor_  == 8)
            {
                removeChild(board[i][j]);
                board[i][j] = nullptr;
            }
            else
            {
                removeChild(board[i][j]);
                board[i][j] = Bubble::initWithType((BubbleType)currentColor_, 1);
                board[i][j]->setPosition(getPointByRowAndCol(i, j));
                board[i][j]->setFlag((i % 2) == 0);
                addChild(board[i][j]);
            }
        }

        dump();
        save();
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
    randomPaoPao();
}
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
    return false;
}

void BubbleLayer2::changeWaitToReady() {}

// 正在运动球停止了，摆正这个球的位置
void BubbleLayer2::correctReadyPosition() {}
// 摆正位置后，才会真正消除掉球
void BubbleLayer2::readyAction() {}
bool BubbleLayer2::getFirstRowFlag()
{
    return true;
}
bool BubbleLayer2::isCircleCollision(Point pos1, float radius1, Point pos2, float radius2)
{
    return true;
}
void BubbleLayer2::findTheSameBubble(int i, int j, bool flag, BubbleType type) {}
void BubbleLayer2::bubbleBlast(int i, int j, bool flag) {}
void BubbleLayer2::moveTheBubble(int i, int j, bool flag, float distance) {}
void BubbleLayer2::deleteTheSameBubble(int i, int j, bool flag) {}
/**
 * 显示连击动画
 */
void BubbleLayer2::showHitNumsAnim() {}

void BubbleLayer2::bubbleAction(Bubble *obj) {}

void BubbleLayer2::callbackRemoveBubble(cocos2d::Node *obj) {}
void BubbleLayer2::movementPassCallBack(Armature *armature, MovementEventType type, const std::string &name) {}
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

void BubbleLayer2::checkDownBubble() {}
void BubbleLayer2::downBubble() {}
void BubbleLayer2::buttonCallback(Node *obj)
{
    auto s = HelpScene::scene();
    auto t = TransitionFade::create(0.5, s);
    Director::getInstance()->replaceScene(t);
}
void BubbleLayer2::downBubbleAction(Bubble *obj) {}

void BubbleLayer2::downBubbleActionCallBack(Node *obj) {}
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

void BubbleLayer2::gameOver(bool over) {}

void BubbleLayer2::swapBubble() {}
void BubbleLayer2::markDesign()
{
    PropLayer::isDesign = true;
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
    return false;
}
bool BubbleLayer2::onTouchBegan(Touch *touch, Event *unused_event)
{
    return true;
}
void BubbleLayer2::showWinAnim(Vec2 &pos) {}
void BubbleLayer2::starCallback(Ref *obj) {}
void BubbleLayer2::onTouchMoved(Touch *touch, Event *unused_event) {}
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

bool BubbleLayer2::initTheBoard(int level)
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

            board[i][j]->setString(i, j);

            addChild(board[i][j]);
            initBubbleAction(board[i][j], i, j);
        }
    }

    return bRet;
}
// 序列化，把每个关卡的设计都存下来，在手机上怎么方便的转存到电脑上？
// 给你自己的邮箱发个邮件？"0_0:1,0_1:2"
void BubbleLayer2::save()
{
    stringstream saveStr;

    for (int i = 0; i < MAX_ROWS; i++)
    {
        for (int j = 0; j < MAX_COLS; ++j)
        {
            if (!board[i][j])
            {
                saveStr << "0,";
                continue;
            }

            saveStr << board[i][j]->getType() << ",";
        }
    }

    USER()->setDesign(USER()->getSelLevel(), saveStr.str());
}

bool BubbleLayer2::load()
{
    string s = USER()->getDesign(USER()->getSelLevel());

    if (s == "")
    {
        return false;
    }

    vector<string> items = TI()->split(s, ',');
    int index = 0;

    for (int i = 0; i < MAX_ROWS; i++)
    {
        for (int j = 0; j < MAX_COLS; ++j)
        {
            if (index >= items.size())
            {
                break;
            }

            auto type = TI()->stoi(items[index]);

            if (type > 0)
            {
                auto sp =  Bubble::initWithType((BubbleType)type);
                board[i][j] = sp;
                addChild(sp);
                board[i][j]->setFlag((i % 2) == 0);
                board[i][j]->setString(i, j);
                initBubbleAction(board[i][j], i, j);
            }

            index ++ ;
        }
    }

    return true;
}
