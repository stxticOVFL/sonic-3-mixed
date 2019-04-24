#ifndef ICZSWINGINGPLATFORM_H
#define ICZSWINGINGPLATFORM_H

class ICZSwingingPlatform;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class ICZSwingingPlatform: public Object {
public:    
    
    int RingAnimation;
    bool Break;
    Object* Trigger;
    int VisualCircle;
    int Pivot;
    IPlayer* Player;
    
    void Create();
    void Update();
    void Render(int CamX, int CamY);
    int OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data);
};

#endif /* ICZSWINGINGPLATFORM_H */
