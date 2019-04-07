#ifndef COLLAPSINGLOGBRIDGE_H
#define COLLAPSINGLOGBRIDGE_H

class CollapsingLogBridge;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class CollapsingLogBridge: public Solid {
public:    
    
    bool Drawbridge;
    int Allotted;
    
    CONSTRUCTER CollapsingLogBridge();
    void Create();
    void Update();
    void Break();
    void Render(int CamX, int CamY);
    int CustomSolidityCheck(int probeX, int probeY, int PlayerID, int checkJumpThrough);
};

#endif /* COLLAPSINGLOGBRIDGE_H */
