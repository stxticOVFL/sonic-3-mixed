#ifndef AIRSHIPBOMB_H
#define AIRSHIPBOMB_H

class AirshipBomb;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class AirshipBomb: public Enemy {
public:    
    
    int WeY;
    
    void Create();
    void Update();
    void Render(int CamX, int CamY);
};

#endif /* AIRSHIPBOMB_H */
