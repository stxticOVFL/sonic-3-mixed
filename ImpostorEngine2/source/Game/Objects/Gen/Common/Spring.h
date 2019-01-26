#ifndef SPRING_H
#define SPRING_H

class Spring;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class Spring: public Object {
public:    
    
    int Diagonal;
    int SpringType;
    int Rotation;
    bool DoAnimate;
    int SpringPower;
    int Twirl;
    bool KillTransverseSpeed;
    
    void Create();
    void Update();
    int OnLeaveScreen();
    void Render(int CamX, int CamY);
    int OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data);
};

#endif /* SPRING_H */
