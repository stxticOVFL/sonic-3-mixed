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
    
    Uint32 OrbXPos[4];
    Uint32 OrbYPos[4];
    float OrbOffsets[4];
    float RotAngle;
    float TurnSpeed;
    int i;
    
    void Create();
    void Update();
    void Render(int CamX, int CamY);
};

#endif /* ORBINAUT_H */
