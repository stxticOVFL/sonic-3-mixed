#ifndef TURBOSPIKER_H
#define TURBOSPIKER_H

class TurboSpiker;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class TurboSpiker: public Enemy {
public:    
    
    int Flip;
    
    void Create();
    int OnHit();
    void Update();
    void Render(int CamX, int CamY);
};

#endif /* TURBOSPIKER_H */
