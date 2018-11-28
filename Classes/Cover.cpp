
#include "Cover.h"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated"
#include "SpriteFrameAnimation.h"
#include "GameScene.h"
#include "HelpScene.h"
#include "GameSetting.h"
#include "Tools.h"

const int MORE_BTN_TAG = 1000;
const int RATE_BTN = 10011;
const int FACEBOOK_TAG = 10012;

using  namespace std;
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

    log("Cover::init");
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
    
//    auto more = MenuItemImage::create("green_btn.png", "green_btn.png",CC_CALLBACK_1(Cover::newCallback,this));
//    more->setTag(MORE_BTN_TAG);
//    more->setPosition(size.width/2, 360);
//    auto more_label = Label::createWithSystemFont("more", "Arial", 36);
//    more->addChild(more_label);
//    more_label->setPosition(more->getContentSize().width/2,more->getContentSize().height/2 + 10);
    
    
//    auto facebook = MenuItemImage::create("facebook_login.png","facebook_login.png",CC_CALLBACK_1(Cover::newCallback, this));
//    facebook->setPosition(size.width/2, 240);
//    facebook->setTag(FACEBOOK_TAG);
    
    
//    TI()->repeatShakeNode(more);
    TI()->repeatShakeNode(new_button);
//    TI()->repeatShakeNode(facebook);
    
    auto rateBtn = addRateButton();
    Menu *pMenu = Menu::create(new_button,sound_, sound2_, rateBtn  , NULL);
    
    pMenu->setPosition(Vec2::ZERO);
    
    
    addChild(pMenu, 100);

//    moreGameLayer_ = MoreGameLayer::create();
//    addChild(moreGameLayer_, 1000);
//    moreGameLayer_->setVisible(false);
    
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
//    if(moreGameLayer_->isVisible())
//    {
//        return;
//    }
    
//    if(obj->getTag() == MORE_BTN_TAG)
//    {
//        showMoreGame();
//        return;
//    }
//
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
    Director::getInstance()->pushScene(HelpScene::scene());
    
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
    
//    if(TI()->isInScope(location,Vec2(490,910),Vec2(540,960)))
//    {
//        moreGameLayer_->setVisible(false);
//        return true;
//    }
    
//    if(!moreGameLayer_->isVisible())
//        return true;
//    
//    if(TI()->isInScope(location,Vec2(62,960-330),Vec2(190,960-190)))
//    {
//        callJava("download", "com.mmj.jewelsline2");
//        return true;
//    }
//    
//    if(TI()->isInScope(location,Vec2(219,960-330),Vec2(348,960-190)))
//    {
//        callJava("download", "com.mmj.majiang");
//        return true;
//    }
//    
//    if(TI()->isInScope(location,Vec2(384,960-330),Vec2(960,960-190)))
//    {
//        callJava("download", "com.mmj.cake");
//        return true;
//    }
//    
//    
//    if(TI()->isInScope(location,Vec2(62,960-526),Vec2(190,960-390)))
//    {
//        callJava("download", "com.mmj.diamond");
//        return true;
//    }
//    
//    if(TI()->isInScope(location,Vec2(219,960-526),Vec2(348,960-390)))
//    {
//        callJava("download", "org.mmj.sudoku");
//        return true;
//    }
//    
//    if(TI()->isInScope(location,Vec2(384,960-526),Vec2(960,960-390)))
//    {
//        callJava("download", "com.mmj.bird");
//        return true;
//    }
//    
    
    
    
    
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


