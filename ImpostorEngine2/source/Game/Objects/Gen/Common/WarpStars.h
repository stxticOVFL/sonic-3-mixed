#ifndef WARPSTARS_H
#define WARPSTARS_H

class WarpStars;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class WarpStars: public Object {
public:    
    
    bool Activated;
    
    CONSTRUCTER WarpStars();
    void Create();
    void Update();
    void Render(int CamX, int CamY);
    int OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data);
};

#endif /* WARPSTARS_H */
