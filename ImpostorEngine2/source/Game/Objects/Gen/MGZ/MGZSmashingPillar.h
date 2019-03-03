#ifndef MGZSMASHINGPILLAR_H
#define MGZSMASHINGPILLAR_H

class MGZSmashingPillar;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class MGZSmashingPillar: public Object {
public:    
    
    int OGY;
    bool Direction;
    int Timer;
    
    void Create();
    void Update();
    void Render(int CamX, int CamY);
    int OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data);
};

#endif /* MGZSMASHINGPILLAR_H */
