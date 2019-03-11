#ifndef STARPOINTERORBS_H
#define STARPOINTERORBS_H

class StarPointerOrbs;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class StarPointerOrbs: public Enemy {
public:    
    
    
    void Create();
    void Render(int CamX, int CamY);
};

#endif /* STARPOINTERORBS_H */
