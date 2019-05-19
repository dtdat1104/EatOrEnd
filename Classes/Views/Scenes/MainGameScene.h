#ifndef __MAINGAME_SCENE_H__
#define __MAINGAME_SCENE_H__

#include "cocos2d.h"
#define SCROLLING_BACKGROUND_SPEED 0.002
USING_NS_CC;
class MainGameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene(int touchItems, int skin,bool flagContinue);

    virtual bool init();   
    // implement the "static create()" method manually
    CREATE_FUNC(MainGameScene);
	/*Animation*/
	void update(float);
	bool onTouchBegan(Touch *touch, Event *unused_evnent);
	void SwingMouse(float);
	void CreateItems(float);
	void CreateGold(float);
	void LabelFunction();
	bool OnContactBegan(cocos2d::PhysicsContact &contact);//check collison
	//
	static void CheckGoldShop(int);
	static void CheckHighScore(int);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
private:
	//Physics 
	cocos2d::PhysicsWorld *world;
	void setPhysicWorld(cocos2d::PhysicsWorld * m_world)
	{
		world = m_world;
	}
	Size visibleSize;
	Vec2 origin;
	cocos2d::Sprite * sprites;
	cocos2d::Sprite * background1;
	cocos2d::Sprite * background2;
	
	bool checkState = true;
	int checkStateClicked = 0;
	cocos2d::Sprite * Mouse;
	cocos2d::Label *label;

	cocos2d::Label *tempScore;// score +1
	int score = 0;
	//
	cocos2d::Label *labelhighScore;
	int iHighScore = 0;
	cocos2d::Label *labelGold;
	int iGold = 0;
	//Count gold
	int countGold = 0;
	//
	int swingtime = 1.7;
	int itemtime = 2;

	//
	
};

#endif // __MAINGAME_SCENE_H__
