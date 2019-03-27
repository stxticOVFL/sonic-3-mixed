#ifndef PLATFORMOUTLINER_H
#define PLATFORMOUTLINER_H

class PlatformOutliner;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class PlatformOutliner: public Object {
public:    
    
    
    CONSTRUCTER PlatformOutliner();
    void Create();
    void Update();
    void OnAnimationFinish();
    void Render(int CamX, int CamY);
};

#endif /* PLATFORMOUTLINER_H */
