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
    
    CONSTRUCTER Spring();
    void Create();
    void Update();
    void OnAnimationFinish();
    int OnLeaveScreen();
    void Render(int CamX, int CamY);
    int OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data);
    void UpdateSubType();
    uint8_t GetSubTypeIncrement();
    uint8_t GetSubTypeMax();
};

#endif /* SPRING_H */
