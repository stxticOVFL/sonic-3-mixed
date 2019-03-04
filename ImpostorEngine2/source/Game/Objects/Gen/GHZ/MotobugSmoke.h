#ifndef MOTOBUGSMOKE_H
#define MOTOBUGSMOKE_H

class MotobugSmoke;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class MotobugSmoke: public Object {
public:    
    
    int SmokeTime;
    
    CONSTRUCTER MotobugSmoke();
    void Create();
    void Update();
    void Render(int CamX, int CamY);
};

#endif /* MOTOBUGSMOKE_H */
