#ifndef BLOOMINATORSPORE_H
#define BLOOMINATORSPORE_H

class BloominatorSpore;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class BloominatorSpore: public Enemy {
public:    
    
    
    void Create();
    void Update();
    void Render(int CamX, int CamY);
};

#endif /* BLOOMINATORSPORE_H */
