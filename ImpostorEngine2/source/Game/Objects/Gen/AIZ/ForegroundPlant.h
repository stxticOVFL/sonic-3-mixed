#ifndef FOREGROUNDPLANT_H
#define FOREGROUNDPLANT_H

class ForegroundPlant;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class ForegroundPlant: public Object {
public:    
    
    int CamMult;
    
    void Create();
    void Render(int CamX, int CamY);
};

#endif /* FOREGROUNDPLANT_H */
