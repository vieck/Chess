#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
using namespace cocos2d;

class GameScene : public cocos2d::Layer
{
private:
    cocos2d::TMXTiledMap * _TiledMap;
    
    Sprite* currentSprite;
    
    Point touchOffset;
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    Point touchToPoint(Touch* touch);
    
    bool isTouchingSprite(Touch* touch);
    
    void onTouchesBegin(const std::vector<Touch*>& touches, Event* event);
    void onTouchesMoved(const std::vector<Touch*>& touches, Event* event);
    void onTouchesEnded(const std::vector<Touch*>& touches, Event* event);

    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
};

#endif // __HELLOWORLD_SCENE_H__
