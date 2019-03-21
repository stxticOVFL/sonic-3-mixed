#ifndef SWINGINGPLATFORMTRIGGER_H
#define SWINGINGPLATFORMTRIGGER_H

class SwingingPlatformTrigger;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class SwingingPlatformTrigger: public Object {
public:    
    
    IPlayer* Player;
    Object* SwingPlatform;
    
    CONSTRUCTER SwingingPlatformTrigger();
    void Create();
    void Update();
};

#endif /* SWINGINGPLATFORMTRIGGER_H */
