#include "Bubble.h"
#include "GameConst.h"
#include "editor-support/cocostudio/CocoStudio.h"


using namespace cocostudio;

Bubble::Bubble()
{
	_flag = false;
	_type = BUBBLE_TYPE_UNKNOW;
	_isSame = false;
	_isPass = false;
	_isMove = false;
	_isDie = false;
}

Bubble::~Bubble()
{

}

Bubble * Bubble::initWithType(BubbleType type, int flag)
{
	Bubble *pRet = Bubble::create();
	pRet->setType(type);
	pRet->initWithSpriteFrameName(getStringByType(type));
    pRet->setScale(0.77);
    pRet->label = Label::createWithSystemFont("0,0", "Arial", 27);
    pRet->label->setColor(Color3B::RED);
    
    pRet->label->enableOutline(Color4B(0,0,0,128),3);
    pRet->label->setPosition(25,25);
    pRet->label->setVisible(false);
    pRet->addChild(pRet->label, 100000);
    if(flag == 1)
    {
        pRet->label->setVisible(false);
    }
	return pRet;
}



std::string Bubble::getStringByType(BubbleType type) 
{
	std::string pRet;
	switch (type) {
	case BUBBLE_TYPE1:
	case BUBBLE_TYPE2:
	case BUBBLE_TYPE3:
	case BUBBLE_TYPE4:
	case BUBBLE_TYPE5:
	case BUBBLE_TYPE6:
	case BUBBLE_TYPE7:
		pRet = StringUtils::format(BUBBLE_NAME.c_str(), (int)type);
		break;
	case BUBBLE_TYPE_COLOR:
		pRet = BUBBLE_COLOR_NAME;
		break;
	default:
		break;
	}
	return pRet;
}
