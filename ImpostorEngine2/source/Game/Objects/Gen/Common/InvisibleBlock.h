#ifndef INVISIBLEBLOCK_H
#define INVISIBLEBLOCK_H

class InvisibleBlock;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class InvisibleBlock: public Object {
public:    
    
    bool Painful;
    bool Deadly;
    int Rotation;
    int Size;
    
    void Create();
    void UpdateSubType();
    uint8_t GetSubTypeIncrement();
    uint8_t GetSubTypeMax();
    void Render(int CamX, int CamY);
    int OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data);
};

#endif /* INVISIBLEBLOCK_H */
