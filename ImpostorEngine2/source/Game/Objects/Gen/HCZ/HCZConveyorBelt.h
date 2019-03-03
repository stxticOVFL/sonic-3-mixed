#ifndef HCZCONVEYORBELT_H
#define HCZCONVEYORBELT_H

class HCZConveyorBelt;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class HCZConveyorBelt: public Object {
public:    
    
    int StartX;
    int EndX;
    
    void Create();
    void Update();
    void Render(int CamX, int CamY);
};

#endif /* HCZCONVEYORBELT_H */
