#ifndef NONANIM_H
#define NONANIM_H

class NonAnim;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class NonAnim: public Object {
public:    
    
    
    void Create();
    void Render(int CamX, int CamY);
};

#endif /* NONANIM_H */
