#ifndef __INTROGAME_SCENE_H__
#define __INTROGAME_SCENE_H__

#include "cocos2d.h"

class IntroGameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();   
    CREATE_FUNC(IntroGameScene);
	//Data
	void openData();
private:
	void addBackGroundInTroGameScene();
	void switchToMainMenuScene(float transitionTime);
	void onExitGame(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void doExitGame();
};

#endif // __INTROGAME_SCENE_H__
