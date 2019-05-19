#ifndef __FINISHGAME_SCENE_H__
#define __FINISHGAME_SCENE_H__

#include "cocos2d.h"
#include "ui/UIButton.h"
using namespace cocos2d;

class FinishGameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene(int score, int highscore, int gold, int touchitems, int skin);

    virtual bool init();   
    // implement the "static create()" method manually
    CREATE_FUNC(FinishGameScene);
	//
	void ButtonReplay();
	void ButtonBack();
	void ButtonShop();
	void ButtonShareFacebook();
	bool isInternetConnected(void);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
private:
	Size visibleSize;
	Vec2 origin;
	cocos2d::Label *label;
	cocos2d::Label *labelhighScore;
	cocos2d::Label *labelGold;
	cocos2d::ui::Button * buttonContinue;
	cocos2d::Sprite * sceneEnd;
	//Continue
	bool flagContinue = true;

};

#endif // __FINISHGAME_SCENE_H__
