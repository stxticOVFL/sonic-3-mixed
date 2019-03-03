#ifndef ROPEPEG_H
#define ROPEPEG_H

class RopePeg;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class RopePeg: public Object {
public:    
    
    
    void Create();
    void Render(int CamX, int CamY);
};

#endif /* ROPEPEG_H */
