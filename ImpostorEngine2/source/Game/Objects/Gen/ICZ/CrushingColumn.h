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
    enum PillarState {
        WAIT = 0,
        MOVE_UP = 1,
        BLOCK = 2,
        CRUSH_DOWN = 3,
    };
    enum PillarAction {
        WAITACTION = 0,
        MOVE_UPACTION = 1,
        BLOCKACTION = 2,
        CRUSH_DOWNACTION = 3,
    };
    
    int OGY;
    bool Direction;
    int SmashStyle;
    int SmashTimer;
    int State;
    int TimerAction;
    
    void Create();
    void Update();
    void Render(int CamX, int CamY);
    int OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data);
};

#endif /* CRUSHINGCOLUMN_H */
