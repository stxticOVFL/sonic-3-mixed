#ifndef ORBINAUT_H
#define ORBINAUT_H

class Orbinaut;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class Orbinaut: public Enemy {
public:    
    
    Object* Orbs[4];
    float OrbOffsets[4];
    float RotAngle;
    float TurnSpeed;
    
    void Create();
    int OnHit();
    void Update();
    void Render(int CamX, int CamY);
};

#endif /* ORBINAUT_H */
