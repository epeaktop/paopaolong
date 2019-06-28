#include "BuyMoveNumber.h"
#include "StartScene.h"
#include "GameScene.h"
#include "UserData.h"
#include "editor-support/cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Cover.h"
#include "NDKHelper.h"
#include "Tools.h"
#include "UserData.h"

using namespace cocostudio::timeline;

bool BuyMoveNumber::init()
{
	if (!Layer::init())
	{
		return false;
	}
	this->initWithColor(Color4B(0, 0, 0, 100));

    Size size = Director::getInstance()->getWinSize();
    auto *game_bg = Sprite::create("watchads_bg.png");
    game_bg->setPosition(Vec2(size.width / 2, size.height / 2));
    addChild(game_bg, 99);
    auto *closeBtn = MenuItemImage::create("button_close.png", "button_close.png", this, menu_selector(BuyMoveNumber::menuOverCallBack));
    auto *showAdsBtn  = MenuItemImage::create("wbt.png", "wbt.png", this, menu_selector(BuyMoveNumber::buyCallback));
    closeBtn->setPosition(Vec2(506, 710));
    showAdsBtn->setPosition(Vec2(276,292));
    Menu *pMenu = Menu::create(closeBtn, showAdsBtn, NULL);
    pMenu->setPosition(Vec2::ZERO);
    addChild(pMenu, 100);
	return true;
}
void BuyMoveNumber::buyCallback(Ref* Psender)
{
	callJava("showRewardAds", "");
	USER()->setClickAds(1);
	removeFromParentAndCleanup(true);
}
#include "HelpScene.h"
void BuyMoveNumber::menuOverCallBack(Ref* Psender)
{
	Director::getInstance()->replaceScene(HelpScene::scene());
}
