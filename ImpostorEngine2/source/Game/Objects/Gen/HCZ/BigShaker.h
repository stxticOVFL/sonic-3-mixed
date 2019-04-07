#ifndef BIGSHAKER_H
#define BIGSHAKER_H

class BigShaker;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class BigShaker: public Enemy {
public:    
    enum BossState {
        SPINNING_WATER = 3,
        ENTERING = 0,
        MOVING = 1,
        SLOWING_DOWN = 2,
        SPEEDING_UP = 4,
    };
    
    int TimerSpin;
    int ActionTimer;
    int SpinSpeed;
    int RocketTurn;
    float RocketSpeed;
    int InvulnTimer;
    bool Started;
    int ExplosionTimer;
    Uint32 MainPalette[16];
    Uint32 MainPaletteWater[16];
    Uint32 HurtPalette[16];
    int IdlePosY;
    int PillarX;
    int PillarY;
    bool LeftWall;
    int WallStartPos;
    float PlayerGravity[7];
    bool PlayerMoveLeft[7];
    bool PlayerEntered;
    int SpinOffsets[7];
    int State;
    
    CONSTRUCTER BigShaker();
    void Create();
    void DoExplosionDebris();
    int OnHit();
    void HandleDamage();
    void Update();
    void DrawRocket(int Rock, int Ang, int Flip, int Side, int CamX, int CamY);
    void Render(int CamX, int CamY);
    void WallSlide();
    void SpinWater();
};

#endif /* BIGSHAKER_H */
