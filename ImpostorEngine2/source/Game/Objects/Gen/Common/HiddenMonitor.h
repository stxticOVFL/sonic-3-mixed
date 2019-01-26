#ifndef HIDDENMONITOR_H
#define HIDDENMONITOR_H

class HiddenMonitor;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class HiddenMonitor: public Object {
public:    
    
    
    void Create();
    void Render(int CamX, int CamY);
};

#endif /* HIDDENMONITOR_H */
