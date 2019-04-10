#ifndef SLIDE_H
#define SLIDE_H

class Slide;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class Slide: public Object {
public:    
    
    int PlayersGot[8];
    bool Bottom;
    int SlideType;
    
    void Create();
    int GetX(int TheY);
    int GetWidth();
    int GetHeight();
    void Update();
    void Render(int CamX, int CamY);
    int OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data);
};

#endif /* SLIDE_H */
