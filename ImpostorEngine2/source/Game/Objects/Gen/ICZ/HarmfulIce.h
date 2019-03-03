#ifndef HARMFULICE_H
#define HARMFULICE_H

class HarmfulIce;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class HarmfulIce: public Object {
public:    
    
    
    void Create();
    void Render(int CamX, int CamY);
    int OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data);
};

#endif /* HARMFULICE_H */
