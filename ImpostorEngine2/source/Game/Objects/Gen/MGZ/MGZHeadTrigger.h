#ifndef MGZHEADTRIGGER_H
#define MGZHEADTRIGGER_H

class MGZHeadTrigger;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class MGZHeadTrigger: public Object {
public:    
    
    
    void Create();
    void Render(int CamX, int CamY);
};

#endif /* MGZHEADTRIGGER_H */
