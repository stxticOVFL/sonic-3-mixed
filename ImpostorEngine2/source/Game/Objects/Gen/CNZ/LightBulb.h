#ifndef LIGHTBULB_H
#define LIGHTBULB_H

class LightBulb;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class LightBulb: public Object {
public:    
    
    bool Broken;
    
    void Create();
    void Update();
    void Render(int CamX, int CamY);
};

#endif /* LIGHTBULB_H */
