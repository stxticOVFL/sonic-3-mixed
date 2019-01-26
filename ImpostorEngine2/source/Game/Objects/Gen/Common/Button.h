#ifndef BUTTON_H
#define BUTTON_H

class Button;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class Button: public Object {
public:    
    
    bool Permanent;
    int TriggerID;
    bool TriggerType;
    bool CollisionType;
    int StartY;
    int CurrentAnimation;
    int Down;
    int Pressed;
    
    void Create();
    void Update();
    void Render(int CamX, int CamY);
    int OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data);
};

#endif /* BUTTON_H */
