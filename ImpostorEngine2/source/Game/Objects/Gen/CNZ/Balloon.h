#ifndef BALLOON_H
#define BALLOON_H

class Balloon;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class Balloon: public Object {
public:    
    
    int Color;
    bool CreateBubble;
    bool Popped;
    
    void Create();
    void Update();
    void OnAnimationFinish();
    int OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data);
};

#endif /* BALLOON_H */
