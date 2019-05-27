/**
 * desc : ui表现层
 * author : jiangxf @ 2109.05.26
 */
#include "PropLayer.h"
#include "GameScene.h"
#include "UserData.h"
#include "GameConst.h"
#include "PauseLayer.h"
#include "editor-support/cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
#include "Tools.h"

using namespace CocosDenshion;
using namespace cocostudio::timeline;
using namespace cocostudio;

enum NodeTag
{
	Tag_time = 100,
	Tag_score,
	tag_bestScore,
	tag_level,
	tag_currentTime
};

const int MENU_TAG = 10240;
const int GIFT1_TAG = 10241;
const int GIFT2_TAG = 10242;
const int TIME_TAG = 10243;
const int BOMB_TAG = 10244;
const int SHOOTER_TAG = 10245;
const int SCORE_TAG = 10246;
const int MAX_TIME =  30000;
const int CHANGE_TAG = 10247;
const int LEVEL_TAG = 10248;
const int MOVE_TAG = 10249;

void PropLayer::initMoveNumbers()
{
    auto level = USER()->getSelLevel();
   
    moveNumber_ = TI()->getMoveNumbers(level);
    auto label = Label::createWithSystemFont(TI()->itos(moveNumber_), "Arial", 30);
    addChild(label);
    label->setTag(MOVE_TAG);
    label->setPosition(270, 140);
}

void PropLayer::showMoveNumbers()
{
    auto label = (Label*)getChildByTag(MOVE_TAG);
    TI()->showNumber(label, moveNumber_, "");
}
// 显示炮筒
void PropLayer::initShooter()
{
    auto sp = Sprite::create("res/shooter.png");
    addChild(sp);
    sp->setPosition(270, 220);
    sp->setTag(SHOOTER_TAG);
}

void PropLayer::initScoreLabel()
{
    auto scoreLabel = Label::createWithSystemFont("0", "Arial", 30);
    addChild(scoreLabel);
    scoreLabel->setTag(SCORE_TAG);
    scoreLabel->setPosition(270, 910);
}
void PropLayer::initChangeBubbleSprite()
{
    auto sp = Sprite::create("res/change.png");
    
    sp->setTag(CHANGE_TAG);
    sp->setPosition(176, 170);
    addChild(sp);
    auto cr  = RotateTo::create(30, 180);
    auto cr2 = RotateTo::create(30, -180);
    auto cr3 = RotateTo::create(30, 0);
    auto sqAction = Sequence::create(cr,cr2,cr3,nullptr);
    auto rpAction = RepeatForever::create(sqAction);
    sp->runAction(rpAction);
}

void PropLayer::initLevelLabel()
{
    auto sp = Label::createWithSystemFont("Level", "Arial", 30);
    addChild(sp);
    sp->setTag(LEVEL_TAG);
    sp->setPosition(86, 910);
}

void PropLayer::initLevelNumLabel()
{
    auto sp = Label::createWithSystemFont("Level", "Arial", 30);
    addChild(sp);
    sp->setPosition(150 ,910);
    sp->setString(TI()->itos(USER()->getSelLevel()));
}

MenuItemImage* PropLayer::initPauseButton()
{
    auto btn = MenuItemImage::create("res/pause.png", "res/pause.png");
    btn->setCallback(CC_CALLBACK_1(PropLayer::menuPauseCallBack, this));
    btn->setPosition(500, 910);
    return btn;
}

bool PropLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
    
	setTime(MAX_TIME);
    initShooter();
    initScoreLabel();
    
    initLevelLabel();
    initLevelNumLabel();
    initMoveNumbers();
    if (UserData::getInstance()->getOpenBox())
    {
        UserData::getInstance()->setOpenBox(false);
        menuHourglassCallBack(this);
    }

    scheduleUpdate();
    initChangeBubbleSprite();
    
    auto b = MenuItemImage::create("box1.png", "box1.png");
    b->setCallback(CC_CALLBACK_1(PropLayer::buttonCallback,this));
    
    auto c = MenuItemImage::create("box2.png", "box2.png");
    c->setCallback(CC_CALLBACK_1(PropLayer::buttonCallback, this));
    
    b->setTag(GIFT1_TAG);
    c->setTag(GIFT2_TAG);
    
    b->setPosition(50, 200);
    c->setPosition(50, 200);
    
    b->setScale(0.5);
    c->setScale(0.5);
    
    auto r1 = RotateTo::create(0.2, 1);
    auto r2 = RotateTo::create(0.2, -1);
    auto r5 = RotateTo::create(0.2, 0);
    
    auto r3 = RotateTo::create(0.2, 3);
    auto r4 = RotateTo::create(0.2, -3);
    auto r6 = RotateTo::create(0.2, 0);
    auto d1 = DelayTime::create(1);
    auto action_ = Sequence::create(d1,r1,r2,r1,r2,r5, d1,nullptr);
    auto action1_ = Sequence::create(d1,r3,r4,r3,r4,r6,d1,nullptr);
    auto a1 = RepeatForever::create(action_);
    auto a2 = RepeatForever::create(action1_);
    b->runAction(a1);
    c->runAction(a2);
    
    auto btn = initPauseButton();
    auto menu = Menu::create(btn, b, c, nullptr);
    menu->setTag(MENU_TAG);
    addChild(menu);
    menu->setPosition(Vec2::ZERO);
    menu->setAnchorPoint(Vec2::ZERO);
    
	return true;
}

