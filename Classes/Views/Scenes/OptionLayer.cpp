#include "OptionLayer.h"
#include "SonarFrameworks.h"
#include "GameManager/Definitions.h"
#include "AudioEngine.h"
#include "MainMenuScene.h"
#include "MessageScene.h"

USING_NS_CC;

const char *SETTING_STATE_LAYER = "keysetting";
const char *CANCEL_STATE_LAYER = "keycancel";
const char *MUSIC_STATE_LAYER = "keymusic";
const char *SOUND_STATE_LAYER = "keysound";

bool OptionLayer::init()
{
	Size screenSize = Director::getInstance()->getVisibleSize();
	//
	auto def = UserDefault::sharedUserDefault();
	def->setIntegerForKey(SETTING_STATE_LAYER, 1);
	def->flush();
	//
	auto defCancel = UserDefault::sharedUserDefault();
	defCancel->setIntegerForKey(CANCEL_STATE_LAYER, 0);
	defCancel->flush();
	//
	OptionLayer::addBackGroundOptionLayer();
	//
	int lang = MainMenuScene::CheckLanguage();
	if (lang == 0) // en
	{
		overlayOptionWindowItem = MenuItemImage::create("BackGroundChoose.png", "BackGroundChoose.png", "BackGroundChoose.png", NULL);
	}
	else
	{
		overlayOptionWindowItem = MenuItemImage::create("VnBackGroundChoose.png", "VnBackGroundChoose.png", "VnBackGroundChoose.png", NULL);
	}
	//check sound
	OptionLayer::setupCheckBoxSound();
	OptionLayer::setupCheckBoxMusic();
	OptionLayer::setupButtonCancel();
	OptionLayer::setupButtonReset();
	OptionLayer::setupMenu();
	OptionLayer::showOptionScene();
	return true;
}
void OptionLayer::showOptionScene()
{
	Size screenSize = Director::getInstance()->getVisibleSize();
	auto def = UserDefault::sharedUserDefault();
	int setting_state = def->getIntegerForKey(SETTING_STATE_LAYER);
	int cancel_state = def->getIntegerForKey(CANCEL_STATE_LAYER);
	if (1 == setting_state && cancel_state == 0)
	{
		//Display background popup and make scene opacity (30)
		settingbackground->runAction(FadeIn::create(0.5));
		//
		EaseBounceOut *menuActionEasing = EaseBounceOut::create(MoveTo::create(1.5, SonarCocosHelper::UI::GetScreenCenter()));
		menu->runAction(menuActionEasing);
		//
		auto defGold = UserDefault::sharedUserDefault();
		defGold->setIntegerForKey(CANCEL_STATE_LAYER, 1);
		defGold->flush();
		//
		MainMenuScene::CheckCancel(0);
		CCLOG("đã vào 1");
	}
	else
	{

		CCLOG("đã vào 0");
	}
}
void OptionLayer::addBackGroundOptionLayer()
{
	Size screenSize = Director::getInstance()->getVisibleSize();
	settingbackground = Sprite::create(POPUP_SCENE_BACKGROUND_FILEPATH);
	settingbackground->setAnchorPoint(Vec2(0, 0));
	settingbackground->setPosition(Vec2(0, 0));
	settingbackground->setOpacity(0);
	this->addChild(settingbackground);
}
void OptionLayer::setupCheckBoxSound()
{
	Size screenSize = Director::getInstance()->getVisibleSize();
	auto checkSound = UserDefault::sharedUserDefault();
	int SoundState = checkSound->getIntegerForKey(SOUND_STATE_LAYER);
	if (SoundState == 1)
	{
		checkboxSound = ui::CheckBox::create(MAIN_MENU_SCENE_SOUND_BUTTON_FILEPATH, MAIN_MENU_SCENE_SOUND_XBUTTON_FILEPATH);
		soundItem = MenuItemSprite::create(checkboxSound, checkboxSound);
		soundItem->setPosition(Vec2(-overlayOptionWindowItem->getContentSize().width / 4, (overlayOptionWindowItem->getContentSize().height / 3)));
		OptionLayer::callCheckBoxSound();
	}
	else
	{
		checkboxXSound = ui::CheckBox::create(MAIN_MENU_SCENE_SOUND_XBUTTON_FILEPATH, MAIN_MENU_SCENE_SOUND_BUTTON_FILEPATH);
		soundItem = MenuItemSprite::create(checkboxXSound, checkboxXSound);
		soundItem->setPosition(Vec2(-overlayOptionWindowItem->getContentSize().width / 4, (overlayOptionWindowItem->getContentSize().height / 3)));
		OptionLayer::callCheckBoxSoundX();
	}
}
void OptionLayer::callCheckBoxSound()
{

	checkboxSound->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
		{

			break;
		}
		case ui::Widget::TouchEventType::ENDED:
		{
			auto checkSound = UserDefault::sharedUserDefault();
			int SoundState = checkSound->getIntegerForKey(SOUND_STATE_LAYER);
			if (SoundState == 1)
			{

				auto defSound = UserDefault::sharedUserDefault();
				defSound->setIntegerForKey(SOUND_STATE_LAYER, 0);
				defSound->flush();
			}
			else
			{
				auto defSound = UserDefault::sharedUserDefault();
				defSound->setIntegerForKey(SOUND_STATE_LAYER, 1);
				defSound->flush();
			}
			auto checkSoundMainMenu = UserDefault::sharedUserDefault();
			int SoundMainMenu = checkSound->getIntegerForKey(SOUND_STATE_LAYER);
			MainMenuScene::CheckSound(SoundMainMenu);
			//messageScene = new MessageScene((Layer*)this);

			break;
		}

		default:
			break;
		}
	});



}
void OptionLayer::callCheckBoxSoundX()
{
	checkboxXSound->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
		{
			break;
		}
		case ui::Widget::TouchEventType::ENDED:
		{
			auto checkSound = UserDefault::sharedUserDefault();
			int SoundState = checkSound->getIntegerForKey(SOUND_STATE_LAYER);
			if (SoundState == 0)
			{
				auto defSound = UserDefault::sharedUserDefault();
				defSound->setIntegerForKey(SOUND_STATE_LAYER, 1);
				defSound->flush();
			}
			else
			{
				auto defSound = UserDefault::sharedUserDefault();
				defSound->setIntegerForKey(SOUND_STATE_LAYER, 0);
				defSound->flush();
			}
			auto checkSoundMainMenu = UserDefault::sharedUserDefault();
			int SoundMainMenu = checkSound->getIntegerForKey(SOUND_STATE_LAYER);
			MainMenuScene::CheckSound(SoundMainMenu);
			break;
		}

		default:
			break;
		}
	});
}
void OptionLayer::setupCheckBoxMusic()
{
	Size screenSize = Director::getInstance()->getVisibleSize();
	auto checkMusic = UserDefault::sharedUserDefault();
	int MusicState = checkMusic->getIntegerForKey(MUSIC_STATE_LAYER);
	if (MusicState == 1)
	{
		checkboxMusic = ui::CheckBox::create("BTMusic.png", MAIN_MENU_SCENE_MUSIC_XBUTTON_FILEPATH);
		musicItem = MenuItemSprite::create(checkboxMusic, checkboxMusic);
		musicItem->setPosition(Vec2(overlayOptionWindowItem->getContentSize().width / overlayOptionWindowItem->getContentSize().width, (overlayOptionWindowItem->getContentSize().height / 3)));
		OptionLayer::callCheckBoxMusic();
	}
	else
	{
		checkboxXMusic = ui::CheckBox::create(MAIN_MENU_SCENE_MUSIC_XBUTTON_FILEPATH, "BTMusic.png");
		musicItem = MenuItemSprite::create(checkboxXMusic, checkboxXMusic);
		musicItem->setPosition(Vec2(overlayOptionWindowItem->getContentSize().width / overlayOptionWindowItem->getContentSize().width, (overlayOptionWindowItem->getContentSize().height / 3)));
		OptionLayer::callCheckBoxMusicX();
	}
}
void OptionLayer::callCheckBoxMusic()
{
	checkboxMusic->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
		{

			break;
		}
		case ui::Widget::TouchEventType::ENDED:
		{
			auto checkMusic = UserDefault::sharedUserDefault();
			int MusicState = checkMusic->getIntegerForKey(MUSIC_STATE_LAYER);
			if (MusicState == 1)
			{
				cocos2d::experimental::AudioEngine::stopAll();
				auto defMusic = UserDefault::sharedUserDefault();
				defMusic->setIntegerForKey(MUSIC_STATE_LAYER, 0);
				defMusic->flush();
			}
			else
			{
				cocos2d::experimental::AudioEngine::stopAll();
				cocos2d::experimental::AudioEngine::play2d(MAIN_MENU_SCENE_MUSIC_BACKGROUND_FILEPATH, true);
				auto defMusic = UserDefault::sharedUserDefault();
				defMusic->setIntegerForKey(MUSIC_STATE_LAYER, 1);
				defMusic->flush();
			}
			auto checkMusicMainMenu = UserDefault::sharedUserDefault();
			int MusicMainMenu = checkMusicMainMenu->getIntegerForKey(MUSIC_STATE_LAYER);
			MainMenuScene::CheckMusic(MusicMainMenu);
			break;
		}

		default:
			break;
		}
	});
}
void OptionLayer::callCheckBoxMusicX()
{
	checkboxXMusic->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
		{
			break;
		}
		case ui::Widget::TouchEventType::ENDED:
		{
			auto checkMusic = UserDefault::sharedUserDefault();
			int MusicState = checkMusic->getIntegerForKey(MUSIC_STATE_LAYER);
			if (MusicState == 0)
			{
				cocos2d::experimental::AudioEngine::stopAll();
				cocos2d::experimental::AudioEngine::play2d(MAIN_MENU_SCENE_MUSIC_BACKGROUND_FILEPATH, true);
				auto defMusic = UserDefault::sharedUserDefault();
				defMusic->setIntegerForKey(MUSIC_STATE_LAYER, 1);
				defMusic->flush();
			}
			else
			{
				cocos2d::experimental::AudioEngine::stopAll();
				auto defMusic = UserDefault::sharedUserDefault();
				defMusic->setIntegerForKey(MUSIC_STATE_LAYER, 0);
				defMusic->flush();
			}
			auto checkMusicMainMenu = UserDefault::sharedUserDefault();
			int MusicMainMenu = checkMusicMainMenu->getIntegerForKey(MUSIC_STATE_LAYER);
			MainMenuScene::CheckMusic(MusicMainMenu);

			break;
		}

		default:
			break;
		}
	});
}
void OptionLayer::setupButtonCancel()
{

	buttonCancel = ui::Button::create("BTX.png");
	cancelItem = MenuItemSprite::create(buttonCancel, buttonCancel);
	cancelItem->setPosition(Vec2(overlayOptionWindowItem->getContentSize().width / 2.5, -(overlayOptionWindowItem->getContentSize().height / 2)));
	OptionLayer::callButtonCancel();
}
void OptionLayer::callButtonCancel()
{
	buttonCancel->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
		{
			break;
		}
		case ui::Widget::TouchEventType::ENDED:
		{

			Size screenSize = Director::getInstance()->getVisibleSize();

			settingbackground->runAction(FadeOut::create(0.5));

			EaseBounceOut *menuActionEasing = EaseBounceOut::create(MoveTo::create(1.5, Vec2(SonarCocosHelper::UI::GetScreenCenter().x, SonarCocosHelper::UI::GetScreenCenter().y + screenSize.height)));
			menu->runAction(menuActionEasing);

			auto defGold = UserDefault::sharedUserDefault();
			defGold->setIntegerForKey(CANCEL_STATE_LAYER, 0);
			defGold->flush();
			//
			MainMenuScene::CheckCancel(1);
			break;
		}

		default:
			break;
		}
	});
}
void OptionLayer::setupButtonReset()
{
	buttonReset = ui::Button::create("BTReset.png");
	resetItem = MenuItemSprite::create(buttonReset, buttonReset, buttonReset);
	resetItem->setPosition(Vec2(overlayOptionWindowItem->getContentSize().width / 4, (overlayOptionWindowItem->getContentSize().height / 3)));
	OptionLayer::callButtonReset();
}
void OptionLayer::callButtonReset()
{
	buttonReset->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
		{
			break;
		}
		case ui::Widget::TouchEventType::ENDED:
		{


			messageScene = MessageScene::create();
			this->addChild(messageScene);
			this->setOpacity(255);
			break;
		}
		default:
			break;
		}
	});
}
void OptionLayer::setupMenu()
{
	Size screenSize = Director::getInstance()->getVisibleSize();
	menu = Menu::create(overlayOptionWindowItem, soundItem, musicItem, resetItem, cancelItem, NULL);
	menu->setPosition(Vec2(SonarCocosHelper::UI::GetScreenCenter().x, SonarCocosHelper::UI::GetScreenCenter().y + screenSize.height));
	this->addChild(menu);
}
void OptionLayer::CheckCancel()
{
	auto defCancel = UserDefault::sharedUserDefault();
	defCancel->setIntegerForKey(CANCEL_STATE_LAYER, 0);
	defCancel->flush();
}

