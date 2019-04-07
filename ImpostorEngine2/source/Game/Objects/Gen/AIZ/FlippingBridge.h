#ifndef FLIPPINGBRIDGE_H
#define FLIPPINGBRIDGE_H

class FlippingBridge;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class FlippingBridge: public Object {
public:    
    
    int Delay;
    int Period;
    int Rise;
    int Flip;
    int RevolutionDuration;
    
    CONSTRUCTER FlippingBridge();
    void Create();
    void Update();
    void Render(int CamX, int CamY);
    int CustomSolidityCheck(int probeX, int probeY, int PlayerID, int checkJumpThrough);
};

#endif /* FLIPPINGBRIDGE_H */
