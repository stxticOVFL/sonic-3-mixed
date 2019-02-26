#ifndef VIEWCOLLISIONTOGGLER_H
#define VIEWCOLLISIONTOGGLER_H

class ViewCollisionToggler;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class ViewCollisionToggler: public Object {
public:    
    
    
    void Create();
    void Update();
    void Render(int CamX, int CamY);
};

#endif /* VIEWCOLLISIONTOGGLER_H */
