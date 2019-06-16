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
#include "NDKHelper.h"
#include "BuyMoveNumber.h"
#include "UserData.h"

using namespace CocosDenshion;
using namespace cocostudio::timeline;
using namespace cocostudio;
bool PropLayer::isDesign = false;

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
const int PAUSE_TAG = 10250;
const int BOMB_BTN_TAG = 10251;
const int BIAO_TAG = 10252;
const int COLOR_TAG = 10253;
const int MORE_BTN_TAG = 10254;
const int BOMB_ICON_BTN_TAG = 10255;
const int BIAO_ICON_BTN_TAG = 10256;
const int COLOR_ICON_BTN_TAG = 10257;
const int MORE_ICON_BTN_TAG = 10258;
const int LABEL_OFFSET = 1000000;
void PropLayer::initMoveNumbers()
{
    auto level = USER()->getSelLevel();
    moveNumber_ = TI()->getMoveNumbers(level);
    auto label = Label::createWithSystemFont(TI()->itos(moveNumber_), "Arial", 30);
    addChild(label);
    label->setTag(MOVE_TAG);
    label->setPosition(270, 140);
    if(isDesign)
    {
        label->setVisible(false);
    }
}

void PropLayer::showMoveNumbers()
{
    auto label = (Label*)getChildByTag(MOVE_TAG);
    TI()->showNumber(label, moveNumber_, "");
    if(moveNumber_ <= 5)
    {
        label->setColor(Color3B::RED);
    }
    else
    {
        label->setColor(Color3B::WHITE);
    }
}
// 显示炮筒
void PropLayer::initShooter()
{
    auto sp = Sprite::create("res/shooter.png");
    addChild(sp);
    sp->setPosition(270, 220);
    sp->setTag(SHOOTER_TAG);
    if(isDesign)
    {
        sp->setVisible(false);
    }
}

