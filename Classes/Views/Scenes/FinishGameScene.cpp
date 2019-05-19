#include "FinishGameScene.h"
#include "GameManager/Definitions.h"
#include "ui/UIButton.h"
#include "MainGameScene.h"
#include "AudioEngine.h"
#include "ui/UICheckBox.h"
#include "MainMenuScene.h"
#include "ShopScene.h"
#include "2d/CCRenderTexture.h"
USING_NS_CC;
using namespace experimental;
using namespace cocos2d::ui;

//
int m_score;
int m_highscore;
int m_gold;
int m_touchitems;
int m_skinend;
//Platform Android
#if(CC_TARGET_PLATFORM== CC_PLATFORM_ANDROID)
#include"jni.h"
extern "C"
{
	JNIEXPORT jint JNICALL Java_org_cocos2dx_cpp_AppActivity_awesomeCppFunction(JNIEnv* env, jobject thiz);
};


JNIEXPORT jint JNICALL Java_org_cocos2dx_cpp_AppActivity_awesomeCppFunction(JNIEnv* env, jobject thiz)
{
	return m_score;
}
#endif
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//lib
#include"jni.h"
#include"platform\android\jni\JniHelper.h" 
//function
static void showAdAndroid()
{


	JniMethodInfo methodInfo;
	if (!cocos2d::JniHelper::getStaticMethodInfo(methodInfo,
		"org/cocos2dx/cpp/AppActivity", "showAd",
		"()V")) {
		return;
	}
	methodInfo.env->CallStaticVoidMethod(methodInfo.classID,
		methodInfo.methodID);
	methodInfo.env->DeleteLocalRef(methodInfo.classID);

}
static void hideAdAndroid()
{


	JniMethodInfo methodInfo;
	if (!cocos2d::JniHelper::getStaticMethodInfo(methodInfo,
		"org/cocos2dx/cpp/AppActivity", "hideAd",
		"()V")) {
		return;
	}
	methodInfo.env->CallStaticVoidMethod(methodInfo.classID,
		methodInfo.methodID);
	methodInfo.env->DeleteLocalRef(methodInfo.classID);

}
static void showAdAndroidInter()
{

	JniMethodInfo methodInfo;
	if (!cocos2d::JniHelper::getStaticMethodInfo(methodInfo,
		"org/cocos2dx/cpp/AppActivity", "showAdInter",
		"()V")) {
		return;
	}
	methodInfo.env->CallStaticVoidMethod(methodInfo.classID,
		methodInfo.methodID);
	methodInfo.env->DeleteLocalRef(methodInfo.classID);

}
static void shareFacebook()
{

	JniMethodInfo methodInfo;
	if (!cocos2d::JniHelper::getStaticMethodInfo(methodInfo,
		"org/cocos2dx/cpp/AppActivity", "loginFB",
		"()V")) {
		return;
	}
	methodInfo.env->CallStaticVoidMethod(methodInfo.classID,
		methodInfo.methodID);
	methodInfo.env->DeleteLocalRef(methodInfo.classID);

}
static void takeScreen()
{

	JniMethodInfo methodInfo;
	if (!cocos2d::JniHelper::getStaticMethodInfo(methodInfo,
		"org/cocos2dx/cpp/AppActivity", "getTakeScreenShot",
		"()V")) {
		return;
	}
	methodInfo.env->CallStaticVoidMethod(methodInfo.classID,
		methodInfo.methodID);
	methodInfo.env->DeleteLocalRef(methodInfo.classID);

}
//check internet
bool FinishGameScene::isInternetConnected()
{

	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/AppActivity", "isConnected", "()Z")) {
		jboolean result = t.env->CallStaticBooleanMethod(t.classID, t.methodID);
		if (result == JNI_TRUE) {
			return true;
		}
		else {
			return false;
		}
	}
	return false;

}
#endif

//Game Core
Scene* FinishGameScene::createScene(int score, int highscore, int gold, int touchitems, int skin)
{
	m_score = score;
	m_highscore = highscore;
	m_gold = gold;
	m_touchitems = touchitems;
	m_skinend = skin;
	return FinishGameScene::create();
}

