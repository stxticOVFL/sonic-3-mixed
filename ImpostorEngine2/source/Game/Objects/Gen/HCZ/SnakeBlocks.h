#ifndef SNAKEBLOCKS_H
#define SNAKEBLOCKS_H

class SnakeBlocks;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class SnakeBlocks: public Object {
public:    
    
    int Offset;
    bool Reverse;
    int DirX;
    int DirY;
    
    void Create();
    void Update();
    void Render(int CamX, int CamY);
};

#endif /* SNAKEBLOCKS_H */
