#ifndef CONVEYORBELT_H
#define CONVEYORBELT_H

class ConveyorBelt;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class ConveyorBelt: public Object {
public:    
    
    int StartX;
    int EndX;
    
    void Create();
    void Update();
    void Render(int CamX, int CamY);
};

#endif /* CONVEYORBELT_H */
