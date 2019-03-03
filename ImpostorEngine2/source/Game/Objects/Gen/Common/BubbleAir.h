#ifndef BUBBLEAIR_H
#define BUBBLEAIR_H

class BubbleAir;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class BubbleAir: public Object {
public:    
    
    
    void Create();
    void Update();
    void OnAnimationFinish();
    int OnLeaveScreen();
    void Render(int CamX, int CamY);
    int OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data);
};

#endif /* BUBBLEAIR_H */
