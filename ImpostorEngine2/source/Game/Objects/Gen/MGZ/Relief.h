#ifndef RELIEF_H
#define RELIEF_H

class Relief;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class Relief: public Object {
public:    
    
    
    void Create();
    void Render(int CamX, int CamY);
};

#endif /* RELIEF_H */
