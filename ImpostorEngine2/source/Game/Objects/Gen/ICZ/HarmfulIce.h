#ifndef HARMFULICE_H
#define HARMFULICE_H

class HarmfulIce;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class HarmfulIce: public Enemy {
public:    
    
    
    CONSTRUCTER HarmfulIce();
    void Create();
    void Render(int CamX, int CamY);
};

#endif /* HARMFULICE_H */
