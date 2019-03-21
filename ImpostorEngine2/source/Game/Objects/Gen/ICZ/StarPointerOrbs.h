#ifndef STARPOINTERORBS_H
#define STARPOINTERORBS_H

class StarPointerOrbs;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class StarPointerOrbs: public Object {
public:    
    
    
    CONSTRUCTER StarPointerOrbs();
    void Create();
    void Render(int CamX, int CamY);
    int OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data);
};

#endif /* STARPOINTERORBS_H */
