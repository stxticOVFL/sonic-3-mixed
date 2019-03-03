#ifndef BLOCK_H
#define BLOCK_H

class Block;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class Block: public Object {
public:    
    
    
    void Create();
    void Render(int CamX, int CamY);
};

#endif /* BLOCK_H */
