#include "PropLayer.h"
#include "GameScene.h"
#include "UserData.h"
#include "GameConst.h"
#include "PauseLayer.h"
#include "editor-support/cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"

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
const int MAX_TIME = 300;

bool PropLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	setTime(MAX_TIME);
	_propLayer = CSLoader::createNode("PropLayer.csb");
	auto frameSize = Director::getInstance()->getVisibleSize();
	_propLayer->setContentSize(frameSize);
	ui::Helper::doLayout(_propLayer);
	addChild(_propLayer);

    if (UserData::getInstance()->getOpenBox())
    {
        UserData::getInstance()->setOpenBox(false);
        menuHourglassCallBack(this);
    }

	auto bomb =  (ui::ImageView*)_propLayer->getChildByTag(24);
    bomb->setVisible(false);

	auto hourglass = (ui::ImageView*)_propLayer->getChildByTag(23);
    hourglass->setVisible(false);

	auto colorBubble = (ui::ImageView*)_propLayer->getChildByTag(22);
    colorBubble->setVisible(false);
    
	auto pauseMenu = (ui::Button*)_propLayer->getChildByTag(36);
	pauseMenu->addClickEventListener(CC_CALLBACK_1(PropLayer::menuPauseCallBack, this));

    auto propArmature = (Armature *)_propLayer->getChildByTag(68);
    propArmature->setVisible(false);
	scheduleUpdate();
    
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
    
    auto menu = Menu::create(b,c,nullptr);
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
	auto bomb = (ui::ImageView*)_propLayer->getChildByTag(24);
	bomb->addClickEventListener(CC_CALLBACK_1(PropLayer::menuBombCallBack, this));
	auto bombText = (ui::TextBMFont*)bomb->getChildByTag(152);
	bombText->setString(StringUtils::format("%d", UserData::getInstance()->getBomb()));
}

void PropLayer::setColorBubbleNum()
{
	auto colorBubble = (ui::ImageView*)_propLayer->getChildByTag(22);
	colorBubble->addClickEventListener(CC_CALLBACK_1(PropLayer::menuColorBubbleCallBack, this));
	auto colorBubbleText = (ui::TextBMFont*)colorBubble->getChildByTag(150);
	colorBubbleText->setString(StringUtils::format("%d", UserData::getInstance()->getColorBubble()));
}


void PropLayer::menuBombCallBack(Ref* Psender)
{
	auto gameSceme = (GameScene*)this->getParent();
	gameSceme->bombBubble();
}
// 增加时间
void PropLayer::menuHourglassCallBack(Ref* Psender)
{
	auto hourglass = (ui::ImageView*)_propLayer->getChildByTag(23);
	hourglass->addClickEventListener(CC_CALLBACK_1(PropLayer::menuHourglassCallBack, this));
	auto hourglassText = (ui::TextBMFont*)hourglass->getChildByTag(151);
	hourglassText->setString(StringUtils::format("%d", UserData::getInstance()->getHourglass()));

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

	auto timeLabel = (ui::TextBMFont*)_propLayer->getChildByTag(131);
 	timeLabel->setString(StringUtils::format("%d", (int)getTime()));

	auto loadingBar = (ui::LoadingBar*)_propLayer->getChildByTag(29);
	loadingBar->setPercent(getTime()/60.0 * 100);

	auto armature = (Armature*)loadingBar->getChildByTag(125);
	float wight = loadingBar->getContentSize().width;
	armature->setPosition(211- wight*(1 - getTime() / 60.0), 13);

	auto levelLabel = (ui::TextBMFont*)_propLayer->getChildByTag(122);
	auto level = StringUtils::format("%d", UserData::getInstance()->getSelLevel());
	auto timeSptite = (Sprite*)_propLayer->getChildByTag(46);

	if (levelLabel->getString() != level)
	{
		levelLabel->setString(level);
	}
	if (getTime() <= 0)
	{
		auto gameSceme = (GameScene*)this->getParent();
		gameSceme->gameOver();
	}
	else if (getTime() <= 5)
	{
		
		auto currentTime = (ui::TextBMFont*)timeSptite->getChildByTag(132);
		if (currentTime->getString() != StringUtils::format("%d", (int)getTime()))
		{
			SimpleAudioEngine::getInstance()->playEffect("Music/Clock.mp3");
			currentTime->setString(StringUtils::format("%d", (int)getTime()));
		}
		
		if (!timeSptite->isVisible())
		{
 			auto point = timeSptite->getPosition();
			timeSptite->setPosition(650, point.y);
 			timeSptite->setVisible(true);
			auto moveAction = MoveTo::create(0.5f, point);
			auto speedAction = EaseSineOut::create(moveAction);
			auto callFunc = CallFunc::create(CC_CALLBACK_0(PropLayer::timeCallFunc, this));
			auto seq = Sequence::create(speedAction, callFunc, nullptr);
 			timeSptite->runAction(seq);
		}
	}
	else
	{
		if (timeSptite->isVisible())
		{
			timeSptite->setVisible(false);
		}
	}
}
void PropLayer::AddScoreLabel(int var)
{
	auto scoreLabel = (ui::TextBMFont*)_propLayer->getChildByTag(123);
	UserData::getInstance()->addScore(var);
	scoreLabel->setString(StringUtils::format("%d", UserData::getInstance()->getScore()));
}
void PropLayer::setCannonAngle(Point target)
{
	auto cannon = (Sprite*)_propLayer->getChildByTag(38);
	auto angle = (target - READY_PAOPAO_POS).getAngle(Vec2(0, 1));
	cannon->setRotation(CC_RADIANS_TO_DEGREES(angle));
}

void PropLayer::setCannonAction(Point target)
{
	auto cannon = (Sprite*)_propLayer->getChildByTag(38);

	auto dir = -10 * (target - READY_PAOPAO_POS).getNormalized();
	auto moveBy = MoveBy::create(0.1f, dir);
	auto seq = Sequence::create(moveBy, moveBy->reverse(), nullptr);
	cannon->runAction(seq);
}

void PropLayer::timeCallFunc()
{
	auto timeSptite = (Sprite*)_propLayer->getChildByTag(46);
	auto time_bg = (Sprite*)timeSptite->getChildByTag(45);
	auto rotateAction = RotateBy::create(1.0f, -360.0f);
	auto repeatAction = RepeatForever::create(rotateAction);
	time_bg->runAction(repeatAction);
}
