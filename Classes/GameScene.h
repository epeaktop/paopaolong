#ifndef GAME_SCENE_H_
#define GAME_SCENE_H_

#include "cocos2d.h"
#include "TouchLayer.h"
#include "BubbleLayer.h"
#include "BubbleLayer2.h"
#include "PropLayer.h"
//#define DESIGN_MODE

USING_NS_CC;

typedef enum{
	k_Operate_Pause,
	k_Operate_Resume

}OperateFlag;

class GameScene : public Scene
{
public:
	CREATE_FUNC(GameScene);
	virtual bool init();
	TouchLayer* _touchLayer;
	BubbleLayer2* _bubbleLayer2;
    BubbleLayer* _bubbleLayer;
	PropLayer* _propLayer;
	Node* _bg;
	void onTouch(Point target);
	void setTouchEnable(bool enable);
	void swapBubble();
	void bombBubble();
	void colorBubble();
	void biaoBubble();
	void gameOver(bool over = false);
	void operateAllSchedulerAndActions(Node* node, OperateFlag flag);
	void mPause();
	void mResume();
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	void setCannonAngle(Point target);
};






#endif
