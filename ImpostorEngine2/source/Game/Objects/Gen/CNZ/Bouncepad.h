#ifndef BOUNCEPAD_H
#define BOUNCEPAD_H

class Bouncepad;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class Bouncepad: public Object {
public:    
    
    
    void Create();
    int OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data);
    void Render(int CamX, int CamY);
};

#endif /* BOUNCEPAD_H */
