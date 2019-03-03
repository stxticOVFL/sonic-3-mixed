#ifndef BLASTOID_H
#define BLASTOID_H

class Blastoid;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class Blastoid: public Enemy {
public:    
    
    Object* Children[8];
    int ShotIndex;
    
    void Create();
    int OnHit();
    void Update();
    void Render(int CamX, int CamY);
};

#endif /* BLASTOID_H */
