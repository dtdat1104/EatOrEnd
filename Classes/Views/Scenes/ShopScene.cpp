#include "MainGameScene.h"
#include "SimpleAudioEngine.h"
#include "ShopScene.h"
#include "ui/CocosGUI.h"
#include "MainMenuScene.h"
#include "ui/UICheckBox.h"
#include "GameManager/Definitions.h"
#include "wxsqlite\sqlite3.h"
#include <string>

using namespace cocos2d::ui;
USING_NS_CC;
//
const char *CHECK_SKIN = "check";
const char *CHECK_BUY = "checkbuy";
//
int m_goldShop;
int m_touchitemsshop;

Scene* ShopScene::createScene(int gold, int touchitems)
{
	m_goldShop = gold;
	m_touchitemsshop = touchitems;
	return ShopScene::create();
}
// on "init" you need to initialize your instance
bool ShopScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}
	
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//add scene
	auto sceneShop = Sprite::create(SHOP_SCENE_BACKGROUND_FILEPATH);
	sceneShop->setAnchorPoint(Vec2(0, 0));
	sceneShop->setPosition(Vec2(0, 0));
	this->addChild(sceneShop, 1);
	//Default Mouse
	Mouse = Sprite::create(SHOP_SCENE_DEFAULT_SKIN_FILEPATH);
	Mouse->setAnchorPoint(Vec2(0.5, 0));
	Mouse->setPosition(Vec2(visibleSize.width / 2, (visibleSize.height - (Mouse->getContentSize().height) - 80)));
	addChild(Mouse, 5);
	//button back
	auto buttonBack = ui::Button::create(FINISH_GAME_SCENE_BACK_BUTTON_FILEPATH);
	buttonBack->setPosition(Vec2(visibleSize.width * 0.09, visibleSize.height*0.94));
	buttonBack->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
		{
			auto menuGame = MainMenuScene::createScene();
			TransitionFade *transition = TransitionFade::create(SCENE_TRANSITION_TIME, menuGame);
			Director::getInstance()->replaceScene(transition);
			break;
		}
		case ui::Widget::TouchEventType::ENDED:
		{

			break;
		}

		default:
			break;
		}
	});
	addChild(buttonBack, 2);
	//BTCoin and Label display coin
	auto coinDisplay = ui::Button::create(MAIN_GAME_SCENE_COIN_BUTTON_FILEPATH);
	coinDisplay->setPosition(Vec2(visibleSize.width *0.75, visibleSize.height*0.94));
	addChild(coinDisplay, 2);
	//Label display gold
	String *gold = String::createWithFormat("%i", m_goldShop);
	labelGold = Label::createWithTTF(gold->getCString(), MAIN_GAME_SCENE_FONT_FILEPATH, visibleSize.height * 0.05);
	labelGold->setPosition(Vec2(visibleSize.width * 0.8 + 30, visibleSize.height*0.94));
	labelGold->setColor(Color3B::WHITE);
	addChild(labelGold, 5);
	//Add Items
	ShopScene::MouseSkinDefault();
	Item1();
	//Item2();
	Item2();

	//button play
	int lang = MainMenuScene::CheckLanguage();
	if (lang == 0) // en
	{
		buttonPlay = ui::Button::create(MAIN_MENU_SCENE_PLAY_BUTTON_FILEPATH);
	}
	else
	{
		buttonPlay = ui::Button::create("VnBTPlay.png");
	}
	buttonPlay->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*0.09));
	buttonPlay->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
		{
			
			break;
		}

		case ui::Widget::TouchEventType::ENDED:
		{
			auto defSkin = UserDefault::sharedUserDefault();
			int skin = defSkin->getIntegerForKey(CHECK_SKIN);
			auto inGame = MainGameScene::createScene(m_touchitemsshop, skin, false);
			Director::getInstance()->replaceScene(inGame);
			break;
		}
			
		default:
			break;
		}
	});
	addChild(buttonPlay, 2);
	//back button in android
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = CC_CALLBACK_2(ShopScene::onKeyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	//Sql lite

	return true;
}
void ShopScene::test(std::vector<std::string> a)
{
	CCLOG("%s", a.at(0).c_str());
}
void ShopScene::addLabel(std::string price,std::string filePath, float positionWidth, float positionHeight)
{
	auto labelPrice = Label::createWithTTF(price, filePath, visibleSize.height * 0.02);
	labelPrice->setPosition(Vec2(positionWidth, positionHeight));
	labelPrice->setColor(Color3B::WHITE);
	addChild(labelPrice, 5);
	auto visibleSize = Director::getInstance()->getVisibleSize();
}
void ShopScene::addItem(std::string filePath,float positionWidth, float positionHeight, int tag)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	buttonMouseSkin = ui::Button::create(filePath);
	buttonMouseSkin->setAnchorPoint(Vec2(0.5, 0));
	buttonMouseSkin->setPosition(Vec2(positionWidth, positionHeight));
	buttonMouseSkin->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
		{
			auto visibleSize = Director::getInstance()->getVisibleSize();
			removeChild(Mouse);
			//Add one model into the ShopScene
			//if enough
			auto defSkin = UserDefault::sharedUserDefault();
			int skin = defSkin->getIntegerForKey(CHECK_SKIN);//check system skin
			int buy = defSkin->getIntegerForKey(CHECK_BUY);
			if (buy != 1)
			{
				if (m_goldShop >= 10) //
				{
					//Display button buy
					auto buttonBuy = ui::Button::create(SHOP_SCENE_BUY_BUTTON_FILEPATH);
					buttonBuy->setPosition(Vec2(visibleSize.width / 2, (visibleSize.height - (MouseSkin->getContentSize().height) - 110)));
					buttonBuy->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
					{
						switch (type)
						{
						case ui::Widget::TouchEventType::BEGAN:
						{
							if (checkbuy == false)
							{
								ShopScene::CountGold();
							}
							//check bought
							auto defSkin = UserDefault::sharedUserDefault();
							defSkin->setIntegerForKey(CHECK_SKIN, 1); //items 1 bought
							
							defSkin->flush();
							//
							defSkin->setIntegerForKey(CHECK_BUY, 1);
							defSkin->flush();
							//check bought by class MainMenuScene
							MainMenuScene::CheckShop(skin);
							//
							removeChildByTag(15);
							//button bought
							auto buttonBuyed = ui::Button::create(SHOP_SCENE_BOUGHT_BUTTON_FILEPATH);
							buttonBuyed->setPosition(Vec2(visibleSize.width / 2, (visibleSize.height - (MouseSkin->getContentSize().height) - 110)));
							addChild(buttonBuyed, 2);
							break;
						}

						case ui::Widget::TouchEventType::ENDED:
						{

							break;
						}
						default:
							break;
						}
					});
					addChild(buttonBuy, 2, 15);
					break;
				}
			}
			else
			{
				auto defSkin = UserDefault::sharedUserDefault();
				defSkin->setIntegerForKey(CHECK_SKIN, 1); //items 1 buyed
				defSkin->flush();
				int skin = defSkin->getIntegerForKey(CHECK_SKIN);
				MainMenuScene::CheckShop(skin);
				removeChildByTag(15);
				auto buttonBuyed = ui::Button::create(SHOP_SCENE_BOUGHT_BUTTON_FILEPATH);
				buttonBuyed->setPosition(Vec2(visibleSize.width / 2, (visibleSize.height - (MouseSkin->getContentSize().height) - 110)));
				addChild(buttonBuyed, 2);

			}
			break;
		}
		case ui::Widget::TouchEventType::ENDED:
			break;
		default:
			break;
		}
	});
	addChild(buttonMouseSkin, 2,tag);
}
void ShopScene::CountGold()
{
	checkbuy = true;
	m_goldShop -= 10;
	String *gold = String::createWithFormat("%i", m_goldShop);
	labelGold->setString(gold->getCString());
	MainGameScene::CheckGoldShop(m_goldShop);
}
void ShopScene::AddMouseDefault()
{
	Mouse = Sprite::create(SHOP_SCENE_DEFAULT_SKIN_FILEPATH);
	Mouse->setAnchorPoint(Vec2(0.5, 0));
	Mouse->setPosition(Vec2(visibleSize.width / 2, (visibleSize.height - (Mouse->getContentSize().height) - 80)));
	addChild(Mouse, 5);
}
void ShopScene::MouseSkinDefault()
{
	visibleSize = Director::getInstance()->getVisibleSize();
	//Mouse skins default
	auto buttonMouseSkin = ui::Button::create(SHOP_SCENE_DEFAULT_SMALL_SKIN_FILEPATH);
	buttonMouseSkin->setAnchorPoint(Vec2(0.5, 0));
	buttonMouseSkin->setPosition(Vec2(visibleSize.width / 4.2, visibleSize.height / 2.10));
	buttonMouseSkin->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType typea)
	{
		switch (typea)
		{
		case ui::Widget::TouchEventType::BEGAN:
		{
			//removeChild(MouseSkin);
			break;
		}
		case ui::Widget::TouchEventType::ENDED:
		{
			ShopScene::AddMouseDefault();
			CCLOG("Da them");
			auto defSkin = UserDefault::sharedUserDefault();
			defSkin->setIntegerForKey(CHECK_SKIN, 0); //items 0 selected
			defSkin->flush();
			//
			int skin = defSkin->getIntegerForKey(CHECK_SKIN);
			MainMenuScene::CheckShop(skin);
			break;
		}
		default:
			break;
		}
	});
	addChild(buttonMouseSkin, 2);
}
void ShopScene::Item1()
{
	//label price 10
	ShopScene::addLabel("10",MAIN_GAME_SCENE_FONT_FILEPATH, visibleSize.width / 2, visibleSize.height / 2.27);
	//Mouse skins 1
	ShopScene::addItem(SHOP_SCENE_1_SMALL_SKIN_FILEPATH,visibleSize.width / 2, visibleSize.height / 2.10,1);
	
}
void ShopScene::Item2()
{
	//label price 10
	ShopScene::addLabel("50", MAIN_GAME_SCENE_FONT_FILEPATH, visibleSize.width / 1.32, visibleSize.height / 2.27);
	//Mouse skins 1
	ShopScene::addItem(SHOP_SCENE_2_SMALL_SKIN_FILEPATH, visibleSize.width / 1.32, visibleSize.height / 2.10, 2);
}
//void ShopScene::Item2() // price width height 
//{
//	//label price 10
//	auto labelPrice = Label::createWithTTF("50", MAIN_GAME_SCENE_FONT_FILEPATH, visibleSize.height * 0.02);
//	labelPrice->setPosition(Vec2(visibleSize.width / 1.32, visibleSize.height / 2.27));
//	labelPrice->setColor(Color3B::WHITE);
//	addChild(labelPrice, 5);
//	auto visibleSize = Director::getInstance()->getVisibleSize();
//	//Mouse skins 2
//	auto buttonMouseSkin = ui::Button::create(SHOP_SCENE_2_SMALL_SKIN_FILEPATH);
//	buttonMouseSkin->setAnchorPoint(Vec2(0.5, 0));
//	buttonMouseSkin->setPosition(Vec2(visibleSize.width/1.32, visibleSize.height / 2.10));
//	buttonMouseSkin->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
//	{
//		switch (type)
//		{
//		case ui::Widget::TouchEventType::BEGAN:
//		{
//			removeChild(Mouse);
//			auto visibleSize = Director::getInstance()->getVisibleSize();
//			MouseSkin = Sprite::create(SHOP_SCENE_2_SKIN_FILEPATH);
//			MouseSkin->setAnchorPoint(Vec2(0.5, 0));
//			MouseSkin->setPosition(Vec2(visibleSize.width / 2, (visibleSize.height - (MouseSkin->getContentSize().height) - 80)));
//			addChild(MouseSkin, 5);
//
//			//if enough
//			auto defSkin = UserDefault::sharedUserDefault();
//			int skin = defSkin->getIntegerForKey(CHECK_SKIN);//check system skin
//			int buy = defSkin->getIntegerForKey(CHECK_BUY);
//			if (buy != 1)
//			{
//				if (m_goldShop >= 50) //
//				{
//					//Display button buy
//					auto buttonBuy = ui::Button::create(SHOP_SCENE_BUY_BUTTON_FILEPATH);
//					buttonBuy->setPosition(Vec2(visibleSize.width / 2, (visibleSize.height - (MouseSkin->getContentSize().height) - 110)));
//					buttonBuy->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
//					{
//						switch (type)
//						{
//						case ui::Widget::TouchEventType::BEGAN:
//						{
//							if (checkbuy == false)
//							{
//								ShopScene::CountGold();
//							}
//							//check bought
//							auto defSkin = UserDefault::sharedUserDefault();
//							defSkin->setIntegerForKey(CHECK_SKIN, 1); //items 1 bought
//							defSkin->flush();
//							//
//							defSkin->setIntegerForKey(CHECK_BUY, 1);
//							defSkin->flush();
//							//check bought by class Introduce
//							MainMenuScene::CheckShop(skin);
//							//
//							removeChildByTag(15);
//							//button bought
//							auto buttonBuyed = ui::Button::create(SHOP_SCENE_BOUGHT_BUTTON_FILEPATH);
//							buttonBuyed->setPosition(Vec2(visibleSize.width / 2, (visibleSize.height - (MouseSkin->getContentSize().height) - 110)));
//							addChild(buttonBuyed, 2);
//							break;
//						}
//
//						case ui::Widget::TouchEventType::ENDED:
//						{
//
//							break;
//						}
//						default:
//							break;
//						}
//					});
//					addChild(buttonBuy, 2, 15);
//					break;
//				}
//			}
//			else
//			{
//				auto defSkin = UserDefault::sharedUserDefault();
//				defSkin->setIntegerForKey(CHECK_SKIN, 1); //items 1 buyed
//				defSkin->flush();
//				int skin = defSkin->getIntegerForKey(CHECK_SKIN);
//				MainMenuScene::CheckShop(skin);
//				removeChildByTag(15);
//				auto buttonBuyed = ui::Button::create(SHOP_SCENE_BOUGHT_BUTTON_FILEPATH);
//				buttonBuyed->setPosition(Vec2(visibleSize.width / 2, (visibleSize.height - (MouseSkin->getContentSize().height) - 110)));
//				addChild(buttonBuyed, 2);
//
//			}
//			break;
//		}
//		case ui::Widget::TouchEventType::ENDED:
//			break;
//		default:
//			break;
//		}
//	});
//	addChild(buttonMouseSkin, 2);
//}
void ShopScene::CheckBuyItem(int a)
{
	auto defSkin = UserDefault::sharedUserDefault();
	defSkin->setIntegerForKey(CHECK_SKIN, 0); //items 0 selected
	defSkin->setIntegerForKey(CHECK_BUY, 0); //items 0 selected
	defSkin->flush();
}
void ShopScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_BACK)
	{
		Director::getInstance()->end();
	}
}