#ifndef MGZTRIGGERPLATFORM_H
#define MGZTRIGGERPLATFORM_H

class MGZTriggerPlatform;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class MGZTriggerPlatform: public Object {
public:    
    
    int TriggerID;
    int PlatformType;
    
    void Create();
    void Update();
    void Render(int CamX, int CamY);
};

#endif /* MGZTRIGGERPLATFORM_H */
