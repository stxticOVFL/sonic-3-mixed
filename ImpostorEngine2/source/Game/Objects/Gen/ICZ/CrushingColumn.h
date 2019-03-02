#ifndef CRUSHINGCOLUMN_H
#define CRUSHINGCOLUMN_H

class CrushingColumn;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class CrushingColumn: public Object {
public:    
    
    int OGY;
    bool Direction;
    int Timer;
    int SmashStyle;
    int SmashTimer;
    int State;
    
    void Create();
    void Update();
    void Render(int CamX, int CamY);
    int OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data);
};

#endif /* CRUSHINGCOLUMN_H */
