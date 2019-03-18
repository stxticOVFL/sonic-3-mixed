#ifndef SEGMENTEDCOLUMNSTUB_H
#define SEGMENTEDCOLUMNSTUB_H

class SegmentedColumnStub;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class SegmentedColumnStub: public Object {
public:    
    
    
    CONSTRUCTER SegmentedColumnStub();
    void Create();
    int OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data);
    void Break();
    void Render(int CamX, int CamY);
    int OnBreakVertical(int PlayerID, int HitFrom);
    int OnBreakHorizontal(int PlayerID, int HitFrom);
};

#endif /* SEGMENTEDCOLUMNSTUB_H */