void PropLayer::showBuyAds()
{
	auto overLayer = BuyMoveNumber::create();
	this->addChild(overLayer);
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
    if (isDesign)
    {
        return;
    }
    auto sp = Sprite::create("res/change.png");
    
    sp->setTag(CHANGE_TAG);
    sp->setPosition(318, 155);
	sp->setScale(0.3);
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

void PropLayer::initBox()
{
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
}

void PropLayer::initItemBtn()
{
	auto menu = getChildByTag(MENU_TAG);
	auto bomb = MenuItemImage::create("bomb_btn.png","bomb_btn.png");
	auto biao = MenuItemImage::create("biao_btn.png","biao_btn.png");
	auto col_btn = MenuItemImage::create("color_btn.png","color_btn.png");
	auto more_btn = MenuItemImage::create("add_btn.png","add_btn.png");

	bomb->setPosition(63, 50);
	biao->setPosition(201, 50);
	col_btn->setPosition(343, 50);
	more_btn->setPosition(472, 50);

	bomb->setCallback(CC_CALLBACK_1(PropLayer::buttonCallback, this));
	biao->setCallback(CC_CALLBACK_1(PropLayer::buttonCallback, this));
	col_btn->setCallback(CC_CALLBACK_1(PropLayer::buttonCallback, this));
	more_btn->setCallback(CC_CALLBACK_1(PropLayer::buttonCallback, this));


	bomb->setTag(BOMB_BTN_TAG);
	biao->setTag(BIAO_TAG);
	col_btn->setTag(COLOR_TAG);
	more_btn->setTag(MORE_BTN_TAG);
	
	menu->addChild(bomb);
	menu->addChild(biao);
	menu->addChild(col_btn);
	menu->addChild(more_btn);
	
	showItemIcon(bomb, USER()->getBombItemNum(), Vec2(110, 21), BOMB_ICON_BTN_TAG);
	showItemIcon(biao, USER()->getBiaoItemNum(), Vec2(110, 21), BIAO_ICON_BTN_TAG);
	showItemIcon(col_btn, USER()->getColorItemNum(), Vec2(110, 21), COLOR_ICON_BTN_TAG);
	showItemIcon(more_btn, USER()->getMoveItemNum(), Vec2(95, 21), MORE_ICON_BTN_TAG);
}

void PropLayer::showItemIcon(MenuItemImage* item, int haveNum, Vec2 pos, int tag)
{
	Sprite* itemNumSp = nullptr;
	if (haveNum <= 0)
	{
		itemNumSp = Sprite::create("add.png");
	}
	else
	{
		itemNumSp = Sprite::create("have.png");
        //auto sp = Label::createWithSystemFont(TI()->itos(haveNum), "Arial", 30);
        auto sp = Label::createWithCharMap("white_font.png", 25, 29, '0');
        sp->setString(TI()->itos(haveNum));
        sp->setScale(0.8);
        itemNumSp->addChild(sp);
        sp->setPosition(20, 23);
        /**
         * XXX: the hidden rule :)
         */
        sp->setTag(tag + LABEL_OFFSET);
	}
    
	item->addChild(itemNumSp);
	itemNumSp->setPosition(pos);
	itemNumSp->setTag(tag);
}

/**
 *	design mode button
 */
void PropLayer::initColorBtn()
{
	if (!isDesign)
	{
		return;
	}
	auto btn = initPauseButton();
	auto menu = Menu::create(btn, nullptr);
	for (auto i = 1; i < 8;i++)
	{
		auto sp = Sprite::create();
		sp->initWithSpriteFrameName(Bubble::getStringByType((BubbleType)i));
		auto btn = MenuItemSprite::create(sp,sp);
		btn->setTag(2000 + i);
		btn->setCallback(CC_CALLBACK_1(PropLayer::colorBtn, this));
		btn->setPosition(50 + (i-1) * 70, 100);
        if(USER()->getDesignColor() == i)
        {
            btn->setScale(1.2);
            
        }
        else
        {
            btn->setScale(0.8);
        }
        
		menu->addChild(btn);
	}
    auto sp = Sprite::create("res/dig.png");
    auto digBtn = MenuItemSprite::create(sp, sp);
    digBtn->setTag(2000+8);
    digBtn->setCallback(CC_CALLBACK_1(PropLayer::colorBtn, this));
    if(USER()->getDesignColor() == 8)
    {
        digBtn->setScale(1.2);
        
    }
    else
    {
        digBtn->setScale(0.8);
    }
    digBtn->setPosition(50, 200);
    menu->addChild(digBtn);
    
    
	addChild(menu);
	menu->setPosition(Vec2::ZERO);
	menu->setAnchorPoint(Vec2::ZERO);
    menu->setTag(MENU_TAG);
}

void PropLayer::colorBtn(Ref * pSender)
{
	if (!pSender)
	{
		return;
	}
    auto menu = getChildByTag(MENU_TAG);
    for(int i = 2001; i <= 2008; i++)
    {
        auto obj = menu->getChildByTag(i);
        if(obj)
        {
            obj->setScale(0.8f);
            //TI()->unShaderSprite(obj);
            obj->setColor(Color3B(255,255,255));
        }
    }
    
	auto obj = (Node*)pSender;
    obj->setScale(1.2);
    if(obj->getTag()==2008){
        obj->setColor(Color3B::RED);
    }
    
	int tag = obj->getTag();
    log("====> %d", tag);
	USER()->setDesignColor(tag - 2000);
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
    initChangeBubbleSprite();
    
    if (UserData::getInstance()->getOpenBox())
    {
        UserData::getInstance()->setOpenBox(false);
        addMoveNumberForOpenBox(this);
    }
	if (!isDesign)
	{
		initBox();
		initItemBtn();
	}
	else
	{
		initColorBtn();
	}

    scheduleUpdate();
    flag = 0;
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
    
    auto sp = Sprite::create("bomb.png");
    sp->setTag(BOMB_TAG);
    
    sp->setScale(0.5);
    addChild(sp);
    sp->setPosition(50, 200);
    auto fi = FadeIn::create(0.5);
    sp->runAction(fi);
    addChild(a);
    UserData::getInstance()->setOpenBox(true);
    isOpenBoxInGame = true;
    removeChild(menu);
    menuBombCallBack(this);
}


void PropLayer::buttonCallback(Ref* obj)
{
    
    MenuItemImage* ob = dynamic_cast<MenuItemImage*>(obj);
    if(!ob)
    {
        callJava("showAds","");
        return;
    }
    if(ob->getTag() == BOMB_BTN_TAG)
    {
        auto icon = ob->getChildByTag(BOMB_ICON_BTN_TAG);
        if(!icon)
        {
            callJava("showAds","");
            return;
        }
        if(USER()->getBombItemNum() <=0)
        {
            callJava("showAds","");
            USER()->setBombItemNum(1);
            ob->removeChild(icon);
            showItemIcon(ob, USER()->getBombItemNum(), Vec2(110, 21), BOMB_ICON_BTN_TAG);
        }
        else
        {
            USER()->addBombItemNum(-1);
            menuBombCallBack(this);
            if(USER()->getBombItemNum() <=0)
            {
                ob->removeChild(icon);
                showItemIcon(ob, USER()->getBombItemNum(), Vec2(110, 21), BOMB_ICON_BTN_TAG);
                return;
            }
            auto labelObj = icon->getChildByTag(BOMB_ICON_BTN_TAG + LABEL_OFFSET);
            if (!labelObj)
            {
                return;
            }
            Label* label = dynamic_cast<Label*>(labelObj);
            if(label)
            {
                label->setString(TI()->itos(USER()->getBombItemNum()));
            }
        }
    }
    else if(ob->getTag() == BIAO_TAG)
    {
        USER()->addBiaoItemNum(1);
    }
    else if(ob->getTag() == COLOR_TAG)
    {
        auto icon = ob->getChildByTag(COLOR_ICON_BTN_TAG);
        if(!icon)
        {
            callJava("showAds","");
            return;
        }
        if(USER()->getColorItemNum() <=0)
        {
            callJava("showAds","");
            USER()->setColorItemNum(1);
            ob->removeChild(icon);
            showItemIcon(ob, USER()->getColorItemNum(), Vec2(110, 21), COLOR_ICON_BTN_TAG);
        }
        else
        {
            USER()->addColorItemNum(-1);
            menuColorBubbleCallBack(this);
            if(USER()->getColorItemNum() <=0)
            {
                ob->removeChild(icon);
                showItemIcon(ob, USER()->getColorItemNum(), Vec2(110, 21), COLOR_ICON_BTN_TAG);
                return;
            }
            auto labelObj = icon->getChildByTag(COLOR_ICON_BTN_TAG + LABEL_OFFSET);
            if (!labelObj)
            {
                return;
            }
            Label* label = dynamic_cast<Label*>(labelObj);
            if(label)
            {
                label->setString(TI()->itos(USER()->getColorItemNum()));
            }
        }
    }
    else if(ob->getTag() == MORE_BTN_TAG)
    {
        auto icon = ob->getChildByTag(MORE_ICON_BTN_TAG);
        if(!icon)
        {
            callJava("showAds","");
            return;
        }
        if(USER()->getMoveItemNum() <=0)
        {
            callJava("showAds","");
            USER()->setMoveItemNum(1);
            ob->removeChild(icon);
            showItemIcon(ob, USER()->getMoveItemNum(), Vec2(110, 21), MORE_ICON_BTN_TAG);
        }
        else
        {
            USER()->addMoveItemNum(-1);
            moveNumber_ += 10;
            if(USER()->getMoveItemNum() <=0)
            {
                ob->removeChild(icon);
                showItemIcon(ob, USER()->getMoveItemNum(), Vec2(110, 21), MORE_ICON_BTN_TAG);
                return;
            }
            auto labelObj = icon->getChildByTag(MORE_ICON_BTN_TAG + LABEL_OFFSET);
            if (!labelObj)
            {
                return;
            }
            Label* label = dynamic_cast<Label*>(labelObj);
            if(label)
            {
                label->setString(TI()->itos(USER()->getMoveItemNum()));
            }
        }
    }
    else
    {
      
        int a = rand()%2 + 1;
        showOpenBoxAnimi(a);
    }
}

void PropLayer::setBombNum()
{
}

void PropLayer::setColorBubbleNum()
{
}

void PropLayer::menuBombCallBack(Ref* Psender)
{
	auto gameSceme = (GameScene*)this->getParent();
	gameSceme->bombBubble();
}
// 增加步数
void PropLayer::addMoveNumberForOpenBox(Ref* Psender)
{
    moveNumber_ += 5;
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
    showMoveNumbers();
    
    if(isOpenBoxInGame)
    {
        if(openBoxFlag++ > 600)
        {
            isOpenBoxInGame = false;
            openBoxFlag = 0;
            UserData::getInstance()->setOpenBox(false);
            initBox();
        }
    }
    if(moveNumber_ <= 0)
    {
		if (!notShowBuy)
		{
			showBuyAds();
			notShowBuy = true;
			return;
		}
		/**
		 *	玩家观看广告
		 */
		if (USER()->getClickAds() == 1)
		{
			if (flag++ > 20) /* 结束的时候等下再出结算界面 */
			{
				hadFinished_ = true;
				flag = 0;
			}
			if (hadFinished_)
			{
				moveNumber_ = 10;
				showMoveNumbers();
				hadFinished_ = false;
				notShowBuy = false;
				USER()->setClickAds(0);
			}
		}
		/**
		 *	玩家直接点关闭
		 */
		if (USER()->getClickAds() == 2)
		{
			USER()->setClickAds(0);
			auto gameSceme = (GameScene*)this->getParent();
			gameSceme->gameOver();	
		}

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
