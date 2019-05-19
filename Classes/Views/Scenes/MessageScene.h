#pragma once
#include "cocos2d.h"
#include "ui/UIButton.h"
USING_NS_CC;
using namespace cocos2d::ui;

class MessageScene : public Layer
{
public:
	MessageScene();
	~MessageScene();
	bool init();
	CREATE_FUNC(MessageScene);
	void close(Ref* sender = nullptr);
private:
	//Variable
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	cocos2d::Sprite *messageBackground;
	cocos2d::String *content;
	cocos2d::Label * fontContent;
	cocos2d::ui::Button * buttonYes;
	cocos2d::ui::Button * buttonNo;
	//Function
	void addBackGroundMessageScene();
	void setupFont();
	void setupMultiLanguage();
	void setupButtonYes();
	void setupButtonNo();
};


