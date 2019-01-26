#ifndef CUTSCENEKNUCKLES_H
#define CUTSCENEKNUCKLES_H

class CutsceneKnuckles;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class CutsceneKnuckles: public Object {
public:    
    
    int CustomFrameToLoop;
    int CustomFrameToCount;
    int SubX;
    int SubY;
    int RoutineNumber;
    bool Ground;
    
    void Create();
    void HCZ2();
    void Update();
    void Render(int CamX, int CamY);
    void Chuckle();
};

#endif /* CUTSCENEKNUCKLES_H */
