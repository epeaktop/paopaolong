#ifndef  USER_DATA_H_
#define  USER_DATA_H_

#include "cocos2d.h"
#include "Tools.h"

USING_NS_CC;
class UserData
{
public:
	static UserData* getInstance();
	bool init();
	void reset();
	void saveData();
	void addScore(int var);


	CC_SYNTHESIZE(int, _score, Score);
	CC_SYNTHESIZE(bool, _isBeginner, IsBeginner);
	CC_SYNTHESIZE(bool, _isClassics, IsClassics);
    
    CC_SYNTHESIZE(bool, _isDesign, IsDesign);

	CC_SYNTHESIZE_ADD(int, _bomb, Bomb); 
	CC_SYNTHESIZE_ADD(int, _colorBubble, ColorBubble); 
	CC_SYNTHESIZE_ADD(int, _hourglass, Hourglass); 
	CC_SYNTHESIZE_ADD(int, _gold, Gold);  
    CC_SYNTHESIZE_ADD(int, _sliver, Sliver); 
    
    CC_SYNTHESIZE_ADD(int, _hp, Hp);  
    CC_SYNTHESIZE_ADD(int, _star, Star); 
    
    CC_SYNTHESIZE_ADD(int, _lasttime, LastTime);
    
	CC_SYNTHESIZE_ADD(int, _rebirth, Rebirth); 
	CC_SYNTHESIZE_ADD(int, _bestScore, BestScore);
	CC_SYNTHESIZE_ADD(unsigned int, _level, Level);
    CC_SYNTHESIZE_ADD(int, _Sellevel, SelLevel);
    CC_SYNTHESIZE_ADD(int, _digNum, digItemNum);
	CC_SYNTHESIZE(bool, _raffle, Raffle);
	CC_SYNTHESIZE(bool, _haveRaffle, HaveRaffle);
	CC_SYNTHESIZE(bool, _openBox, OpenBox);

	CC_SYNTHESIZE_ADD(int, _moveItemNum, MoveItemNum);
	CC_SYNTHESIZE_ADD(int, _biaoNum, BiaoItemNum);
	CC_SYNTHESIZE_ADD(int, _colorNum, ColorItemNum);
	CC_SYNTHESIZE_ADD(int, _bombNum, BombItemNum);

private:
	UserData() = default;
	~UserData();
    std::string getKeyByLevel(int Level)
    {
        std::stringstream ss;
        ss.str("");
        ss << "level_"<<Level;
        return ss.str();
    }
    std::string getDesignKey(int Level)
    {
        std::stringstream ss;
        ss.str("");
        ss << "design_"<<Level;
        return ss.str();
    }
    
public:
    void setScore(int level, int score)
    {
        UserDefault::getInstance()->setIntegerForKey(getKeyByLevel(level).c_str(), score);
    }
    int getScore(int level)
    {
        return UserDefault::getInstance()->getIntegerForKey(getKeyByLevel(level).c_str(), 0);
    }
    
    void setDesign(int level, std::string str)
    {
        UserDefault::getInstance()->setStringForKey(getDesignKey(level).c_str(), str);
    }
    std::string getDesign(int level)
    {
        return UserDefault::getInstance()->getStringForKey(getDesignKey(level).c_str(), "");
    }

	void setDesignColor(int n)
	{
		UserDefault::getInstance()->setIntegerForKey("design_color", n);
	}

	int getDesignColor()
	{
		return UserDefault::getInstance()->getIntegerForKey("design_color", 1);
	}

	void setClickAds(int n)
	{
		UserDefault::getInstance()->setIntegerForKey("click_ads", n);
	}

	int getClickAds()
	{
		return UserDefault::getInstance()->getIntegerForKey("click_ads", 0);
	}

	
};

#define USER UserData::getInstance

#endif
