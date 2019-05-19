#include "MessageScene.h"
#include "SonarFrameworks.h"
#include "GameManager/Definitions.h"
#include "MainMenuScene.h"
#include "MainGameScene.h"
#include "ShopScene.h"
#include "ui/UIButton.h"
#include "GameManager/LanguageManager.h"

USING_NS_CC;

MessageScene::MessageScene()
{

}
MessageScene::~MessageScene()
{
}
bool MessageScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	//
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [](Touch *touch, Event*event)->bool
	{
		return true;
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	MessageScene::setupMultiLanguage();
	MessageScene::addBackGroundMessageScene();
	MessageScene::setupFont();
	MessageScene::setupButtonYes();
	MessageScene::setupButtonNo();
	return true;
}
void MessageScene::setupButtonYes()
{
	buttonYes->setPosition(Vec2(visibleSize.width / 2 + origin.x - (-ui::Button::create("Yes.png")->getContentSize().height + (ui::Button::create("Yes.png")->getContentSize().width)), visibleSize.height / 2.3 + origin.y));
	buttonYes->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
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
			MainMenuScene::CheckGold(0);
			MainMenuScene::CheckShop(0);
			MainMenuScene::CheckMusic(1);
			MainMenuScene::CheckSound(1);
			MainMenuScene n;
			n.selectCharacter();
			//
			MainGameScene::CheckHighScore(0);
			//
			ShopScene::CheckBuyItem(0);
			this->close();
			break;
		}

		default:
			break;
		}
	});
	this->addChild(buttonYes);
}
void MessageScene::setupButtonNo()
{
	buttonNo->setPosition(Vec2(visibleSize.width / 2 + origin.x + (-ui::Button::create("No.png")->getContentSize().height + (ui::Button::create("No.png")->getContentSize().width)), visibleSize.height / 2.3 + origin.y));
	buttonNo->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
		{
			break;
		}
		case ui::Widget::TouchEventType::ENDED:
		{
			this->close();
			break;
		}

		default:
			break;
		}
	});
	this->addChild(buttonNo);
}
void MessageScene::setupMultiLanguage()
{
	int lang = MainMenuScene::CheckLanguage();
	buttonYes = ui::Button::create("Yes.png");
	buttonNo = ui::Button::create("No.png");
	if (lang == 0) // en
	{
		messageBackground = Sprite::create("PopupYesNo.png");
		content = String::createWithFormat("Do you want to reset ?");
		fontContent = Label::createWithTTF(content->getCString(), MAIN_MENU_SCENE_FONT_FILEPATH, visibleSize.height * 0.04);
		buttonYes = ui::Button::create("Yes.png");
		buttonNo = ui::Button::create("No.png");
	}
	else
	{

		messageBackground = Sprite::create("PopupYesNo.png");
		content = String::createWithFormat("Bạn có muốn đặt lại không ?");
		fontContent = Label::createWithTTF(content->getCString(), MAIN_MENU_SCENE_FONT_FILEPATH, visibleSize.height * 0.04);
		buttonYes = ui::Button::create("Co.png");
		buttonNo = ui::Button::create("Khong.png");
	}

}
void MessageScene::addBackGroundMessageScene()
{
	messageBackground->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(messageBackground);
}
void MessageScene::setupFont()
{
	//Font 
	fontContent->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 1.9 + origin.y));
	fontContent->setColor(Color3B::WHITE);
	addChild(fontContent);
}
void MessageScene::close(Ref* sender)
{
	this->removeFromParentAndCleanup(true);
}
