#ifndef STARPOST_H
#define STARPOST_H

class StarPost;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class StarPost: public Object {
public:    
    
    bool Activated;
    int Spin;
    bool Blinking;
    bool ShowStars;
    int StarTimer;
    Object* Stars[4];
    
    CONSTRUCTER StarPost();
    void Create();
    void Update();
    int OnLeaveScreen();
    void DrawStar(int Rock, int Ang, int Side, int CamX, int CamY);
    void Render(int CamX, int CamY);
    int OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data);
};

#endif /* STARPOST_H */
