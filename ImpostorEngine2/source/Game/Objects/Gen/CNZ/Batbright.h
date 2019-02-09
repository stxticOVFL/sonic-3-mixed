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
    
    void Create();
    void Update();
    void OnAnimationFinish();
    int OnHit();
    int OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data);
};

#endif /* BATBRIGHT_H */
