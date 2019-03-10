#ifndef MEGACHOMPER_H
#define MEGACHOMPER_H

class MegaChomper;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class MegaChomper: public Enemy {
public:    
    
    int Flip;
    int Routine;
    int MaximumSpeed;
    int Acceleration;
    int SubX;
    int SubY;
    int StuckX;
    int LRTimer;
    int LRAmount;
    int LastFlip;
    
    void Create();
    int OnHit();
    void Update();
    void Render(int CamX, int CamY);
};

#endif /* MEGACHOMPER_H */
