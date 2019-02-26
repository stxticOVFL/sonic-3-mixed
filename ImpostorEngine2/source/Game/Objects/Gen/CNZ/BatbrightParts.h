#ifndef BATBRIGHTPARTS_H
#define BATBRIGHTPARTS_H

class BatbrightParts;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class BatbrightParts: public Enemy {
public:    
    
    bool IsLight;
    int16_t AnimationData[14];
    
    void Create();
    void Update();
    void Render(int CamX, int CamY);
};

#endif /* BATBRIGHTPARTS_H */
