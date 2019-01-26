#ifndef SPINNINGCOLUMN_H
#define SPINNINGCOLUMN_H

class SpinningColumn;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class SpinningColumn: public Object {
public:    
    
    int YS;
    int LastX;
    int LastY;
    int MoveType;
    int ColumnType;
    int MotionDirection;
    
    void Create();
    void Update();
    void Render(int CamX, int CamY);
    int OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data);
};

#endif /* SPINNINGCOLUMN_H */
