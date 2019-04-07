#ifndef SCREWMOBILE_H
#define SCREWMOBILE_H

class ScrewMobile;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class ScrewMobile: public Enemy {
public:    
    enum BossState {
        ENTERING = 0,
        MOVING = 1,
        SUCC_TIME = 3,
        DROPPING_CHARGE = 2,
    };
    
    int InvulnTimer;
    bool Started;
    int ExplosionTimer;
    Uint32 MainPalette[16];
    Uint32 HurtPalette[16];
    bool PlayerEntered;
    int PropellorAnim;
    int RackAnim;
    int PropellorFrame;
    int RackFrame;
    int State;
    
    CONSTRUCTER ScrewMobile();
    void Create();
    void DoExplosionDebris();
    int OnHit();
    void HandleDamage();
    void Update();
    void Render(int CamX, int CamY);
};

#endif /* SCREWMOBILE_H */
