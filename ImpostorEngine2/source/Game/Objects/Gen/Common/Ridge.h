#ifndef RIDGE_H
#define RIDGE_H

class Ridge;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class Ridge: public Object {
public:    
    
    
    void Create();
    int OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data);
};

#endif /* RIDGE_H */
