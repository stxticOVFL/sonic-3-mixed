#ifndef NONANIMSPRITE_H
#define NONANIMSPRITE_H

class NonAnimSprite;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class NonAnimSprite: public Object {
public:    
    
    
    void Create();
    void Render(int CamX, int CamY);
};

#endif /* NONANIMSPRITE_H */
