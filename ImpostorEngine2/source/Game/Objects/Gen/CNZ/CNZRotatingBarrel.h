#ifndef CNZROTATINGBARREL_H
#define CNZROTATINGBARREL_H

class CNZRotatingBarrel;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class CNZRotatingBarrel: public Object {
public:    
    
    int16_t YSubtypeVelocity;
    int16_t PositionOffset;
    
    void Create();
    void Update();
    void Render(int CamX, int CamY);
    int OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data);
};

#endif /* CNZROTATINGBARREL_H */
