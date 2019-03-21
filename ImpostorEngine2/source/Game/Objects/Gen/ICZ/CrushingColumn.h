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
    enum PillarType {
        UNKNOWN = 0,
        CEILING_CRUSH = 1,
        CEILING_CRUSH_PERIODIC = 2,
        FLOOR_CRUSH = 3,
        FLOOR_CRUSH_PERIODIC = 4,
        STATIONARY_KNUX_ONLY = 5,
    };
    enum PillarState {
        MOVE_TOWARDS_CRUSH = 2,
        INIT = 0,
        WAIT = 1,
        BLOCK = 3,
        BACK_AWAY = 4,
    };
    enum PillarAction {
        WAITACTION = 0,
        MOVE_UPACTION = 1,
        BLOCKACTION = 2,
        CRUSH_DOWNACTION = 3,
    };
    
    int Type;
    int State;
    int TimerAction;
    int FloorY;
    
    CONSTRUCTER CrushingColumn();
    void Create();
    void Update();
    void Render(int CamX, int CamY);
    int OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data);
};

#endif /* CRUSHINGCOLUMN_H */
