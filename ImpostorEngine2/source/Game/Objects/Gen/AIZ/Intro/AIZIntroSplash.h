#ifndef AIZINTROSPLASH_H
#define AIZINTROSPLASH_H

class AIZIntroSplash;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class AIZIntroSplash: public Object {
public:    
    
    int FrameTimer;
    
    void Create();
    void Update();
    void Render(int CamX, int CamY);
};

#endif /* AIZINTROSPLASH_H */
