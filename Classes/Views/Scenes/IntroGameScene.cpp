#include "IntroGameScene.h"
#include "SonarFrameworks.h"
#include "GameManager/Definitions.h"
#include "MainMenuScene.h"
#include "wxsqlite\sqlite3.h"
#include <iostream>

USING_NS_CC;

Scene* IntroGameScene::createScene()
{
	return IntroGameScene::create();
}
// on "init" you need to initialize your instance
bool IntroGameScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}
	//Add background
	addBackGroundInTroGameScene();
	//exit game when pressing the back button
	doExitGame();
	return true;
}
void IntroGameScene::addBackGroundInTroGameScene()
{
	auto backGroundIntroGameScene = Sprite::create(INTRO_GAME_SCENE_BACKGROUND_FILEPATH);
	backGroundIntroGameScene->setAnchorPoint(Vec2(0, 0));
	backGroundIntroGameScene->setPosition(Vec2(0, 0));
	scheduleOnce(schedule_selector(IntroGameScene::switchToMainMenuScene), SPLASH_SCENE_SHOW_TIME);
	this->addChild(backGroundIntroGameScene);
}
void IntroGameScene::doExitGame()
{
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = CC_CALLBACK_2(IntroGameScene::onExitGame, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}
void IntroGameScene::onExitGame(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_BACK)
	{
		Director::getInstance()->end();
	}
}
void IntroGameScene::switchToMainMenuScene(float transitionTime)
{
	Scene * scene = MainMenuScene::createScene();
	TransitionFade * transition = TransitionFade::create(SCENE_TRANSITION_TIME, scene);
	Director::getInstance()->replaceScene(transition);
}


