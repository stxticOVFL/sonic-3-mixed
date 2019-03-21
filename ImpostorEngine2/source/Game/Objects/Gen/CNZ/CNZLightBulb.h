#ifndef CNZLIGHTBULB_H
#define CNZLIGHTBULB_H

class CNZLightBulb;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class CNZLightBulb: public Object {
public:    
    
    bool Broken;
    
    void Create();
    void Update();
    void Render(int CamX, int CamY);
};

#endif /* CNZLIGHTBULB_H */
