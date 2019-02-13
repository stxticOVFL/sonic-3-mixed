#ifndef VACUUMTUBE_H
#define VACUUMTUBE_H

class VacuumTube;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class VacuumTube: public Object {
public:    
    
    bool Vertical;
    int SoundTimer;
    bool PlayerIn[8];
    int PlayerTimer[8];
    
    void Create();
    void Update();
    int OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data);
};

#endif /* VACUUMTUBE_H */
