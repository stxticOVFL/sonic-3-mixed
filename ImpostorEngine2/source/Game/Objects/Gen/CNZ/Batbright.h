#ifndef BATBRIGHT_H
#define BATBRIGHT_H

class Batbright;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class Batbright: public Enemy {
public:    
    
    Object* Children[2];
    Object* WorkingChild;
    int16_t AnimationData[6];
    
    void Create();
    void Update();
    void OnAnimationFinish();
    int OnHit();
    int OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data);
    void Render(int CamX, int CamY);
};

#endif /* BATBRIGHT_H */
