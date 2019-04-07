#ifndef DRILLMOBILE_H
#define DRILLMOBILE_H

class DrillMobile;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class DrillMobile: public Enemy {
public:    
    
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

#endif /* DRILLMOBILE_H */
