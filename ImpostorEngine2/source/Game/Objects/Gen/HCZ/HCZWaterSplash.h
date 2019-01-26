#ifndef HCZWATERSPLASH_H
#define HCZWATERSPLASH_H

class HCZWaterSplash;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class HCZWaterSplash: public Object {
public:    
    
    
    void Create();
    void Render(int CamX, int CamY);
};

#endif /* HCZWATERSPLASH_H */
