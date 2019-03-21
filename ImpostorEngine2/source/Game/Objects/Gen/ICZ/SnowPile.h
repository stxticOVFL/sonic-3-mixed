#ifndef SNOWPILE_H
#define SNOWPILE_H

class SnowPile;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class SnowPile: public Object {
public:    
    
    
    CONSTRUCTER SnowPile();
    void Create();
    void Render(int CamX, int CamY);
    int OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data);
};

#endif /* SNOWPILE_H */
