#ifndef INVISIBLEDEATH_H
#define INVISIBLEDEATH_H

class InvisibleDeath;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class InvisibleDeath: public Object {
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

#endif /* INVISIBLEDEATH_H */
