#ifndef AIZINTROKNUX_H
#define AIZINTROKNUX_H

class AIZIntroKnux;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class AIZIntroKnux: public Object {
public:    
    
    int ActionTimer;
    int Action;
    int Cutscene_KnucklesBackForth;
    int JumpAnim;
    int AnimTimer;
    int Floor;
    bool StayGrounded;
    bool AllowGrounded;
    int PebbleX;
    int PebbleY;
    bool LandStarted;
    bool LandFinished;
    int EmeraldsX;
    int EmeraldsY;
    bool DisplayEmeralds;
    
    void Create();
    void Update();
    void Render(int CamX, int CamY);
    void UpdateSubType();
};

#endif /* AIZINTROKNUX_H */
