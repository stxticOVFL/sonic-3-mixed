#ifndef SPIKER_H
#define SPIKER_H

class Spiker;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class Spiker: public Enemy {
public:    
    
    bool Rise;
    int StartYpos;
    
    void Create();
    int OnHit();
    void Update();
    void Render(int CamX, int CamY);
    int OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data);
};

#endif /* SPIKER_H */
