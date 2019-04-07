#ifndef FALLINGLOG_H
#define FALLINGLOG_H

class FallingLog;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class FallingLog: public Object {
public:    
    
    int Length;
    int LastY;
    
    CONSTRUCTER FallingLog();
    void Create();
    void Update();
    void Render(int CamX, int CamY);
};

#endif /* FALLINGLOG_H */
