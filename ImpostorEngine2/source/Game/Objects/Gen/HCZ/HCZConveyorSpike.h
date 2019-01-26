#ifndef HCZCONVEYORSPIKE_H
#define HCZCONVEYORSPIKE_H

class HCZConveyorSpike;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class HCZConveyorSpike: public Object {
public:    
    
    int StartX;
    int EndX;
    bool Painful;
    
    void Create();
    void Update();
    void Render(int CamX, int CamY);
};

#endif /* HCZCONVEYORSPIKE_H */
