#ifndef SIGNPOST_H
#define SIGNPOST_H

class Signpost;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class Signpost: public Object {
public:    
    
    int SubX;
    int SubY;
    int SpinSpeed;
    int Rot;
    bool Falling;
    
    void Create();
    void Update();
    void Render(int CamX, int CamY);
    int OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data);
};

#endif /* SIGNPOST_H */
