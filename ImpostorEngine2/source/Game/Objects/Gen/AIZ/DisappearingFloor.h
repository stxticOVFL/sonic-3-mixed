#ifndef DISAPPEARINGFLOOR_H
#define DISAPPEARINGFLOOR_H

class DisappearingFloor;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class DisappearingFloor: public Object {
public:    
    
    int Offset;
    int Period;
    int PeriodFrames;
    bool Visible;
    
    CONSTRUCTER DisappearingFloor();
    void Create();
    void Update();
    void Render(int CamX, int CamY);
};

#endif /* DISAPPEARINGFLOOR_H */
