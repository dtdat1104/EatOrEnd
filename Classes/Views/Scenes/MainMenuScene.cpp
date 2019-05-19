#include "MainMenuScene.h"
#include "GameManager/Definitions.h"
#include "ui/UIButton.h"
#include "MainGameScene.h"
#include "AudioEngine.h"
#include "ShopScene.h"
#include "GameManager/LanguageManager.h"
#include "MessageScene.h"
#include "OptionLayer.h"
#include "GameManager/SQLiteManager.h"

USING_NS_CC;
using namespace experimental;

//Local storage
const char *SKIN_STATE = "keyskin";
const char *GOLD_STATE = "keygold";
const char *MUSIC_STATE_CHECK = "keymusic";
const char *SOUND_STATE_CHECK = "keysound";
const char *CANCEL_STATE_CHECK = "keycancel";
const char *FIRST_INSTALL = "keyinstall";
const char *LANGUAGE = "language";

Scene* MainMenuScene::createScene()
{
	return MainMenuScene::create();
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}
	//The visibleSize variable stores the current resolution of the screen 
	//The origin stores the origin of the current scene
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	//Check first game installed on your device
	MainMenuScene::checkFirstInstall();
	MainMenuScene::addBackGroundMainMenuScene();
	MainMenuScene::selectCharacter();
	MainMenuScene::setupPreLoad();
	MainMenuScene::setupButtonPlay();
	//MainMenuScene::setupButtonPlayOnline();
	MainMenuScene::setupButtonShop();
	MainMenuScene::setupButtonOption();
	MainMenuScene::setupButtonLanguage();
	MainMenuScene::loadBackGroundMusic();
	MainMenuScene::doExitGame();
	return true;
}
void MainMenuScene::checkFirstInstall()
{
	//check first install
	auto checkInstall = UserDefault::sharedUserDefault();
	int first = checkInstall->getIntegerForKey(FIRST_INSTALL);
	if (first == 0)
	{
		AudioEngine::play2d(MAIN_MENU_SCENE_MUSIC_BACKGROUND_FILEPATH, true);
		auto defMusic = UserDefault::sharedUserDefault();
		defMusic->setIntegerForKey(MUSIC_STATE_CHECK, 1);
		defMusic->flush();
		auto defSound = UserDefault::sharedUserDefault();
		defSound->setIntegerForKey(SOUND_STATE_CHECK, 1);
		defSound->flush();

		checkInstall->setIntegerForKey(FIRST_INSTALL, 1);
		checkInstall->flush();
		CCLOG("Da vo first");

	}
	else
	{

	}
}
void MainMenuScene::selectCharacter()
{
	auto def = UserDefault::sharedUserDefault();
	int skin = def->getIntegerForKey(SKIN_STATE);
	if (skin == 0) // default mouse
	{
		Mouse = Sprite::create(SHOP_SCENE_DEFAULT_SKIN_FILEPATH);
		Mouse->setAnchorPoint(Vec2(0.5, 0));
		Mouse->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - Mouse->getContentSize().height - Mouse->getContentSize().height / 4));
	}
	else
	{
		Mouse = Sprite::create(SHOP_SCENE_1_SKIN_FILEPATH);
		Mouse->setAnchorPoint(Vec2(0.5, 0));
		Mouse->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - Mouse->getContentSize().height - Mouse->getContentSize().height / 4));
	}
	addChild(Mouse);
}
void MainMenuScene::CheckCancel(int a)
{
	auto defCancel = UserDefault::sharedUserDefault();
	defCancel->setIntegerForKey(CANCEL_STATE_CHECK, a);
	defCancel->flush();
}
void MainMenuScene::CheckShop(int a)
{
	//
	auto def = UserDefault::sharedUserDefault();
	def->setIntegerForKey(SKIN_STATE, a);
	def->flush();
}
void MainMenuScene::CheckGold(int a)
{
	auto defGold = UserDefault::sharedUserDefault();
	defGold->setIntegerForKey(GOLD_STATE, a);
	defGold->flush();
}
void MainMenuScene::CheckSound(int a)
{
	auto defSound = UserDefault::sharedUserDefault();
	defSound->setIntegerForKey(SOUND_STATE_CHECK, a);
	defSound->flush();
}
void MainMenuScene::CheckMusic(int a)
{
	auto defMusic = UserDefault::sharedUserDefault();
	defMusic->setIntegerForKey(MUSIC_STATE_CHECK, a);
	defMusic->flush();
}
int MainMenuScene::CheckLanguage()
{
	auto defLanguage = UserDefault::sharedUserDefault();
	CCLOG("%d", defLanguage->getIntegerForKey(LANGUAGE));
	return defLanguage->getIntegerForKey(LANGUAGE);

}
void MainMenuScene::setupPreLoad()
{
	//preload
	AudioEngine::preload(MAIN_MENU_SCENE_MUSIC_BACKGROUND_FILEPATH); //background audio
	AudioEngine::preload(MAIN_GAME_SCENE_EAT_SOUND_FILEPATH);
	AudioEngine::preload(MAIN_GAME_SCENE_DIE_SOUND_FILEPATH);
	AudioEngine::preload(MAIN_GAME_SCENE_EAT_GOLD_SOUND_FILEPATH);
}
void MainMenuScene::addBackGroundMainMenuScene()
{
	backGroundMainMenu = Sprite::create(MAIN_MENU_SCENE_BACKGROUND_FILEPATH);
	backGroundMainMenu->setAnchorPoint(Vec2(0, 0));
	backGroundMainMenu->setPosition(Vec2(0, 0));
	this->addChild(backGroundMainMenu);
}
void MainMenuScene::loadBackGroundMusic()
{
	auto checkMusic = UserDefault::sharedUserDefault();
	int Music = checkMusic->getIntegerForKey(MUSIC_STATE_CHECK);
	if (Music == 1)
	{
		AudioEngine::stopAll();//avoid repeat a lot of
		AudioEngine::play2d(MAIN_MENU_SCENE_MUSIC_BACKGROUND_FILEPATH, true);
	}
	else
	{
		AudioEngine::stopAll();//avoid repeat a lot of
	}
}
void MainMenuScene::setupButtonPlay()
{
	auto defLanguage = UserDefault::sharedUserDefault();
	int en = defLanguage->getIntegerForKey(LANGUAGE);
	if (en == 0) // 0 - En
	{
		//button play
		buttonPlay = ui::Button::create(MAIN_MENU_SCENE_PLAY_BUTTON_FILEPATH);
		buttonPlay->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 4.5));
		buttonPlay->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType typeplay)
		{
			switch (typeplay)
			{
			case ui::Widget::TouchEventType::BEGAN:
			{

				break;
			}
			case ui::Widget::TouchEventType::ENDED: {
				//
				auto def = UserDefault::sharedUserDefault();
				int skin = def->getIntegerForKey(SKIN_STATE);
				//
				auto defSound = UserDefault::sharedUserDefault();
				int soundstate = defSound->getIntegerForKey(SOUND_STATE_CHECK);
				//check turn off popup
				auto defCancel = UserDefault::sharedUserDefault();
				int cancelstate = defCancel->getIntegerForKey(CANCEL_STATE_CHECK);
				//
				/* if (cancelstate == 1)
				{*/
				auto inGame = MainGameScene::createScene(soundstate, skin, false);
				TransitionFade *transition = TransitionFade::create(SCENE_TRANSITION_TIME, inGame);
				Director::getInstance()->replaceScene(transition);

				CCLOG("Da vo choi game");
				//}
				break;
			}
			default:
				break;
			}
		});
		addChild(buttonPlay);
	}
	else if (en == 1)
	{
		defLanguage->setStringForKey("LANGUAGE", "vi");
		buttonPlay = ui::Button::create(LanguageManager::getInstance()->getStringForKey("MAIN_MENU_SCENE_PLAY_BUTTON_FILEPATH").c_str());
		buttonPlay->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 4.5));
		buttonPlay->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType typeplay)
		{
			switch (typeplay)
			{
			case ui::Widget::TouchEventType::BEGAN:
			{

				break;
			}
			case ui::Widget::TouchEventType::ENDED: {
				//
				auto def = UserDefault::sharedUserDefault();
				int skin = def->getIntegerForKey(SKIN_STATE);
				//
				auto defSound = UserDefault::sharedUserDefault();
				int soundstate = defSound->getIntegerForKey(SOUND_STATE_CHECK);
				//check turn off popup
				auto defCancel = UserDefault::sharedUserDefault();
				int cancelstate = defCancel->getIntegerForKey(CANCEL_STATE_CHECK);
				//
				/* if (cancelstate == 1)
				{*/
				auto inGame = MainGameScene::createScene(soundstate, skin, false);
				TransitionFade *transition = TransitionFade::create(SCENE_TRANSITION_TIME, inGame);
				Director::getInstance()->replaceScene(transition);

				CCLOG("Da vo choi game");
				//}
				break;
			}
			default:
				break;
			}
		});
		addChild(buttonPlay);
	}
}
void MainMenuScene::setupButtonPlayOnline()
{
	buttonPlay = ui::Button::create(MAIN_MENU_SCENE_PLAY_BUTTON_FILEPATH);
	buttonPlay->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 3));
	buttonPlay->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType typeplay)
	{
		switch (typeplay)
		{
		case ui::Widget::TouchEventType::BEGAN:
		{

			break;
		}
		case ui::Widget::TouchEventType::ENDED: {
			//
			/*auto roomScene = RoomScene::createScene();
			TransitionFade *transition = TransitionFade::create(SCENE_TRANSITION_TIME, roomScene);
			Director::getInstance()->replaceScene(transition);*/
			break;
		}
		default:
			break;
		}
	});
	addChild(buttonPlay);

}
void MainMenuScene::setupButtonShop()
{
	buttonShop = ui::Button::create(MAIN_MENU_SCENE_SHOP_BUTTON_FILEPATH);
	buttonShop->setPosition(Vec2(visibleSize.width / 1.8 + Button::create(MAIN_MENU_SCENE_SOUND_BUTTON_FILEPATH)->getContentSize().width, visibleSize.height / 10.5));
	buttonShop->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
		{


			break;
		}
		case ui::Widget::TouchEventType::ENDED:
		{
			//
			auto defGold = UserDefault::sharedUserDefault();
			int m_gold = defGold->getIntegerForKey(GOLD_STATE);
			//
			auto defSound = UserDefault::sharedUserDefault();
			int soundstate = defSound->getIntegerForKey(SOUND_STATE_CHECK);
			//
			auto defCancel = UserDefault::sharedUserDefault();
			int cancelstate = defCancel->getIntegerForKey(CANCEL_STATE_CHECK);
			//
			auto shop = ShopScene::createScene(m_gold, soundstate);
			TransitionFade *transition = TransitionFade::create(SCENE_TRANSITION_TIME, shop);
			Director::getInstance()->replaceScene(transition);
			break;
		}

		default:
			break;
		}
	});

	this->addChild(buttonShop);
}
void MainMenuScene::setupButtonOption()
{
	buttonOption = ui::Button::create("BTChoose.png");
	buttonOption->setPosition(Vec2(visibleSize.width / 2.3 - Button::create("BTChoose.png")->getContentSize().width, visibleSize.height / 10.5));
	buttonOption->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
		{

			break;
		}
		case ui::Widget::TouchEventType::ENDED:
		{
			//
			auto defCancel = UserDefault::sharedUserDefault();
			int cancelstate = defCancel->getIntegerForKey(CANCEL_STATE_CHECK);
			//
			optionLayer = OptionLayer::create();
			this->addChild(optionLayer);

			break;
		}

		default:
			break;
		}
	});
	this->addChild(buttonOption);
}
void MainMenuScene::setupButtonLanguage()
{
	auto defLanguage = UserDefault::sharedUserDefault();

	//
	int en = defLanguage->getIntegerForKey(LANGUAGE);
	if (en == 0)
	{
		buttonLanguage = ui::CheckBox::create("BTVn.png", "BTEng.png");
	}
	else
	{
		buttonLanguage = ui::CheckBox::create("BTEng.png", "BTVn.png");
	}
	buttonLanguage->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 10.5));
	buttonLanguage->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
		{

			break;
		}
		case ui::Widget::TouchEventType::ENDED:
		{
			//
			auto defLanguage = UserDefault::sharedUserDefault();
			//
			int en = defLanguage->getIntegerForKey(LANGUAGE);
			if (en == 0) // 0 - En
			{
				//
				defLanguage->setStringForKey("LANGUAGE", "en");
				//
				defLanguage->setIntegerForKey(LANGUAGE, 1);
				defLanguage->flush();
				//
				buttonPlay = ui::Button::create(LanguageManager::getInstance()->getStringForKey("MAIN_MENU_SCENE_PLAY_BUTTON_FILEPATH").c_str());
				buttonPlay->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 4.5));
				buttonPlay->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType typeplay)
				{
					switch (typeplay)
					{
					case ui::Widget::TouchEventType::BEGAN:
					{

						break;
					}
					case ui::Widget::TouchEventType::ENDED: {
						//
						auto def = UserDefault::sharedUserDefault();
						int skin = def->getIntegerForKey(SKIN_STATE);
						//
						auto defSound = UserDefault::sharedUserDefault();
						int soundstate = defSound->getIntegerForKey(SOUND_STATE_CHECK);
						//check turn off popup
						auto defCancel = UserDefault::sharedUserDefault();
						int cancelstate = defCancel->getIntegerForKey(CANCEL_STATE_CHECK);
						//
						/* if (cancelstate == 1)
						{*/
						auto inGame = MainGameScene::createScene(soundstate, skin, false);
						TransitionFade *transition = TransitionFade::create(SCENE_TRANSITION_TIME, inGame);
						Director::getInstance()->replaceScene(transition);

						CCLOG("Da vo choi game");
						//}
						break;
					}
					default:
						break;
					}
				});
				addChild(buttonPlay);
			}
			else if (en == 1) //1 - VN
			{
				//
				defLanguage->setIntegerForKey(LANGUAGE, 0);
				defLanguage->flush();
				//
				buttonPlay = ui::Button::create(MAIN_MENU_SCENE_PLAY_BUTTON_FILEPATH);
				buttonPlay->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 4.5));
				buttonPlay->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType typeplay)
				{
					switch (typeplay)
					{
					case ui::Widget::TouchEventType::BEGAN:
					{

						break;
					}
					case ui::Widget::TouchEventType::ENDED: {
						//
						auto def = UserDefault::sharedUserDefault();
						int skin = def->getIntegerForKey(SKIN_STATE);
						//
						auto defSound = UserDefault::sharedUserDefault();
						int soundstate = defSound->getIntegerForKey(SOUND_STATE_CHECK);
						//check turn off popup
						auto defCancel = UserDefault::sharedUserDefault();
						int cancelstate = defCancel->getIntegerForKey(CANCEL_STATE_CHECK);
						//
						auto inGame = MainGameScene::createScene(soundstate, skin, false);
						TransitionFade *transition = TransitionFade::create(SCENE_TRANSITION_TIME, inGame);
						Director::getInstance()->replaceScene(transition);

						CCLOG("Da vo choi game");
						//}
						break;
					}
					default:
						break;
					}
				});
				addChild(buttonPlay);
			}

			break;
		}
		default:
			break;
		}
	});
	this->addChild(buttonLanguage);
}
void MainMenuScene::doExitGame()
{
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = CC_CALLBACK_2(MainMenuScene::onExitGame, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}
void MainMenuScene::onExitGame(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_BACK)
	{
		Director::getInstance()->end();
	}
}


