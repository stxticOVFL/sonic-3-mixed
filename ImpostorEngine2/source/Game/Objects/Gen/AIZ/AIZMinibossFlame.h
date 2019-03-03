#ifndef AIZMINIBOSSFLAME_H
#define AIZMINIBOSSFLAME_H

class AIZMinibossFlame;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class AIZMinibossFlame: public Enemy {
public:    
    
    int TimerAction;
    
    void Create();
    int OnHit();
    void Update();
    void Render(int CamX, int CamY);
};

#endif /* AIZMINIBOSSFLAME_H */
