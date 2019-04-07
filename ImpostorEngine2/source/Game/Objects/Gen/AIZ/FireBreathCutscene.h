#ifndef FIREBREATHCUTSCENE_H
#define FIREBREATHCUTSCENE_H

class FireBreathCutscene;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class FireBreathCutscene: public Enemy {
public:    
    enum BossState {
        WAIT = 3,
        WAITING_FOR_PLAYER = 0,
        EMERGE_FROM_WATER = 1,
        WAIT_NO_MOVE = 4,
        WATER_DRY = 2,
        SHIFT_CAMERA = 5,
    };
    enum BossAction {
        START_MOVING = 5,
        START_FIGHT = 0,
        SOMEKINDAWAIT = 1,
        WAIT_LONG = 2,
        STOP_AND_EMERGE = 6,
        WAIT_SHORT = 3,
        HIDE_BEHIND = 4,
    };
    
    int TimerAction;
    int InvulnTimer;
    int ExplosionTimer;
    int State;
    Uint32 MainPalette[16];
    Uint32 HurtPalette[16];
    int SmallX;
    int SmallerX;
    int SmallestX;
    bool OpenHatch;
    int OpenHatchTimer;
    bool Cutscene;
    int Shot1;
    int Shot2;
    int Shot3;
    
    CONSTRUCTER FireBreathCutscene();
    void Create();
    int OnHit();
    void DoExplosionDebris();
    void HandleDamage();
    void Update();
    void Render(int CamX, int CamY);
};

#endif /* FIREBREATHCUTSCENE_H */
