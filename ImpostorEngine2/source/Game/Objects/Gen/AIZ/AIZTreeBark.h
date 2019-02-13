#ifndef AIZTREEBARK_H
#define AIZTREEBARK_H

class AIZTreeBark;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class AIZTreeBark: public Object {
public:    
    
    
    void Create();
    void Render(int CamX, int CamY);
};

#endif /* AIZTREEBARK_H */
