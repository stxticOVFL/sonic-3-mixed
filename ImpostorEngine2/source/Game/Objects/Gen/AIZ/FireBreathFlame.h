#ifndef FIREBREATHFLAME_H
#define FIREBREATHFLAME_H

class FireBreathFlame;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class FireBreathFlame: public Enemy {
public:    
    
    int TimerAction;
    
    void Create();
    int OnHit();
    void Update();
    void Render(int CamX, int CamY);
};

#endif /* FIREBREATHFLAME_H */