// on "init" you need to initialize your instance
bool FinishGameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
	//show ad android
	
	#if(CC_TARGET_PLATFORM== CC_PLATFORM_ANDROID)
		showAdAndroid();
	#endif

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
	//add scene
	int lang = MainMenuScene::CheckLanguage();
	if (lang == 0) // en
	{
		sceneEnd = Sprite::create(FINISH_GAME_SCENE_BACKGROUND_FILEPATH);
	}
	else
	{
		sceneEnd = Sprite::create("VnEndGame.png");
	}
	sceneEnd->setAnchorPoint(Vec2(0, 0));
	sceneEnd->setPosition(Vec2(0, 0));
	this->addChild(sceneEnd,0);
	//Display new best score
	if (m_score > m_highscore)
	{
		auto NewBestScore = Sprite::create(FINISH_GAME_SCENE_NEWBEST_FILEPATH);
		NewBestScore->setAnchorPoint(Vec2(00.5, 0));
		NewBestScore->setPosition(Vec2(visibleSize.width / 2 + 80, visibleSize.height * 0.60));
		this->addChild(NewBestScore);
	}
	//add scored
	String *score = String::createWithFormat("%i", m_score);
	label = Label::createWithTTF(score->getCString(), MAIN_GAME_SCENE_FONT_FILEPATH, visibleSize.height * 0.1);
	label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.68));
	label->setColor(Color3B::WHITE);
	addChild(label, 1);
	//add bestscored
	String *highscore = String::createWithFormat("%i", m_highscore);
	labelhighScore = Label::createWithTTF(highscore->getCString(), MAIN_GAME_SCENE_FONT_FILEPATH, visibleSize.height * 0.05);
	labelhighScore->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.58));
	labelhighScore->setColor(Color3B::WHITE);
	addChild(labelhighScore, 1);
	//add gold
	String *gold = String::createWithFormat("%i", m_gold);
	labelGold = Label::createWithTTF(gold->getCString(), MAIN_GAME_SCENE_FONT_FILEPATH, visibleSize.height * 0.05);
	labelGold->setAlignment(TextHAlignment::LEFT);
	labelGold->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.50));
	labelGold->setColor(Color3B::WHITE);
	addChild(labelGold, 1);
	

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//Continue
	if (isInternetConnected() == true)
	{
		int lang = MainMenuScene::CheckLanguage();
		if (lang == 0) // en
		{
			buttonContinue = ui::Button::create("BTContinute.png");
		}
		else
		{
			buttonContinue = ui::Button::create("VnBTContinute.png");
		}
		
		buttonContinue->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2.4));
		buttonContinue->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
		{
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
			{
				flagContinue = false;
				//hide ad android
				#if(CC_TARGET_PLATFORM== CC_PLATFORM_ANDROID)
					hideAdAndroid();
					
				#endif
				//show ad android
				#if(CC_TARGET_PLATFORM== CC_PLATFORM_ANDROID)
					showAdAndroidInter();
				#endif
				auto inGameAgain = MainGameScene::createScene(m_touchitems, m_skinend, true);
				Director::getInstance()->replaceScene(inGameAgain);
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
		addChild(buttonContinue, 1, 9);
	}
	//btnShareFB
	ButtonShareFacebook();
#endif
	//Button replay
	ButtonReplay();
	//button back
	ButtonBack();
	//btnShop
	ButtonShop();	
	//back button in android
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = CC_CALLBACK_2(FinishGameScene::onKeyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    return true;
}
void FinishGameScene::ButtonReplay()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto buttonReplay = ui::Button::create(FINISH_GAME_SCENE_REPLAY_BUTTON_FILEPATH);
	buttonReplay->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 3.6));
	buttonReplay->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
		{
			auto inGameAgain = MainGameScene::createScene(m_touchitems, m_skinend, false);
			TransitionFade *transition = TransitionFade::create(SCENE_TRANSITION_TIME, inGameAgain);
			Director::getInstance()->replaceScene(transition);
			//hide ad android
			#if(CC_TARGET_PLATFORM== CC_PLATFORM_ANDROID)
			hideAdAndroid();
			#endif
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
	addChild(buttonReplay, 1);
}
void FinishGameScene::ButtonBack() 
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto buttonBack = ui::Button::create(FINISH_GAME_SCENE_BACK_BUTTON_FILEPATH);
	//buttonBack->setPosition(Vec2(visibleSize.width / 2 - 30, (visibleSize.height / 3.5 - (ui::Button::create("BTReplay.png")->getContentSize().height))));
	buttonBack->setPosition(Vec2(visibleSize.width / 2.3 - Button::create("BTChoose.png")->getContentSize().width, (visibleSize.height / 3.5 - (ui::Button::create("BTReplay.png")->getContentSize().height))));
	
	buttonBack->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
		{
			break;
		}
		case ui::Widget::TouchEventType::ENDED:
		{
			auto menuGame = MainMenuScene::createScene();
			TransitionFade *transition = TransitionFade::create(SCENE_TRANSITION_TIME, menuGame);
			Director::getInstance()->replaceScene(transition);
			//hide ad android
			#if(CC_TARGET_PLATFORM== CC_PLATFORM_ANDROID)
				hideAdAndroid();
			#endif
			break;
		}

		default:
			break;
		}
	});
	addChild(buttonBack, 1);
}
void FinishGameScene::ButtonShop()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto buttonShop = ui::Button::create(MAIN_MENU_SCENE_SHOP_BUTTON_FILEPATH);
	buttonShop->setPosition(Vec2(visibleSize.width / 2, (visibleSize.height / 3.5 - (ui::Button::create(FINISH_GAME_SCENE_REPLAY_BUTTON_FILEPATH)->getContentSize().height))));
	buttonShop->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
		{
			//getScreenPic();
			auto shop = ShopScene::createScene(m_gold, m_touchitems);
			TransitionFade *transition = TransitionFade::create(SCENE_TRANSITION_TIME, shop);
			Director::getInstance()->replaceScene(transition);
			//hide ad android
			#if(CC_TARGET_PLATFORM== CC_PLATFORM_ANDROID)
			hideAdAndroid();
			#endif
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
	addChild(buttonShop, 1);
}

void FinishGameScene::ButtonShareFacebook()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto buttonShareFB = ui::Button::create(FINISH_GAME_SCENE_SHAREFB_BUTTON_FILEPATH);
	buttonShareFB->setPosition(Vec2(visibleSize.width / 1.8 + Button::create(MAIN_MENU_SCENE_SOUND_BUTTON_FILEPATH)->getContentSize().width, (visibleSize.height / 3.5 - (ui::Button::create(FINISH_GAME_SCENE_REPLAY_BUTTON_FILEPATH)->getContentSize().height))));
	buttonShareFB->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
		{
			
			#if(CC_TARGET_PLATFORM== CC_PLATFORM_ANDROID)
				//hideAdAndroid();
			if (isInternetConnected() == true)
			{
				shareFacebook();
			}
			else
			{
				
			}
			#endif
			
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
	addChild(buttonShareFB, 1);
}
void FinishGameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_BACK)
	{
		Director::getInstance()->end();
	}
}
