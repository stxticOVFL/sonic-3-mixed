#ifndef COLLAPSINGPLATFORM_H
#define COLLAPSINGPLATFORM_H

class CollapsingPlatform;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class CollapsingPlatform: public Object {
public:    
    
    int f;
    int Allotted;
    int Separation;
    int Sections;
    int Vsect;
    Object* Outliner;
    
    CONSTRUCTER CollapsingPlatform();
    void Create();
    void Update();
    void Break();
    int OnLeaveScreen();
    void Render(int CamX, int CamY);
    int CustomSolidityCheck(int probeX, int probeY, int PlayerID, int checkJumpThrough);
};

#endif /* COLLAPSINGPLATFORM_H */
