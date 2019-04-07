#ifndef FIREBREATHBOMB_H
#define FIREBREATHBOMB_H

class FireBreathBomb;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class FireBreathBomb: public Enemy {
public:    
    
    
    void Create();
    int OnHit();
    void Update();
    void Render(int CamX, int CamY);
};

#endif /* FIREBREATHBOMB_H */
