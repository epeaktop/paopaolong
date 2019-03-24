#include "GameoverLayer.h"
#include "StartScene.h"
#include "GameScene.h"
#include "UserData.h"
#include "editor-support/cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Cover.h"

using namespace cocostudio::timeline;

bool GameoverLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	this->initWithColor(Color4B(0, 0, 0, 100));
	auto gameoverLayer = CSLoader::createNode("GameoverLayer.csb");
	auto frameSize = Director::getInstance()->getVisibleSize();
	gameoverLayer->setContentSize(frameSize);
	ui::Helper::doLayout(gameoverLayer);
    gameoverLayer->setVisible(false);
	addChild(gameoverLayer);
    Size size = Director::getInstance()->getWinSize();
    auto *game_bg = Sprite::create("popui-over-bg.png");
    game_bg->setPosition(Vec2(size.width / 2, size.height / 2));
    addChild(game_bg, 99);
    auto *home = MenuItemImage::create("r.png", "r.png", this, menu_selector(GameoverLayer::menuOverCallBack));
    auto *con  = MenuItemImage::create("c.png", "c.png", this, menu_selector(GameoverLayer::menuStartCallBack));
    home->setPosition(Vec2(165,960 - 700));
    con->setPosition(Vec2(353,960 - 700));
    Menu *pMenu = Menu::create(home, con, NULL);
    pMenu->setPosition(Vec2::ZERO);
    addChild(pMenu, 100);
	return true;
}
void GameoverLayer::menuStartCallBack(Ref* Psender)
{
	Director::getInstance()->replaceScene(GameScene::create());
}

void GameoverLayer::menuOverCallBack(Ref* Psender)
{
	Director::getInstance()->replaceScene(Cover::scene());
}
