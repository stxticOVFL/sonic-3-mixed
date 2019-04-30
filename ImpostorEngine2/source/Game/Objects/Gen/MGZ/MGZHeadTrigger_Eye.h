#ifndef MGZHEADTRIGGER_EYE_H
#define MGZHEADTRIGGER_EYE_H

class MGZHeadTrigger_Eye;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class MGZHeadTrigger_Eye: public Enemy {
public:    
    
    
    void Create();
    void Update();
    int OnHit();
    int OnDeath();
    void Render(int CamX, int CamY);
};

#endif /* MGZHEADTRIGGER_EYE_H */
