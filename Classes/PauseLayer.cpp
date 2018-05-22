#include "PauseLayer.h"
#include "GameScene.h"
#include "editor-support/cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "UserData.h"
#include "StartScene.h"
#include "GiftLayer.h"
#include "Cover.h"
#include "GameSetting.h"
using namespace cocostudio::timeline;

bool PauseLayer::init()
{
	if (!LayerColor::init())
	{
		return false;
	}

    Size size = Director::getInstance()->getWinSize();
    
    
    auto *game_bg = Sprite::create("popui-stop-bg.png");
    game_bg->setPosition(ccp(size.width / 2, size.height / 2));
    addChild(game_bg, -1);
	auto *home = MenuItemImage::create("r.png", "r.png", this, menu_selector(PauseLayer::menuHomeCallBack));
    auto *con  = MenuItemImage::create("c.png", "c.png", this, menu_selector(PauseLayer::menuContinueCallBack));
    auto *so   = MenuItemImage::create("sound.png", "sound.png", this, menu_selector(PauseLayer::soundCallBack));
    
    if (!GameSetting::getInstance()->isSoundOn_) {
        auto sp = Sprite::create("no-sound.png");
        so->setNormalImage(sp);
    }
    
    home->setPosition(Vec2(140,960 - 537));
    con->setPosition(Vec2(353,960 - 537));
    
    so->setPosition(Vec2(172,960 - 435));
    
    
    Menu *pMenu = Menu::create(home, con,so, NULL);
    pMenu->setPosition(Vec2::ZERO);
    
    addChild(pMenu, 100);
    

	return true;
}

void PauseLayer::soundCallBack(Ref* obj)
{
    MenuItemImage* button = (MenuItemImage*) obj;
	if(!button)
        return;
    if (GameSetting::getInstance()->isSoundOn_)
    {
        auto sp = Sprite::create("no-sound.png");
        button->setNormalImage(sp);
        GameSetting::getInstance()->setSound(false);
        SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    }
    else
    {
        auto sp = Sprite::create("sound.png");
        button->setNormalImage(sp);
        GameSetting::getInstance()->setSound(true);
        SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    }
    
    
	
}
void PauseLayer::menuContinueCallBack(Ref* Psender)
{
	auto gameScene = dynamic_cast<GameScene *>(this->getParent());
	gameScene->mResume();
	gameScene->removeChild(this);
}
void PauseLayer::menuGetCallBack(Ref* Psender)
{
	auto gameScene = dynamic_cast<GameScene *>(this->getParent());
	auto giftLayer = GiftLayer::create();
	giftLayer->isGameScene = true;
	gameScene->addChild(giftLayer);
	this->removeFromParent();
}
void PauseLayer::menuHomeCallBack(Ref* Psender)
{
	Director::getInstance()->replaceScene(Cover::scene());
}
