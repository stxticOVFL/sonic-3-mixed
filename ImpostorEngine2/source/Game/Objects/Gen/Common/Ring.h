#ifndef RING_H
#define RING_H

class Ring;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class Ring: public Object {
public:    
    
    uint32_t MyX;
    uint32_t MyY;
    int CurrentFrame;
    int MagnetizedTo;
    bool ShouldRingFall;
    
    CONSTRUCTER Ring();
    void Create();
    void Update();
    void Render(int CamX, int CamY);
    int OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data);
};

#endif /* RING_H */
