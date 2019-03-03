#ifndef ANIMSPRITE_H
#define ANIMSPRITE_H

class AnimSprite;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class AnimSprite: public Object {
public:    
    
    int FrameStart;
    int FrameCount;
    int FrameLength;
    
    void Create();
    void Update();
    void Render(int CamX, int CamY);
};

#endif /* ANIMSPRITE_H */
