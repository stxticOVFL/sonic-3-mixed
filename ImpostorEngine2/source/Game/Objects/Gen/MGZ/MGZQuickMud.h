#ifndef MGZQUICKMUD_H
#define MGZQUICKMUD_H

class MGZQuickMud;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class MGZQuickMud: public Object {
public:    
    
    
    void Create();
    int OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data);
};

#endif /* MGZQUICKMUD_H */
