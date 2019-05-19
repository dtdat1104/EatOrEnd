#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

#include "cocos2d.h"
#include "ui/UIButton.h"
#include "ui/UICheckBox.h"
#include "MessageScene.h"
#include "OptionLayer.h"

using namespace cocos2d;
using namespace cocos2d::ui;

class MainMenuScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	// implement the "static create()" method manually
	CREATE_FUNC(MainMenuScene);
	//ShopScene
	void static CheckShop(int);
	void static CheckGold(int);
	//SettingScene
	static void CheckSound(int);
	static void CheckMusic(int);
	//Pop up
	static void CheckCancel(int);
	static int CheckLanguage();
	void selectCharacter();

private:
	//Variable
	Size visibleSize;
	Vec2 origin;
	Sprite * backGroundMainMenu;
	Sprite * Mouse;
	Button *buttonPlay;
	Button *buttonShop;
	Button *buttonOption;
	CheckBox * buttonLanguage;
	//
	OptionLayer * optionLayer;
	MessageScene * messageScene;
	//MainMenuScene
	void checkFirstInstall();
	void setupPreLoad();
	void addBackGroundMainMenuScene();
	void setupButtonPlay();
	void setupButtonPlayOnline();
	void setupButtonShop();
	void setupButtonOption();
	void setupButtonLanguage();
	void loadBackGroundMusic();
	void onExitGame(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void doExitGame();

};

#endif // __MAINMENU_SCENE_H__
