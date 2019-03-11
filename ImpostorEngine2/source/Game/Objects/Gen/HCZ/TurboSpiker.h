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
    bool Fired;
    int FireTimer;
    int MoveTimer;
    int KeptFlip;
    int TurnTimer;
    bool Turning;
    
    void Create();
    int OnHit();
    void Update();
    void MoveSprite();
    void Render(int CamX, int CamY);
};

#endif /* TURBOSPIKER_H */
