#ifndef STALAGTITE_H
#define STALAGTITE_H

class Stalagtite;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class Stalagtite: public Object {
public:    
    
    int OGY;
    int OGX;
    bool Fallen;
    int FallTimer;
    int ParticleAnim;
    
    CONSTRUCTER Stalagtite();
    void Create();
    void Update();
    int OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data);
    void Render(int CamX, int CamY);
};

#endif /* STALAGTITE_H */
