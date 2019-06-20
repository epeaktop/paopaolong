#ifndef __tool_game_data_H__
#define __tool_game_data_H__
#include <iostream>
#include <vector>

#include <cocos2d.h>
#include "NDKHelper.h"


using namespace std;

USING_NS_CC;
/**
 * @@ 自己定义的函数库,避免包含boost库,尽量用c++17,跨平台!!
 * @@ jiangxf @2016.12.15
 */

class Tools
{
public:
    static Tools* getInstance();
    
    vector<string> split(const string &s, char delim);
    int string2number(string str);
    int stoi(string s);
    string itos(int s);
    float getWidth();
    float getHeigh();
	bool isInScope(Vec2 v, Vec2 v1, Vec2 v2);
    
    
    int getYear();
    int getMonth();
    int getDay();
    
    
    void shakeNode(Node* obj);
    
    /* 一直放大缩小，游戏开始按钮的特效 */
    void repeatShakeNode(cocos2d::Node *obj);
    
    bool startWith(const string &mainstr, const string &substr)
    {
        return mainstr.find(substr)==0 ? 1 : 0;
    }
    
    bool isDiamond()
    {
        return true;
    }
    
    void setPos(Node* obj, float x, float y)
    {
    	if(nullptr == obj)
        {
        	return;
        }
        
        obj->setPosition(x, 720 - y);
    }
    
    Node* addNumLabel(Node* obj, long n, float x, float y)
    {
        auto label = Label::createWithCharMap("num_gold.png", 55, 78, '0');
    	label->setString(StringUtils::format("%ld",n));
    	obj->addChild(label, 100);
		setPos(label, x, y);
        
        auto a = Sprite::create("plus.png");
        setPos(a, x - label->getContentSize().width/2 -10, y);
        obj->addChild(a, 100);
    	
        return label;
    }
    
    Node* subNumLabel(Node* obj, long n, float x, float y)
    {
        auto label = Label::createWithCharMap("num_gray.png", 55, 78, '0');
    	label->setString(StringUtils::format("%ld",n));
    	obj->addChild(label, 100);
		setPos(label, x, y);
        
        auto a = Sprite::create("sub.png");
        setPos(a, x - label->getContentSize().width/2 -10, y);
        obj->addChild(a, 100);
    	
        return label;
    }

	bool isAndroid()
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    	return true;
#else
		return false;
#endif
    }
    
    bool isIos()
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    	return true;
#else
		return false;
#endif
    
    }
    void toast(string str);
    
    int getInterval(string n)
    {
    	int interval = UserDefault::getInstance()->getIntegerForKey(n.c_str(),0);
        if(interval == 0)
        {
        	return 0;
        }
        
        int _time = int(utils::getTimeInMilliseconds()/1000);
        
        return _time - interval;
        
    }
    
    void setInterval(string n)
    {
    	int _time = int(utils::getTimeInMilliseconds()/1000);
		UserDefault::getInstance()->setIntegerForKey(n.c_str(), _time);
    }
    string _itos(int s)
	{
        stringstream _ss;
    	_ss.str("");
    	_ss << s;
    	return _ss.str();
	}
    

    Label* addLabel(cocos2d::Node *obj, std::string name, float x, float y, int order);
    void showNumber(cocos2d::Label* label, int num, const char* name);
    
    int getMoveNumbers(int level);
    
    //精灵着色器(sp为需要描边的对象,color描边颜色,width描边的宽度)
    void shaderSprite(Node* sp, Color4B color, float width)
    {
        //上边
        auto up = LayerColor::create(color, sp->getContentSize().width + 2 * width, width);
        up->setPosition(Vec2(-width,sp->getContentSize().height));
        //下边
        auto down = LayerColor::create(color, sp->getContentSize().width + 2 * width, width);
        down->setPosition(Vec2(-width,-width));
        //右边
        auto right = LayerColor::create(color, width, sp->getContentSize().height);
        right->setPosition(Vec2(sp->getContentSize().width,0));
        //左边
        auto left = LayerColor::create(color, width, sp->getContentSize().height);
        left->setPosition(Vec2(- width,0));
        //加载到sp上
        sp->addChild(up);
        sp->addChild(down);
        sp->addChild(right);
        sp->addChild(left);
    }
    void unShaderSprite(Node* sp)
    {
        sp->removeAllChildren();
    }
    
	/**
	 *	draw a line
	 */

	void myDrawLine(Node* obj, float x, float y, int length)
	{
		
		int len = 0;
		int i = 0;
		const int tag = 1111111;
		while(len < length)
		{
			i++;
			auto sp = Sprite::create("res/line2.png");
			sp->setPosition(x + 10*i, y);
			sp->setTag(tag);
			len += 5;
			obj->addChild(sp, 1000);
		}
	}

private:
    static Tools* instance_;

        
};

#define TI Tools::getInstance
#define CC_SYNTHESIZE_ADD(varType, varName, funName)\
protected: varType varName; \
public: virtual varType get##funName(void) const { return varName; }\
public: virtual void set##funName(varType var){ varName = var; }\
public: virtual void add##funName(varType var){ varType temp = varName; varName = var + temp; }\

#endif  // __HELLOWORLD_SCENE_H__
