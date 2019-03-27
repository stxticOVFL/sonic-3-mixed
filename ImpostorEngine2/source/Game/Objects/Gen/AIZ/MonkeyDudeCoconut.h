#ifndef MONKEYDUDECOCONUT_H
#define MONKEYDUDECOCONUT_H

class MonkeyDudeCoconut;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class MonkeyDudeCoconut: public Enemy {
public:    
    
    
    CONSTRUCTER MonkeyDudeCoconut();
    void Create();
    void Update();
    void Render(int CamX, int CamY);
};

#endif /* MONKEYDUDECOCONUT_H */
