#ifndef HCZWATERWALL_H
#define HCZWATERWALL_H

class HCZWaterWall;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class HCZWaterWall: public Object {
public:    
    
    
    void Create();
    void Render(int CamX, int CamY);
    int OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data);
};

#endif /* HCZWATERWALL_H */
