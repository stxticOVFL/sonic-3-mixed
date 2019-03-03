#ifndef BLASTOIDSHOT_H
#define BLASTOIDSHOT_H

class BlastoidShot;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class BlastoidShot: public Enemy {
public:    
    
    
    void Create();
    void Update();
    void Render(int CamX, int CamY);
};

#endif /* BLASTOIDSHOT_H */
