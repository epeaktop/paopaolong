#ifndef GAMEOVER_LAYER_H_
#define GAMEOVER_LAYER_H_

#include "cocos2d.h"

USING_NS_CC;

class BuyMoveNumber : public LayerColor
{
public:
	CREATE_FUNC(BuyMoveNumber);
	virtual bool init();
private:
	void menuOverCallBack(Ref* Psender);
	void buyCallback(Ref* Psender);

};







#endif