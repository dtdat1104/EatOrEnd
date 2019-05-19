#ifndef __SHOP_SCENE_H__
#define __SHOP_SCENE_H__

#include "cocos2d.h"
#include "ui/UIButton.h"
#include "wxsqlite\sqlite3.h"
#define SCROLLING_BACKGROUND_SPEED 0.002
USING_NS_CC;
using namespace cocos2d::ui;
class ShopScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene(int gold, int touchitems);
	virtual bool init();
	// implement the "static create()" method manually
	CREATE_FUNC(ShopScene);
	//void onEnter();
	void MouseSkinDefault();
	void AddMouseDefault();
	void CountGold();
	//Add item
	void Item1();
	void Item2();
	//
	static void CheckBuyItem(int);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	//
	void addLabel(std::string price,std::string filePath, float positionWidth, float positionHeight);
	void addItem(std::string filePathItem, float positionWidth, float positionHeight, int tag);
	void test(std::vector<std::string> a);
private:
	bool checkbuy = false;
	cocos2d::Sprite * MouseSkin;
	cocos2d::Sprite * Mouse;
	cocos2d::Label * labelGold;
	cocos2d::ui::Button * buttonPlay;
	cocos2d::ui::Button * buttonMouseSkin;
	Size visibleSize;
};

#endif // __SHOP_SCENE_H__
