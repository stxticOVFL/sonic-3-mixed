#ifndef AIZMINIBOSSBOMB_H
#define AIZMINIBOSSBOMB_H

class AIZMinibossBomb;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class AIZMinibossBomb: public Enemy {
public:    
    
    
    void Create();
    int OnHit();
    void Update();
    void Render(int CamX, int CamY);
};

#endif /* AIZMINIBOSSBOMB_H */
