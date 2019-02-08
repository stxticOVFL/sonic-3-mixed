#ifndef CORKFLOOR_H
#define CORKFLOOR_H

class CorkFloor;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class CorkFloor: public Object {
public:    
    
    Sint16 PieceVels[64];
    bool BreakableFromTop;
    
    void Create();
    void BreakAIZ(int HitSide);
    void Render(int CamX, int CamY);
    int OnBreakVertical(int PlayerID, int HitFrom);
};

#endif /* CORKFLOOR_H */
