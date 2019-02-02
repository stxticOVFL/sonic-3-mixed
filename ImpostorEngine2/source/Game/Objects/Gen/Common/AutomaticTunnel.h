#ifndef AUTOMATICTUNNEL_H
#define AUTOMATICTUNNEL_H

class AutomaticTunnel;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class AutomaticTunnel: public Object {
public:    
    
    int PlayersGrabbed;
    int PlayerTimers[8];
    int PlayerIndex[8];
    int PlayerPathSize[8];
    int PathID;
    bool Reverse;
    bool Launch;
    Sint16 AutoTunnel_Data[0x1D];
    
    void Create();
    void Update();
    void Render(int CamX, int CamY);
    int OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data);
};

#endif /* AUTOMATICTUNNEL_H */
