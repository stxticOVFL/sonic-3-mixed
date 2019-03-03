#ifndef COLLAPSINGBRIDGE_H
#define COLLAPSINGBRIDGE_H

class CollapsingBridge;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class CollapsingBridge: public Object {
public:    
    
    int f;
    int Allotted;
    int Separation;
    int Sections;
    int Vsect;
    int Reset;
    int BridgeType;
    int TriggerID;
    int Delay;
    bool UseTrigger;
    bool BreakSide;
    
    void Create();
    void Update();
    void BreakHCZ();
    void BreakMGZ();
    void BreakICZ();
    void Break();
    void Render(int CamX, int CamY);
    int CustomSolidityCheck(int probeX, int probeY, int PlayerID, int checkJumpThrough);
};

#endif /* COLLAPSINGBRIDGE_H */
