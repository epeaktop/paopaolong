#include "Tools.h"
#include <iostream>
#include <vector>
#include <regex>
#include <sstream>


using namespace std;

USING_NS_CC;

Tools* Tools::instance_ = nullptr;


Tools*  Tools::getInstance()
{
    if (nullptr == instance_)
    {
        instance_ = new Tools;
    }
    return instance_;
}

std::vector<std::string> Tools::split(const std::string &s, char delim) 
{
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> elems;
    while (std::getline(ss, item, delim))
    {
        elems.push_back(item);
    }

    return elems;
}
#include <sstream>

int Tools::stoi(string s)
{
    stringstream _ss(s);
    int num;
    _ss >> num;
    return num;
}



string Tools::itos(int s)
{
    stringstream _ss;
    _ss.str("");
    _ss << s;
    return _ss.str();
}

int Tools::string2number(string str)
{
    if (str.length() != 3)
    {
        return -1;
    }

    if (str[0] == '0' && str[1] == '0' && str[2] == '0')
    {
        return 0;
    }
    else if (str[0] == '0' && str[1] == '0')
    {
        string _s = str.substr(2, 2);
        return stoi(_s);
    }
    else if (str[0] == '0')
    {
        string _s = str.substr(1, 2);
        return stoi(_s);
    }
    else
    {
        return stoi(str);
    }
}

float Tools::getHeigh()
{
    auto size = Director::getInstance()->getWinSize();
    return size.height;
}

bool Tools::isInScope(Vec2 v,Vec2 v1, Vec2 v2)
{
	if (v.x < v2.x && v.x > v1.x)
	{
		if (v.y > v1.y && v.y < v2.y)
		{
			return true;
		}
	}

	return false;
}

float Tools::getWidth()
{
    auto size = Director::getInstance()->getWinSize();
    return size.width;
}


int Tools::getYear()
{
    struct tm *tm;
    time_t timep;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    time(&timep);
#else
    struct timeval tv;
    gettimeofday(&tv, NULL);
    timep = tv.tv_sec;
#endif
    
    tm = localtime(&timep);
    return tm->tm_year + 1900;//年
}

int Tools::getMonth()
{
    struct tm *tm;
    time_t timep;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    time(&timep);
#else
    struct timeval tv;
    gettimeofday(&tv, NULL);
    timep = tv.tv_sec;
#endif
    
    tm = localtime(&timep);
   
    return tm->tm_mon + 1;//月
    
}

int Tools::getDay()
{
    struct tm *tm;
    time_t timep;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    time(&timep);
#else
    struct timeval tv;
    gettimeofday(&tv, NULL);
    timep = tv.tv_sec;
#endif
    
    tm = localtime(&timep);
    
    return tm->tm_mday;//日
}

void Tools::shakeNode(cocos2d::Node *obj)
{

    if (!obj)
    {
        return;
    }
    
    Action* act = Sequence::create(ScaleTo::create(0.0, 0.0),
                                   ScaleTo::create(0.06, 1.35),
                                   ScaleTo::create(0.08, 0.95),
                                   ScaleTo::create(0.08, 1.0), NULL);
    obj->runAction(act);
    
}

void Tools::repeatShakeNode(cocos2d::Node *obj)
{

    if (!obj)
    {
        return;
    }
    
    auto act = Sequence::create(ScaleTo::create(0.8, 1.02),ScaleTo::create(0.9, 0.99),NULL);
    auto repeat = RepeatForever::create(act);
    obj->runAction(repeat);
    
}

Label* Tools::addLabel(cocos2d::Node *obj, std::string name, float x, float y, int order=1000)
{
    auto label = Label::createWithSystemFont(name.c_str(), "Arial", 30);
    obj->addChild(label, order);
    setPos(label, x, y);
    return label;
}



#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
void Tools::toast(string str)
{
	callJava("toast", str);
}
#endif

void Tools::showNumber(cocos2d::Label* label, int num, const char* name)
{
    std::stringstream s("");
    s << num << name;
    label->setString(s.str().c_str());
}

int Tools::getMoveNumbers(int level)
{
    int a[] =
    {
        30,30,30,30,30,
        30,30,30,30,30,
        // 10
        30,30,30,30,30,
        30,30,30,30,30,
        // 20
        30,30,30,30,30,
        30,30,30,30,30,
        // 30
        30,30,30,30,30,
        30,30,30,30,30,
        // 40
        30,30,30,30,30,
        30,30,30,30,30,
        // 50
        30,30,30,30,30,
        30,30,30,30,30,
        // 60
        30,30,30,30,30,
        30,30,30,30,30,
        // 70
        30,30,30,30,30,
        30,30,30,30,30,
        // 80
        30,30,30,30,30,
        30,30,30,30,30,
        // 90
        30,30,30,30,30,
        30,30,30,30,30,
        // 100
        30,30,30,30,30,
        30,30,30,30,30,
        // 110
        30,30,30,30,30,
        30,30,30,30,30,
        // 120
        30,30,30,30,30,
        30,30,30,30,30,
        // 130
        30,30,30,30,30,
        30,30,30,30,30,
        // 140
        30,30,30,30,30,
        30,30,30,30,30,
        // 150
        30,30,30,30,30,
        30,30,30,30,30,
        // 160
        30,30,30,30,30,
        30,30,30,30,30,
        // 170
        30,30,30,30,30,
        30,30,30,30,30,
        // 180
        30,30,30,30,30,
        30,30,30,30,30,
        // 190
        30,30,30,30,30,
        30,30,30,30,30,
        // 200
        30,30,30,30,30,
        30,30,30,30,30,
        
    };
    return a[level];
}
