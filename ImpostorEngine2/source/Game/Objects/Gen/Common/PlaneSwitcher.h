#ifndef PLANESWITCHER_H
#define PLANESWITCHER_H

class PlaneSwitcher;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class PlaneSwitcher: public Object {
public:    
    
    int Angle;
    int Flags;
    bool OnPath;
    int Size;
    
    void Create();
    void Render(int CamX, int CamY);
    int OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data);
};

#endif /* PLANESWITCHER_H */
