#ifndef SPIKEDLOG_H
#define SPIKEDLOG_H

class SpikedLog;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class SpikedLog: public Object {
public:    
    
    int Direction;
    int Period;
    int WaterCount;
    int Spin;
    
    void Create();
    void Update();
    void Render(int CamX, int CamY);
    int OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data);
};

#endif /* SPIKEDLOG_H */
