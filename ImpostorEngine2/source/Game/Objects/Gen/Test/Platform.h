#ifndef PLATFORM_H
#define PLATFORM_H

class Platform;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class Platform: public Object {
public:    
    enum PlatformType {
        UNK_2 = 2,
        NORMAL = 0,
        UNK_1 = 1,
        PUSHABLE = 6,
        UNK_3 = 3,
        UNK_4 = 4,
        UNK_5 = 5,
    };
    
    int Type;
    int AmplitudeX;
    int AmplitudeY;
    int Speed;
    bool HasTension;
    int FrameID;
    int Collision;
    int TileOriginX;
    int TileOriginY;
    int ChildCount;
    int Angle;
    
    void Create();
    void Update();
    void Render(int CamX, int CamY);
};

#endif /* PLATFORM_H */
