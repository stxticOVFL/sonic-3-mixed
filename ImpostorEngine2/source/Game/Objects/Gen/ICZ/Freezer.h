#ifndef FREEZER_H
#define FREEZER_H

class Freezer;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class Freezer: public Object {
public:    
    
    int FreezeTimer;
    bool OnOff;
    int DustAnimation;
    int IceCubeAnimation;
    int WaitTimer;
    int Range;
    int FrozenTimer[7];
    bool Frozen[7];
    int StoredX[7];
    int StoredY[7];
    int StoredFrame[7];
    
    CONSTRUCTER Freezer();
    void Create();
    void Update();
    void Render(int CamX, int CamY);
};

#endif /* FREEZER_H */
