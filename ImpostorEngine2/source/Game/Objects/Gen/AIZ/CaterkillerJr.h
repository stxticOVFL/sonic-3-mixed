#ifndef CATERKILLERJR_H
#define CATERKILLERJR_H

class CaterkillerJr;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class CaterkillerJr: public Enemy {
public:    
    
    int Routine;
    Uint32 PosTable[0x80];
    
    CONSTRUCTER CaterkillerJr();
    void Create();
    void OnSwingFinish();
    void Update();
    int OnHit();
    void Render(int CamX, int CamY);
};

#endif /* CATERKILLERJR_H */
