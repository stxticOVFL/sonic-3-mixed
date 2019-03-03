#ifndef MGZMINIBOSS_H
#define MGZMINIBOSS_H

class MGZMiniBoss;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class MGZMiniBoss: public Enemy {
public:    
    enum BossState {
        RISING = 1,
        IDLE = 0,
        DRILLING = 2,
        LOWERING = 3,
    };
    
    Uint32 MainPalette[16];
    Uint32 HurtPalette[16];
    int TimerAction;
    int InvulnTimer;
    int ExplosionTimer;
    int State;
    
    void Create();
    int OnHit();
    void DoExplosionDebris();
    void HandleDamage();
    void Update();
    void Render(int CamX, int CamY);
    int OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data);
};

#endif /* MGZMINIBOSS_H */
