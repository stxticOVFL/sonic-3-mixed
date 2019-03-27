#ifndef BLOOMINATOR_H
#define BLOOMINATOR_H

class Bloominator;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class Bloominator: public Enemy {
public:    
    
    Object* Children[2];
    
    CONSTRUCTER Bloominator();
    void Create();
    void Update();
    int OnHit();
    void Render(int CamX, int CamY);
};

#endif /* BLOOMINATOR_H */
