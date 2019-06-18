#include "GameScene.h"
#include "UserData.h"
#include "GameoverLayer.h"
#include "PauseLayer.h"
#include "FailLayer.h"
#include "editor-support/cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
#include "GameSetting.h"
#include "NDKHelper.h"

using namespace CocosDenshion;
using namespace cocostudio::timeline;


bool GameScene::init()
{

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("bubbles.plist");
    auto frameSize = Director::getInstance()->getVisibleSize();
	
    _bg = CSLoader::createNode("Background.csb");
	_bg->setContentSize(frameSize);
	ui::Helper::doLayout(_bg);
	addChild(_bg);
    
    if (GameSetting::getInstance()->isSoundOn_)
    {
        SimpleAudioEngine::getInstance()->playBackgroundMusic("Music/bgm.mp3", true);
        SimpleAudioEngine::getInstance()->resumeAllEffects();
    }
    else
    {
        SimpleAudioEngine::getInstance()->pauseAllEffects();
        SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    }
    if(USER()->getIsDesign())
    {
        _bubbleLayer2 = BubbleLayer2::create();
        addChild(_bubbleLayer2);
    }
    else
    {
	    _bubbleLayer = BubbleLayer::create();
        addChild(_bubbleLayer);
    }
    
	_propLayer = PropLayer::create();
	addChild(_propLayer);

    auto bgArmature = (Armature *)_bg->getChildByTag(63);
    bgArmature->setVisible(false);
    
	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyListener, this);

	return true;
}

void GameScene::operateAllSchedulerAndActions(Node* node, OperateFlag flag)
{
	if (node->isRunning()) {
		switch (flag) {
		case k_Operate_Pause:
			node->pause();
			break;
		case k_Operate_Resume:
			node->resume();
		default:
			break;
		}
		auto children = node->getChildren();
		if (children.size() > 0) {
			for (auto child : children) {
				operateAllSchedulerAndActions(child, flag);
			}
		}
	}
}

void GameScene::mPause()
{
	operateAllSchedulerAndActions(this, k_Operate_Pause);
}

void GameScene::mResume()
{
	operateAllSchedulerAndActions(this, k_Operate_Resume);
}

void GameScene::onTouch(Point target)
{
    if(USER()->getIsDesign())
        _bubbleLayer2->onTouch(target);
    else
	    _bubbleLayer->onTouch(target);
}
void GameScene::setCannonAngle(Point target)
{
    _propLayer->setCannonAngle(target);
}
void GameScene::setTouchEnable(bool enable)
{
	_touchLayer->setTouchEnable(enable);
}
void GameScene::swapBubble()
{
	_bubbleLayer->swapBubble();
}
void GameScene::bombBubble()
{
	_bubbleLayer->bombBubble();
}
void GameScene::colorBubble()
{
	_bubbleLayer->colorBubble();
}
void GameScene::biaoBubble()
{
	_bubbleLayer->biaoBubble();
}
void GameScene::gameOver(bool over)
{
	UserData::getInstance()->saveData();
	operateAllSchedulerAndActions(this, k_Operate_Pause);
    callJava("showAds", "");
	if (over)
	{
		SimpleAudioEngine::getInstance()->playEffect("Music/Ending.mp3");
		auto overLayer = GameoverLayer::create();
		this->addChild(overLayer);
	}
	else
	{
		SimpleAudioEngine::getInstance()->playEffect("Music/end.mp3");
        auto overLayer = GameoverLayer::create();
        this->addChild(overLayer);
	}

}
void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode != EventKeyboard::KeyCode::KEY_BACK)
	{
		return;
	}
	operateAllSchedulerAndActions(this, k_Operate_Pause);
}
