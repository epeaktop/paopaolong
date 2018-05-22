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
private:
    static Tools* instance_;
        
};

#define TI Tools::getInstance
	
#endif  // __HELLOWORLD_SCENE_H__
