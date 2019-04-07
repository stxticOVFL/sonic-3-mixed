#ifndef SPECIALRING_H
#define SPECIALRING_H

class SpecialRing;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class SpecialRing: public Object {
public:    
    
    int HyperColor;
    bool HyperRing;
    int percent;
    int GoTimer;
    int StoredX;
    int StoredY;
    bool Used;
    int RingID;
	double Scale;
    
    void Create();
    void Update();
    void Render(int CamX, int CamY);
    int OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data);
};

#endif /* SPECIALRING_H */
