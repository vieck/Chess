#include "GameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("MainScene.csb");
    addChild(rootNode);
    
    _TiledMap = (cocos2d::TMXTiledMap*) rootNode->getChildByTag(5);
    cocos2d::TMXLayer* board = _TiledMap->getLayer("board");
    cocos2d::TMXObjectGroup* gamefield = _TiledMap->getObjectGroup("gameplay");
    
    currentSprite = cocos2d::Sprite::create("whitepawn.png");
    currentSprite->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2 + board->getPositionX(), Director::getInstance()->getWinSize().height / 2 + board->getPositionY()));
    addChild(currentSprite, 2);
    
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(GameScene::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(GameScene::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(GameScene::onTouchesEnded, this);
    listener->onTouchesCancelled = CC_CALLBACK_2(GameScene::onTouchesEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

Point GameScene::touchToPoint(Touch * touch) {
    return Director::getInstance()->convertToGL(touch->getLocationInView());
}

bool GameScene::isTouchingSprite(Touch* touch) {
    return (currentSprite->getPosition().getDistance(touchToPoint(touch)) < 100.0f);
}

void GameScene::onTouchesBegin(const std::vector<Touch*>& touches, Event* event) {
    touchOffset = Point::ZERO;
    for (auto touch : touches) {
        if (touch && isTouchingSprite(touch)) {
            currentSprite->setPosition(touchToPoint(touch) + touchOffset);
        }
    }
}

void GameScene::onTouchesMoved(const std::vector<Touch*>& touches, Event* event) {
    for (auto touch : touches) {
        if (touch && touchOffset.x && touchOffset.y ) {
            currentSprite->setPosition(touchToPoint(touch) + touchOffset);
        }
    }
}

void GameScene::onTouchesEnded(const std::vector<Touch*>& touches, Event* event) {
    for (auto touch: touches) {
        if (touch && touchOffset.x && touchOffset.y) {
            currentSprite->setPosition(touchToPoint(touch) + touchOffset);
            currentSprite->stopAllActions();
            currentSprite->setScale(1.0f);
            
            currentSprite->runAction(Sequence::create(ScaleBy::create(0.125f, 1.111f), ScaleBy::create(0.125f, 0.9f) ,NULL));
        }
    }
}
