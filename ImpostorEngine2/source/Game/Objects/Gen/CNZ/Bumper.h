#ifndef BUMPER_H
#define BUMPER_H

class Bumper;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class Bumper: public Object {
public:    
    
    int ForceX;
    int ForceY;
    int ForcePower;
    
    void Create();
    void Update();
    void Render(int CamX, int CamY);
    int OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data);
};

#endif /* BUMPER_H */
