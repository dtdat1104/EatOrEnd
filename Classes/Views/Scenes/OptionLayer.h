#pragma once
#include "cocos2d.h"
#include "ui/UIButton.h"
#include "ui/UICheckBox.h"
#include "MessageScene.h"
using namespace cocos2d::ui;
USING_NS_CC;
class OptionLayer : public Layer
{
public:
	
	bool init();
	CREATE_FUNC(OptionLayer);
	void close(Ref* sender = nullptr);
	static void CheckCancel();
	void showOptionScene();
private:
	//Variable
	cocos2d::Menu * menu;
	cocos2d::Sprite *settingbackground;
	cocos2d::ui::Button * buttonCancel;
	cocos2d::ui::Button * buttonReset;
	cocos2d::ui::CheckBox * checkboxMusic;
	cocos2d::ui::CheckBox * checkboxXMusic;
	cocos2d::ui::CheckBox * checkboxSound;
	cocos2d::ui::CheckBox * checkboxXSound;
	cocos2d::MenuItemSprite *musicItem;
	cocos2d::MenuItemSprite *soundItem;
	cocos2d::MenuItemSprite *resetItem;
	cocos2d::MenuItemSprite *cancelItem;
	cocos2d::MenuItemImage *overlayOptionWindowItem;
	MessageScene *messageScene;
	//Function
	void addBackGroundOptionLayer();

	void setupCheckBoxSound();
	void callCheckBoxSound();
	void callCheckBoxSoundX();

	void setupCheckBoxMusic();
	void callCheckBoxMusic();
	void callCheckBoxMusicX();

	void setupButtonCancel();
	void callButtonCancel();

	void setupButtonReset();
	void callButtonReset();

	void setupMenu();
};


