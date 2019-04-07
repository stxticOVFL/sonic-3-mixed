#ifndef DRAWBRIDGE_H
#define DRAWBRIDGE_H

class Drawbridge;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class Drawbridge: public Object {
public:    
    
    bool Activated;
    
    CONSTRUCTER Drawbridge();
    void Create();
    void Update();
    void Break();
    void Render(int CamX, int CamY);
    int CustomSolidityCheck(int probeX, int probeY, int PlayerID, int checkJumpThrough);
};

#endif /* DRAWBRIDGE_H */
