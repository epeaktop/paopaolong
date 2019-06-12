#ifndef BUBBLE_H_
#define BUBBLE_H_

#include "cocos2d.h"
#include "GameEnum.h"
USING_NS_CC;

class Bubble : public Sprite
{
public:
	Bubble();
	~Bubble();
	static Bubble *initWithType(BubbleType type = BUBBLE_TYPE1, int flag = 0);
	CREATE_FUNC(Bubble);
	CC_SYNTHESIZE(BubbleType, _type, Type);
	CC_SYNTHESIZE(bool, _isSame, IsSame);
	CC_SYNTHESIZE(bool, _isPass, IsPass);
	CC_SYNTHESIZE(bool, _flag, Flag);
	CC_SYNTHESIZE(bool, _isMove, IsMove);
	CC_SYNTHESIZE(bool, _isDie, IsDie);
public:
    Label *label = nullptr;
	static std::string getStringByType(BubbleType type);
    void setString(std::string s)
    {
        if(!label)
            return;
        label->setString(s);
    }
    void setString(int i, int j)
    {
        std::stringstream s;
        s <<i<<","<<j;
        setString(s.str());
    }
};

#endif /* defined(__paopaolong__PaoPao__) */
