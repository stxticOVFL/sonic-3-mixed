#ifndef BUGGERNAUT_H
#define BUGGERNAUT_H

class Buggernaut;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class Buggernaut: public Enemy {
public:    
    
    int Flip;
    int Routine;
    int TimerRoutine;
    int MaximumSpeed;
    int Acceleration;
    int SubX;
    int SubY;
    int ChildSubX;
    int ChildSubY;
    int ChildXSpeed;
    int ChildYSpeed;
    int ChildFlip;
    
    void Create();
    int OnHit();
    void Update();
    void Render(int CamX, int CamY);
};

#endif /* BUGGERNAUT_H */
