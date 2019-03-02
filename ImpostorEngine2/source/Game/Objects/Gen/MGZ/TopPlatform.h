#ifndef TOPPLATFORM_H
#define TOPPLATFORM_H

class TopPlatform;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class TopPlatform: public Object {
public:    
    
    bool InUse;
    int PlayerUsed;
    float XFriction;
    IPlayer* Player;
    bool AlreadyUsed;
    int FrameSpeed;
    
    void Create();
    void Update();
    void MoveSprite();
    void Render(int CamX, int CamY);
    int OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data);
};

#endif /* TOPPLATFORM_H */
