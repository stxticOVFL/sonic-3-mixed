#ifndef TREEBARK_H
#define TREEBARK_H

class TreeBark;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class TreeBark: public Object {
public:    
    
    
    void Create();
    void Render(int CamX, int CamY);
};

#endif /* TREEBARK_H */
