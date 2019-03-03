#ifndef RIDEVINE_H
#define RIDEVINE_H

class RideVine;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class RideVine: public Object {
public:    
    
    int RopeLength;
    int AngleOffset;
    int Oscello;
    int LastX;
    int LastY;
    int BaseX;
    int BaseY;
    int EndX;
    bool Fireable;
    bool OnFire;
    bool ZipActive;
    bool Spinning;
    int PlayersControlled;
    int Amp;
    bool ClassicStyle;
    
    void Create();
    int OnLeaveScreen();
    void Update();
    void Render(int CamX, int CamY);
    int OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data);
};

#endif /* RIDEVINE_H */
