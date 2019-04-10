#ifndef WATERSPLASH_H
#define WATERSPLASH_H

class WaterSplash;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class WaterSplash: public Object {
public:    
    
    
    void Create();
    void Render(int CamX, int CamY);
};

#endif /* WATERSPLASH_H */
