#ifndef QUICKMUD_H
#define QUICKMUD_H

class QuickMud;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class QuickMud: public Object {
public:    
    
    
    void Create();
    int OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data);
};

#endif /* QUICKMUD_H */
