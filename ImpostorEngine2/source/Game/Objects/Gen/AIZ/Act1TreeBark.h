#ifndef ACT1TREEBARK_H
#define ACT1TREEBARK_H

class Act1TreeBark;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class Act1TreeBark: public Object {
public:    
    
    
    void Create();
    void Render(int CamX, int CamY);
};

#endif /* ACT1TREEBARK_H */
