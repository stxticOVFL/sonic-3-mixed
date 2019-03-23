#ifndef RHINOBOT_H
#define RHINOBOT_H

class Rhinobot;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class Rhinobot: public Enemy {
public:    
    
    int SubX;
    int Speed;
    int Acceleration;
    
    void Create();
    void Update();
    void Render(int CamX, int CamY);
};

#endif /* RHINOBOT_H */
