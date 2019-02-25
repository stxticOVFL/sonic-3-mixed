#ifndef RELIEFEYE_H
#define RELIEFEYE_H

class ReliefEye;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class ReliefEye: public Enemy {
public:    
    
    int InvulnTimer;
    int ExplosionTimer;
    
    void Create();
    void Update();
    int OnHit();
    void HandleDamage();
    void Render(int CamX, int CamY);
};

#endif /* RELIEFEYE_H */
