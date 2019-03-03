#ifndef MOTOBUG_H
#define MOTOBUG_H

class Motobug;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class Motobug: public Object {
public:    
    
    
    CONSTRUCTER Motobug();
    void Create();
    void Update();
    void Render(int CamX, int CamY);
};

#endif /* MOTOBUG_H */