void PropLayer::showOpenBoxAnimi(int flag)
{
    auto a = ParticleSystemQuad::create("BubbleSpecial/yanhua02.plist");
    a->setPosition(50, 200);
    
    auto b = FadeOut::create(0.2);
    auto menu = getChildByTag(MENU_TAG);
    auto box1 = menu->getChildByTag(GIFT1_TAG);
    auto box2 = menu->getChildByTag(GIFT2_TAG);
    auto c = FadeOut::create(0.2);
    box1->runAction(b);
    box2->runAction(c);
    
    auto sp = Sprite::create("time.png");
    sp->setTag(TIME_TAG);
    if(flag == 2)
    {
        sp = Sprite::create("bomb.png");
        sp->setTag(BOMB_TAG);
    }
    
    sp->setScale(0.5);
    addChild(sp);
    sp->setPosition(50, 200);
    auto fi = FadeIn::create(0.5);
    sp->runAction(fi);
    addChild(a);
    UserData::getInstance()->setOpenBox(true);
}

#include "NDKHelper.h"
void PropLayer::buttonCallback(Ref* obj)
{
    if (UserData::getInstance()->getOpenBox())
    {
        auto sp = getChildByTag(TIME_TAG);
        if (sp)
        {
            menuHourglassCallBack(this);
            sp->setVisible(false);
        }
        
        sp = getChildByTag(BOMB_TAG);
        if(sp)
        {
            menuBombCallBack(this);
            sp->setVisible(false);
        }
        
        return;
    }
    callJava("showAds","");
    int a = rand()%2 + 1;
    showOpenBoxAnimi(a);
}

void PropLayer::setBombNum()
{
/*
	auto bomb = (ui::ImageView*)_propLayer->getChildByTag(24);
	bomb->addClickEventListener(CC_CALLBACK_1(PropLayer::menuBombCallBack, this));
	auto bombText = (ui::TextBMFont*)bomb->getChildByTag(152);
	bombText->setString(StringUtils::format("%d", UserData::getInstance()->getBomb()));
*/
}

void PropLayer::setColorBubbleNum()
{
/*
    auto colorBubble = (ui::ImageView*)_propLayer->getChildByTag(22);
	colorBubble->addClickEventListener(CC_CALLBACK_1(PropLayer::menuColorBubbleCallBack, this));
	auto colorBubbleText = (ui::TextBMFont*)colorBubble->getChildByTag(150);
	colorBubbleText->setString(StringUtils::format("%d", UserData::getInstance()->getColorBubble()));
*/
}


void PropLayer::menuBombCallBack(Ref* Psender)
{
	auto gameSceme = (GameScene*)this->getParent();
	gameSceme->bombBubble();
}
// 增加时间
void PropLayer::menuHourglassCallBack(Ref* Psender)
{
	auto time = getTime() + HOURGLASSTIME;
    if (time >= MAX_TIME)
	{	
		time = MAX_TIME;
	}
	setTime(time);
}

void PropLayer::menuColorBubbleCallBack(Ref* Psender)
{
	auto gameSceme = (GameScene*)this->getParent();
	gameSceme->colorBubble();
}

void PropLayer::menuPauseCallBack(Ref* Psender)
{
	auto gameSceme = (GameScene*)this->getParent();
	gameSceme->mPause();
	auto layer = PauseLayer::create();
	gameSceme->addChild(layer);
}

void PropLayer::update(float delta)
{
	setTime(getTime() - 1.0/60.0);
	if (getTime() <= 0)
	{
		auto gameSceme = (GameScene*)this->getParent();
		gameSceme->gameOver();
	}
}

void PropLayer::AddScoreLabel(int var)
{
    auto scoreLabel = (Label*)getChildByTag(SCORE_TAG);
	UserData::getInstance()->addScore(var);
	scoreLabel->setString(StringUtils::format("%d", UserData::getInstance()->getScore()));
}
/**
 * 設置炮筒的角度
 */
void PropLayer::setCannonAngle(Point target)
{
    auto cannon = (Sprite*)this->getChildByTag(SHOOTER_TAG);
	auto angle = (target - READY_PAOPAO_POS).getAngle(Vec2(0, 1));
	cannon->setRotation(CC_RADIANS_TO_DEGREES(angle));
}
/**
 * 設置炮筒的行為
 */
void PropLayer::setCannonAction(Point target)
{
    
	auto cannon = (Sprite*)this->getChildByTag(SHOOTER_TAG);
	auto dir = -10 * (target - READY_PAOPAO_POS).getNormalized();
	auto moveBy = MoveBy::create(0.1f, dir);
	auto seq = Sequence::create(moveBy, moveBy->reverse(), nullptr);
	cannon->runAction(seq);
    
}
/**
 *
 */
void PropLayer::timeCallFunc()
{
    /*
	auto timeSptite = (Sprite*)_propLayer->getChildByTag(46);
	auto time_bg = (Sprite*)timeSptite->getChildByTag(45);
	auto rotateAction = RotateBy::create(1.0f, -360.0f);
	auto repeatAction = RepeatForever::create(rotateAction);
	time_bg->runAction(repeatAction);
     */
}
