#ifndef SWINGINGPLATFORM_H
#define SWINGINGPLATFORM_H

class SwingingPlatform;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class SwingingPlatform: public Object {
public:    
    
    int RingAnimation;
    bool Break;
    Object* Trigger;
    int VisualCircle;
    int Pivot;
    IPlayer* Player;
    
    CONSTRUCTER SwingingPlatform();
    void Create();
    void Update();
    void Render(int CamX, int CamY);
    int OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data);
};

#endif /* SWINGINGPLATFORM_H */
