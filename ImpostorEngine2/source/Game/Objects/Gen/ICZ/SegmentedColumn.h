#ifndef SEGMENTEDCOLUMN_H
#define SEGMENTEDCOLUMN_H

class SegmentedColumn;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class SegmentedColumn: public Object {
public:    
    
    Object* Stubs[4];
    
    void Create();
};

#endif /* SEGMENTEDCOLUMN_H */
