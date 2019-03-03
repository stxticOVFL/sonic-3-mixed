#ifndef SWINGVINE_H
#define SWINGVINE_H

class SwingVine;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class SwingVine: public Object {
public:    
    
    int RopeLength;
    int AngleOffset;
    int Oscello;
    int LastX;
    int LastY;
    int PlayersControlled;
    bool ClassicStyle;
    
    void Create();
    void Update();
    void Render(int CamX, int CamY);
    int OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data);
};

#endif /* SWINGVINE_H */
