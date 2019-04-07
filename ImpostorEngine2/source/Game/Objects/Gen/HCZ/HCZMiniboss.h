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
    enum BossState {
        SPINNING_WATER = 3,
        ENTERING = 0,
        DEAD = 5,
        MOVING = 1,
        SLOWING_DOWN = 2,
        SPEEDING_UP = 4,
    };
    
    int TimerSpin;
    int SpinSpeed;
    int RocketTurn;
    int RocketSpeed;
    int InvulnTimer;
    bool Started;
    int ExplosionTimer;
    Uint32 MainPalette[16];
    Uint32 MainPaletteWater[16];
    Uint32 HurtPalette[16];
    int IdlePosY;
    int PillarX;
    int PillarY;
    int State;
    
    void Create();
    int OnHit();
    void HandleDamage();
    void Update();
    void DrawRocket(int Rock, int Ang, int Flip, int Side, int CamX, int CamY);
    void Render(int CamX, int CamY);
    void WallSlide();
    void SpinWater();
};

#endif /* HCZMINIBOSS_H */
