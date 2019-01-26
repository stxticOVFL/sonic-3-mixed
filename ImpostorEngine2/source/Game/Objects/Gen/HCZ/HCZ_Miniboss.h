#ifndef HCZ_MINIBOSS_H
#define HCZ_MINIBOSS_H

class HCZ_Miniboss;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class HCZ_Miniboss: public Enemy {
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

#endif /* HCZ_MINIBOSS_H */
