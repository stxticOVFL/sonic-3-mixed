#ifndef DRILLEREGGMAN_H
#define DRILLEREGGMAN_H

class DrillerEggman;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class DrillerEggman: public Enemy {
public:    
    
    Uint32 MainPalette[16];
    Uint32 HurtPalette[16];
    int TimerAction;
    int InvulnTimer;
    int ExplosionTimer;
    int State;
    
    void Create();
    int OnHit();
    void Update();
    void Render(int CamX, int CamY);
};

#endif /* DRILLEREGGMAN_H */
