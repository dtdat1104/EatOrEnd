#include "MainGameScene.h"
#include "GameManager/Definitions.h"
#include "AudioEngine.h"
#include "ui/UIButton.h"
#include "MainMenuScene.h"
#include "FinishGameScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace experimental;
using namespace cocos2d::ui;

const char *HIGH_SCORE = "key"; // highscore save in system
const char *GOLD = "keygold";
const char *TEMSCORE = "keyscore";

int m_touchItems; //temp sound item
int m_skin;
bool m_flagContinue;
Scene* MainGameScene::createScene(int touchItems, int skin,bool flagContinue)
{
	//
	m_touchItems = touchItems;
	m_skin = skin;
	m_flagContinue = flagContinue;
	//create scene with physics
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
	auto layer = MainGameScene::create();
	layer->setPhysicWorld(scene->getPhysicsWorld());
	scene->addChild(layer);
	return scene;
}
// on "init" you need to initialize your instance
bool MainGameScene::init()
{
	
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	/*Set Physics on game*/
	auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 0);
	edgeBody->setCollisionBitmask(1);
	edgeBody->setContactTestBitmask(true);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	edgeNode->setPhysicsBody(edgeBody);
	addChild(edgeNode);

	/*Background*/
	background1 = Sprite::create(MAIN_GAME_SCENE_BACKGROUND_FILEPATH);
	background1->setAnchorPoint(Vec2(0, 0));
	background1->setPosition(Vec2(origin.x, origin.y));

	background2 = Sprite::create(MAIN_GAME_SCENE_BACKGROUND_FILEPATH);
	background2->setAnchorPoint(Vec2(0, 0));
	background2->setPosition(Vec2(origin.x, origin.y + background2->getContentSize().height));
	addChild(background1, -6);
	addChild(background2, -6);
	
	//add mouse
	if (m_skin == 0) // default mouse
	{
		Mouse = Sprite::create(MAIN_GAME_SCENE_MOUSE_ITEM_DEFAULT_FILEPATH);
		Mouse->setAnchorPoint(Vec2(0.5, 0));
		Mouse->setPosition(Vec2(visibleSize.width / 2, 5));
		//auto MouseLeftPhysic = PhysicsBody::createBox(Mouse->getContentSize());
		auto MouseLeftPhysic = PhysicsBody::createCircle(Mouse->getContentSize().width /2, PHYSICSBODY_MATERIAL_DEFAULT);
		MouseLeftPhysic->setDynamic(false);
		MouseLeftPhysic->setCollisionBitmask(2);// Set name
		MouseLeftPhysic->setContactTestBitmask(true);//Allow collision
		Mouse->setPhysicsBody(MouseLeftPhysic);
		addChild(Mouse);
	}
	else
	{
		Mouse = Sprite::create(MAIN_GAME_SCENE_MOUSE_ITEM_FIRST_FILEPATH);
		Mouse->setAnchorPoint(Vec2(0.5, 0));
		Mouse->setPosition(Vec2(visibleSize.width / 2, 5));
		//auto MouseLeftPhysic = PhysicsBody::createBox(Mouse->getContentSize());
		auto MouseLeftPhysic = PhysicsBody::createCircle(Mouse->getContentSize().width / 2, PHYSICSBODY_MATERIAL_DEFAULT);
		MouseLeftPhysic->setDynamic(false);
		MouseLeftPhysic->setCollisionBitmask(2);// Set name
		MouseLeftPhysic->setContactTestBitmask(true);//Allow collision
		Mouse->setPhysicsBody(MouseLeftPhysic);
		addChild(Mouse);
	}

	/*Coin*/
	auto coinDisplay = ui::Button::create(MAIN_GAME_SCENE_COIN_BUTTON_FILEPATH);
	coinDisplay->setPosition(Vec2(visibleSize.width *0.9, visibleSize.height*0.95));
	addChild(coinDisplay, 2);
	/*Best*/
	auto bestnDisplay = ui::Button::create(MAIN_GAME_SCENE_RATE_BUTTON_FILEPATH);
	bestnDisplay->setPosition(Vec2(visibleSize.width *0.08, visibleSize.height*0.95));
	addChild(bestnDisplay, 2);
	/*Event */
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(MainGameScene::onTouchBegan, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(MainGameScene::OnContactBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
	//set level	
	this->schedule(schedule_selector(MainGameScene::SwingMouse), swingtime);
	this->schedule(schedule_selector(MainGameScene::CreateItems), itemtime);
	this->schedule(schedule_selector(MainGameScene::CreateGold), 6);
	//
	MainGameScene::LabelFunction();
	//Create Gold
	this->scheduleUpdate();
	//
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = CC_CALLBACK_2(MainGameScene::onKeyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    return true;
}
void MainGameScene::CheckGoldShop(int a)
{
	auto defGold = UserDefault::sharedUserDefault();
	defGold->setIntegerForKey(GOLD, a);
	defGold->flush();
}
void MainGameScene::CheckHighScore(int a)
{
	auto defHigh = UserDefault::sharedUserDefault();
	defHigh->setIntegerForKey(HIGH_SCORE, a);
	defHigh->flush();
}
void MainGameScene::LabelFunction()
{
	/*Label Scrore*/
	if (m_flagContinue == true)
	{
		auto def = UserDefault::sharedUserDefault();
		score = def->getIntegerForKey(TEMSCORE);
		String *teamscore = String::createWithFormat("%i", score);
		label = Label::createWithTTF(teamscore->getCString(), MAIN_GAME_SCENE_FONT_FILEPATH, visibleSize.height * 0.1);
		label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.85));
		label->setColor(Color3B::WHITE);
		addChild(label, 5);
	}
	else
	{
		String *teamscore = String::createWithFormat("%i", score);
		label = Label::createWithTTF(teamscore->getCString(), MAIN_GAME_SCENE_FONT_FILEPATH, visibleSize.height * 0.1);
		label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.85));
		label->setColor(Color3B::WHITE);
		addChild(label, 5);
	}
	/*HighScore*/
	auto def = UserDefault::sharedUserDefault();
	iHighScore = def->getIntegerForKey(HIGH_SCORE);
	String *highScore = String::createWithFormat("%i", iHighScore);
	labelhighScore = Label::createWithTTF(highScore->getCString(), MAIN_GAME_SCENE_FONT_FILEPATH, visibleSize.height * 0.05,Size::ZERO,TextHAlignment::LEFT);
	labelhighScore->setPosition(Vec2(visibleSize.width * 0.08 + 35, visibleSize.height*0.94));
	labelhighScore->setColor(Color3B::WHITE);
	addChild(labelhighScore, 5);
	/*Gold*/
	auto defGold = UserDefault::sharedUserDefault();
	iGold = defGold->getIntegerForKey(GOLD);
	String *gold = String::createWithFormat("%i", iGold);
	labelGold = Label::createWithTTF(gold->getCString(), MAIN_GAME_SCENE_FONT_FILEPATH, visibleSize.height * 0.05, Size::ZERO,TextHAlignment::RIGHT);
	labelGold->setAnchorPoint(Vec2(0.5, 0.5));
	labelGold->setPosition(Vec2(visibleSize.width * 0.78, visibleSize.height*0.94));
	labelGold->setColor(Color3B::WHITE);
	addChild(labelGold, 5);
	countGold = iGold;
}
bool MainGameScene::OnContactBegan(cocos2d::PhysicsContact &contact)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto a = contact.getShapeA()->getBody();
	auto b = contact.getShapeB()->getBody();
	//Mouse 2 - --3
	if (a->getCollisionBitmask() == 2 && b->getCollisionBitmask() == 3)
	{
		++score;
		String * teamscore = String::createWithFormat("%i", score);
		label->setString(teamscore->getCString());
		//audio when mouse eat
		if (m_touchItems == 1)
		{
			AudioEngine::play2d(MAIN_GAME_SCENE_EAT_SOUND_FILEPATH);
		}
		tempScore = Label::createWithTTF("+1", MAIN_GAME_SCENE_FONT_FILEPATH, visibleSize.height * 0.03);
		tempScore->setPosition(Vec2(b->getPosition().x, b->getPosition().y));
		tempScore->setColor(Color3B::WHITE);
		addChild(tempScore, 5);

		//Exit
		removeChild(b->getNode(), true);

	}
	else if (a->getCollisionBitmask() == 3 && b->getCollisionBitmask() == 2)
	{
		++score;
		String * teamscore = String::createWithFormat("%i", score);
		label->setString(teamscore->getCString());
		//audio when mouse eat
		if (m_touchItems == 1)
		{
			AudioEngine::play2d(MAIN_GAME_SCENE_EAT_SOUND_FILEPATH);
		}
		//Display +1 when eat 
		tempScore = Label::createWithTTF("+1", MAIN_GAME_SCENE_FONT_FILEPATH, visibleSize.height * 0.03);
		tempScore->setPosition(Vec2(a->getPosition().x, a->getPosition().y));
		tempScore->setColor(Color3B::WHITE);
		addChild(tempScore, 5);
		//Exit
		removeChild(a->getNode(), true); 
	}
	else if (a->getCollisionBitmask() == 4 && b->getCollisionBitmask() == 2)
	{
		//temp score
		auto deftemp = UserDefault::sharedUserDefault();
		deftemp->setIntegerForKey(TEMSCORE, score);
		deftemp->flush();
		//high score
		auto def = UserDefault::sharedUserDefault();
		iHighScore = def->getIntegerForKey(HIGH_SCORE);
		if (score > iHighScore)
		{
			def->setIntegerForKey(HIGH_SCORE, score);
			def->flush();
			String *highScore = String::createWithFormat("%i", iHighScore);
			labelhighScore->setString(highScore->getCString());
		}
		if (m_touchItems == 1)
		{
			AudioEngine::play2d(MAIN_GAME_SCENE_DIE_SOUND_FILEPATH);
		}
		//
		auto defGold = UserDefault::sharedUserDefault();
		iGold = defGold->getIntegerForKey(GOLD);
		//call class endgame
		auto EndGame = FinishGameScene::createScene(score, iHighScore, iGold, m_touchItems, m_skin);
		Director::getInstance()->replaceScene(EndGame);
	}
	//die - 4
	else if (a->getCollisionBitmask() == 2 && b->getCollisionBitmask() == 4)
	{
		//temp score
		auto deftemp = UserDefault::sharedUserDefault();
		deftemp->setIntegerForKey(TEMSCORE, score);
		deftemp->flush();
		//high score
		auto def = UserDefault::sharedUserDefault();
		iHighScore = def->getIntegerForKey(HIGH_SCORE);
		if (score > iHighScore)
		{
			def->setIntegerForKey(HIGH_SCORE, score);
			def->flush();
			String *highScore = String::createWithFormat("%i", iHighScore);
			labelhighScore->setString(highScore->getCString());
		}
		if (m_touchItems == 1)
		{
			AudioEngine::play2d(MAIN_GAME_SCENE_DIE_SOUND_FILEPATH);
		}
		//
		auto defGold = UserDefault::sharedUserDefault();
		iGold = defGold->getIntegerForKey(GOLD);

		auto EndGame = FinishGameScene::createScene(score, iHighScore, iGold, m_touchItems, m_skin);
		Director::getInstance()->replaceScene(EndGame);
	}
	//gold - 5
	else if (a->getCollisionBitmask() == 2 && b->getCollisionBitmask() == 5)
	{
		countGold++;
		String *gold = String::createWithFormat("%i", countGold);
		labelGold->setString(gold->getCString());
		//
		auto defGold = UserDefault::sharedUserDefault();
		defGold->setIntegerForKey(GOLD, countGold);
		//defGold->setIntegerForKey(GOLD, 10);
		defGold->flush();

		if (m_touchItems == 1)
		{
			AudioEngine::play2d(MAIN_GAME_SCENE_EAT_GOLD_SOUND_FILEPATH);
		}
		//CheckGold
		iGold = defGold->getIntegerForKey(GOLD);
		MainMenuScene::CheckGold(iGold);

		removeChild(b->getNode(), true);
	}
	else if (a->getCollisionBitmask() == 5 && b->getCollisionBitmask() == 2)
	{
		countGold++;
		String *gold = String::createWithFormat("%i", countGold);
		labelGold->setString(gold->getCString());
		//
		auto defGold = UserDefault::sharedUserDefault();
		iGold = defGold->getIntegerForKey(GOLD);
		defGold->setIntegerForKey(GOLD, countGold);
		//defGold->setIntegerForKey(GOLD, 10);
		defGold->flush();
		if (m_touchItems == 1)
		{
			AudioEngine::play2d(MAIN_GAME_SCENE_EAT_GOLD_SOUND_FILEPATH);
		}
		//CheckGold
		iGold = defGold->getIntegerForKey(GOLD);
		MainMenuScene::CheckGold(iGold);
		removeChild(a->getNode(), true);
	}
	//
	if (a->getCollisionBitmask() == 3 && b->getCollisionBitmask() == 1  && a->getPosition().y < 200)
	{
		CCLOG("Da nho hon man hinh");
		removeChild(a->getNode(), true);
	}
	else if (b->getCollisionBitmask() == 3 && a->getCollisionBitmask() == 1 && b->getPosition().y < 200)
	{
		CCLOG("Da nho hon man hinh");
		removeChild(b->getNode(), true);
	}
	else if (a->getCollisionBitmask() == 4 && b->getCollisionBitmask() == 1 && a->getPosition().y < 200)
	{
		CCLOG("Da nho hon man hinh");
		removeChild(a->getNode(), true);
	}
	else if (b->getCollisionBitmask() == 4 && a->getCollisionBitmask() == 1 && b->getPosition().y < 200)
	{
		CCLOG("Da nho hon man hinh");
		removeChild(b->getNode(), true);
	}
	else if (a->getCollisionBitmask() == 5 && b->getCollisionBitmask() == 1 && a->getPosition().y < 200)
	{
		CCLOG("Da nho hon man hinh");
		removeChild(a->getNode(), true);
	}
	else if (b->getCollisionBitmask() == 5 && a->getCollisionBitmask() == 1 && b->getPosition().y < 200)
	{
		CCLOG("Da nho hon man hinh");
		removeChild(b->getNode(), true);
	}
	return true;
}
//scrolling background
void MainGameScene::update(float)
{
	background1->setPositionY(background1->getPositionY() - (SCROLLING_BACKGROUND_SPEED*visibleSize.height));
	background2->setPositionY(background2->getPositionY() - (SCROLLING_BACKGROUND_SPEED*visibleSize.height));

	if (background1->getPositionY() <= -background1->getContentSize().height)
	{
		background1->setPositionY(background2->getPositionY() +
			background2->getContentSize().height);
	}
	if (background2->getPositionY() <= -background2->getContentSize().height)
	{
		background2->setPositionY(background1->getPositionY() +
			background1->getContentSize().height);
	}
}
void MainGameScene::CreateItems(float dt)
{
	/*Create Items*/
	auto corn = Sprite::create(MAIN_GAME_SCENE_CORN_ITEM_FILEPATH);
	auto pepper = Sprite::create(MAIN_GAME_SCENE_PEPPER_ITEM_FILEPATH);
	//Create Physics
	//auto cornPhysic = PhysicsBody::createBox(corn->getContentSize());
	auto cornPhysic = PhysicsBody::createCircle(corn->getContentSize().width / 2, PHYSICSBODY_MATERIAL_DEFAULT);
	cornPhysic->setDynamic(false);
	cornPhysic->setCollisionBitmask(3);// Set name
	cornPhysic->setContactTestBitmask(true);//Allows
	corn->setPhysicsBody(cornPhysic);

	auto pepperPhysic = PhysicsBody::createBox(pepper->getContentSize());
	pepperPhysic->setDynamic(false);
	pepperPhysic->setCollisionBitmask(4);// Set name
	pepperPhysic->setContactTestBitmask(true);//Allows
	pepper->setPhysicsBody(pepperPhysic);
	//random
	auto randomCorn = CCRANDOM_0_1();
	//Position corn and pepper
	auto cornPosition = (visibleSize.width * randomCorn) + (corn->getContentSize().height);
	if (cornPosition < visibleSize.width)
	{
		corn->setPosition(Vec2(cornPosition - 10, visibleSize.height + corn->getContentSize().height));
		pepper->setPosition(Vec2(cornPosition + 70, visibleSize.height + corn->getContentSize().height + 50));
	}
	else
	{
		corn->setPosition(Vec2(10, visibleSize.height + corn->getContentSize().height));
		pepper->setPosition(Vec2(80, visibleSize.height + corn->getContentSize().height + 50));
	}
	addChild(corn);
	addChild(pepper);

	//Move
	auto cornMove = MoveBy::create(0.02*visibleSize.height, Vec2(0, -visibleSize.height*1.5));
	auto pepperMove = MoveBy::create(0.02*visibleSize.height, Vec2(0, -visibleSize.height*1.5));

	corn->runAction(cornMove);
	pepper->runAction(pepperMove);

	//remove lable +1 when eat corn
	removeChild(tempScore);
}
void MainGameScene::CreateGold(float dt)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	auto gold = Sprite::create(MAIN_GAME_SCENE_GOLD_ITEM_FILEPATH);
	//auto goldPhysic = PhysicsBody::createBox(gold->getContentSize());
	auto goldPhysic = PhysicsBody::createCircle(gold->getContentSize().width / 2, PHYSICSBODY_MATERIAL_DEFAULT);
	goldPhysic->setDynamic(false);
	goldPhysic->setCollisionBitmask(5);// Set name
	goldPhysic->setContactTestBitmask(true);//Allows
	gold->setPhysicsBody(goldPhysic);
	//position gold
	int randomGold1 = random(1, 3);
	int randomGold2 = random(1, 4);
	auto goldPosition = (visibleSize.width * randomGold1 / (1 + randomGold2)) - (gold->getContentSize().height);

	gold->setPosition(Vec2(goldPosition, visibleSize.height + gold->getContentSize().height));

	addChild(gold);
	//
	auto goldMove = MoveBy::create(15, Vec2(0, -visibleSize.height*1.5));
	gold->runAction(goldMove);
}
void MainGameScene::SwingMouse(float dt)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	/*Action*/
	if (checkState == true)
	{
		auto actionMouseRight = RotateTo::create(0.5, 30);
		auto actionMouseAgain = RotateBy::create(0.5, -30);
		auto sequences = Sequence::create(actionMouseRight, actionMouseAgain, nullptr);
		Mouse->runAction(sequences);
		checkState = false;
		//CCLOG("%d", checkState);
	}
	else
	{
		auto actionMouseLeft = RotateTo::create(0.5, -30);
		auto actionMouseAgain = RotateBy::create(0.5, 30);
		auto sequences = Sequence::create(actionMouseLeft, actionMouseAgain, nullptr);
		Mouse->runAction(sequences);
		checkState = true;
		//CCLOG("%d", checkState);
	}
}
bool MainGameScene::onTouchBegan(Touch * touch, Event *unused_event)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 locationNow = Mouse->getPosition();
	if (checkState == false)
	{
		if (locationNow.x < visibleSize.width) //Don't allow 
		{
			Mouse->setPosition(locationNow.x + 15, 5);
		}
	}
	else
	{
		if (locationNow.x > 0) // Don't allow 
		{
			Mouse->setPosition(locationNow.x - 15, 5);
		}
	}
	return true;
}
void MainGameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_BACK)
	{
		Director::getInstance()->end();
	}
}

