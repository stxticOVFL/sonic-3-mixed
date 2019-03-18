#ifndef ICECUBE_H
#define ICECUBE_H

class IceCube;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class IceCube: public Object {
public:    
    
    
    CONSTRUCTER IceCube();
    void Create();
    void Render(int CamX, int CamY);
    void Break();
    int OnBreakVertical(int PlayerID, int HitFrom);
    int OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data);
};

#endif /* ICECUBE_H */
