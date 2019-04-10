#ifndef TRIGGERPLATFORM_H
#define TRIGGERPLATFORM_H

class TriggerPlatform;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class TriggerPlatform: public Object {
public:    
    
    int TriggerID;
    int PlatformType;
    
    void Create();
    void Update();
    void Render(int CamX, int CamY);
};

#endif /* TRIGGERPLATFORM_H */
