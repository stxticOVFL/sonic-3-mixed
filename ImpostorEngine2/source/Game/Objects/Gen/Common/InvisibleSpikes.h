#ifndef INVISIBLESPIKES_H
#define INVISIBLESPIKES_H

class InvisibleSpikes;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class InvisibleSpikes: public Object {
public:    
    
    bool Painful;
    bool Deadly;
    int Rotation;
    int Size;
    
    void Create();
    int OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data);
};

#endif /* INVISIBLESPIKES_H */
