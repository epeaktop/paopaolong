#include "AppDelegate.h"
#include "Cover.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	glview = cocos2d::GLViewImpl::createWithRect("xiaoxiao", Rect(0, 0, 540, 960));
	director->setOpenGLView(glview);
#endif
    glview->setDesignResolutionSize(540 , 960, ResolutionPolicy::SHOW_ALL);
	//director->getOpenGLView()->setFrameZoomFactor(0.5f);
    director->setDisplayStats(false);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    director->setAnimationInterval(1.0 / 15);
#else
    director->setAnimationInterval(1.0 / 15);
#endif
    FileUtils::getInstance()->addSearchPath("res");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/bgm.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("Music/Ending.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("Music/Fuhuo.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("Music/Guoguan.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("Music/Click.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("Music/Clock.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("Music/Remove.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("Music/Hit.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("Music/Bomb.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("Music/start.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("Music/end.mp3");

	auto scene = Cover::scene();
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
}
