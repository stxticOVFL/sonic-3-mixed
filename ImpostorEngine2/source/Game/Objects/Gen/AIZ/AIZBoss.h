#ifndef AIZBOSS_H
#define AIZBOSS_H

class AIZBoss;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class AIZBoss: public Enemy {
public:    
    enum BossAction {
        STOP_AND_EMERGE = 6,
        START_MOVING = 5,
        WAIT_LONG = 2,
        HIDE_BEHIND = 4,
        WAIT_SHORT = 3,
        SOMEKINDAWAIT = 1,
        START_FIGHT = 0,
    };
    enum BossState {
        SHIFT_CAMERA = 5,
        WAIT_NO_MOVE = 4,
        WAIT = 3,
        WATER_DRY = 2,
        EMERGE_FROM_WATER = 1,
        WAITING_FOR_PLAYER = 0,
    };
    
    int TimerAction;
    int InvulnTimer;
    int ExplosionTimer;
    int State;
    Uint32 MainPalette[16];
    Uint32 HurtPalette[16];
    int ArmBackAngle;
    int ArmFrontAngle;
    bool BehindWaterFall;
    int EmergeFromWaterTimer;
    int DryTimer;
    Uint8 AniWaterSplashing[13];
    bool Visible;
    int TargetX;
    int TargetY;
    int TargetIndex;
    
    void Create();
    int OnHit();
    void DoExplosionDebris();
    void HandleDamage();
    void GetTargetPos();
    void Update();
    void Render(int CamX, int CamY);
};

#endif /* AIZBOSS_H */
