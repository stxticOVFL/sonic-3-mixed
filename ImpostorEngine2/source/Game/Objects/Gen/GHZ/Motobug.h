#ifndef MOTOBUG_H
#define MOTOBUG_H

class Motobug;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class Motobug: public Enemy {
public:    
    
    int Acceleration;
    int Time;
    int SmokeDelay;
    int State;
    Object* Smoke;
    
    void Create();
    void Update();
    void Render(int CamX, int CamY);
};

#endif /* MOTOBUG_H */
