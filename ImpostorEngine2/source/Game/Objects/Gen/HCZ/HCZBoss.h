#ifndef HCZBOSS_H
#define HCZBOSS_H

class HCZBoss;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class HCZBoss: public Enemy {
public:    
    
    int InvulnTimer;
    bool Started;
    int ExplosionTimer;
    Uint32 MainPalette[16];
    Uint32 HurtPalette[16];
    
    void Create();
    int OnHit();
    void HandleDamage();
    void Update();
    void Render(int CamX, int CamY);
};

#endif /* HCZBOSS_H */
