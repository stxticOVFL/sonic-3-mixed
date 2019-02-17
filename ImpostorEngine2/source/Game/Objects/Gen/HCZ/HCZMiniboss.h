#ifndef HCZMINIBOSS_H
#define HCZMINIBOSS_H

class HCZMiniboss;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class HCZMiniboss: public Enemy {
public:    
    
    int TimerSpin;
    int SpinSpeed;
    int RocketTurn;
    int InvulnTimer;
    bool Started;
    int ExplosionTimer;
    
    void Create();
    int OnHit();
    void Update();
    void DrawRocket(int Rock, int Ang, int Flip, int Side, int CamX, int CamY);
    void Render(int CamX, int CamY);
};

#endif /* HCZMINIBOSS_H */
