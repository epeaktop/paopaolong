
#include "Cover.h"
#include "UserData.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated"
#include "SpriteFrameAnimation.h"
#include "GameScene.h"
#include "HelpScene.h"
#include "GameSetting.h"
#include "Tools.h"

//const int MORE_BTN_TAG = 1000;
const int RATE_BTN = 10011;
const int FACEBOOK_TAG = 10012;
const int CLASSICS_TAG = 10013;

using  namespace std;

MenuItemImage *Cover::classicsButton()
{
    Size size = Director::getInstance()->getWinSize();
    /* 经典模式按钮 */
    auto classics = MenuItemImage::create("yellow_btn.png", "yellow_btn.png", CC_CALLBACK_1(Cover::newCallback,this));
    auto classicsLabel = Label::createWithSystemFont("classics", "Arial", 36);
    classics->addChild(classicsLabel);
    classicsLabel->setPosition(classics->getContentSize().width/2, classics->getContentSize().height/2+ 10);
    classics->setPosition(Vec2(size.width / 2 , 360));
    classics->setTag(CLASSICS_TAG);
    return classics;
}

bool Cover::init()
{
    if (!Layer::init())
    {
        return false;
    }

    Size size = Director::getInstance()->getWinSize();
    auto *game_bg = Sprite::create("cover-bg.png");
    game_bg->setPosition(Vec2(size.width / 2, size.height / 2));
    addChild(game_bg, -1);

    auto *new_button = MenuItemImage::create("yellow_btn.png", "yellow_btn.png", CC_CALLBACK_1(Cover::newCallback,this));
    auto new_label = Label::createWithSystemFont("play", "Arial", 36);
    new_button->addChild(new_label);
    new_label->setPosition(new_button->getContentSize().width/2,new_button->getContentSize().height/2+ 10);
    new_button->setPosition(Vec2(size.width / 2 , size.height / 2));
    sound_ = MenuItemImage::create("sound.png", "sound.png", CC_CALLBACK_1(Cover::soundCallBack,this));
    sound2_ = MenuItemImage::create("no-sound.png", "no-sound.png", CC_CALLBACK_1(Cover::soundCallBack,this));
    sound_->setPosition(Vec2(74,960-49));
    sound2_->setPosition(Vec2(74,960-49));
    showSoundButton();
    TI()->repeatShakeNode(new_button);
    auto rateBtn = addRateButton();
    auto classics = classicsButton();
    Menu *pMenu = Menu::create(new_button, classics, sound_, sound2_, rateBtn , NULL);
    pMenu->setPosition(Vec2::ZERO);
    addChild(pMenu, 100);
    regTouch();
    return true;
}

MenuItemImage* Cover::addRateButton()
{
    auto ret = MenuItemImage::create("rate.png", "rate.png", CC_CALLBACK_1(Cover::newCallback, this));
    ret->setTag(RATE_BTN);
    ret->setPosition(170,960-49);
    return ret;
}

void Cover::onExit()
{
    Layer::onExit();
    log("Cover::onExit");
}

void Cover::onEnter()
{
    Layer::onEnter();
    log("Cover::onEnter");
}

void Cover::showMoreGame()
{
//    moreGameLayerShow = true;
//    moreGameLayer_->setVisible(moreGameLayerShow);
}

void Cover::newCallback(Ref *pSender)
{
    Node *obj = (Node*) pSender;
    if(obj->getTag() == RATE_BTN)
    {
    	callJava("download", "com.mmj.paopaolong");
    	return;
    }
    
    if(obj->getTag() == FACEBOOK_TAG)
    {
    	callJava("facebookLogin", "com.mmj.paopaolong");
    	return;
    }
    
    SimpleAudioEngine::getInstance()->playEffect("Music/Click.mp3");
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    
    if (obj->getTag() == CLASSICS_TAG)
    {
        // USER()->setIsClassics(true);
        USER()->setIsDesign(true);
    }
    else
    {
        // USER()->setIsClassics(false);
        USER()->setIsDesign(false);
    }
    /* ========= 选择关卡的界面 ========= */
    auto scene = HelpScene::scene();
    Director::getInstance()->pushScene(scene);
}
void Cover::exitCallback(Ref *pSender)
{
    log("exitCallback!");
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
void Cover::resumeCallback(Ref *pSender)
{

}

void Cover::soundCallBack(Ref *pSender)
{
    if (isSoundOn_)
    {
        isSoundOn_ = false;
        GameSetting::getInstance()->setSound(false);
        SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
        
    }
    else
    {
        isSoundOn_ = true;
        GameSetting::getInstance()->setSound(true);
        SimpleAudioEngine::getInstance()->playBackgroundMusic("Music/bgm.mp3", true);
    }

    showSoundButton();

}

Scene *Cover::scene()
{
    Scene *scene = Scene::create();
    Cover *layer = Cover::create();
    scene->addChild(layer);

    return scene;
}

void Cover::showSoundButton()
{
    if (GameSetting::getInstance()->isSoundOn_)
    {
        sound_->setVisible(true);
        sound2_->setVisible(false);
    }
    else
    {
        sound2_->setVisible(true);
        sound_->setVisible(false);
    }
}

void Cover::showEffect(Point point, int cur_type_)
{
    
}

void Cover::update(float dt)
{
	
}

bool Cover::onTouchBegan(Touch *touch, Event *unused_event)
{
    Vec2 location = touch->getLocationInView();
    location = Director::getInstance()->convertToGL(location);
	return true;
}

void Cover::onTouchMoved(Touch *touch, Event *unused_event)
{

}
void Cover::onTouchEnded(Touch *touch, Event *unused_event)
{

}

void Cover::regTouch()
{
	_listener = EventListenerTouchOneByOne::create();
    //_listener->setSwallowTouches(true);
    _listener->onTouchBegan = CC_CALLBACK_2(Cover::onTouchBegan, this);
    _listener->onTouchMoved = CC_CALLBACK_2(Cover::onTouchMoved, this);
    _listener->onTouchEnded = CC_CALLBACK_2(Cover::onTouchEnded, this);

    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_listener, this);

}
#pragma clang diagnostic pop



