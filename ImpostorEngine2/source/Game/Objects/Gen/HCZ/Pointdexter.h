#ifndef POINTDEXTER_H
#define POINTDEXTER_H

class Pointdexter;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class Pointdexter: public Enemy {
public:    
    
    int Flip;
    int SubX;
    
    void Create();
    int OnHit();
    void Update();
    void Render(int CamX, int CamY);
};

#endif /* POINTDEXTER_H */
