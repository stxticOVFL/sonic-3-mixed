#ifndef BLANKOBJECT_H
#define BLANKOBJECT_H

class BlankObject;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class BlankObject: public Object {
public:    
    
    
    void Create();
    void Render(int CamX, int CamY);
};

#endif /* BLANKOBJECT_H */
