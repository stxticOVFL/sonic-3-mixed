// Object ID: 0xB3
// Object Name: SegmentedColumn.cpp

#include "SegmentedColumn.h"

typedef IMath Math;

void SegmentedColumn::Create() {
    Object::Create();
    Active = true;
    Priority = false;
    for (int i = 0; i < 4; i++)
{
        Stubs[i] = Scene->AddNewObject(Obj_SegmentedColumnStub, i == 3 ? (SubType == 0 ? 1 : 2) : 0, X, Y - (i * 32), false, false);
        Stubs[i]->Sprite = Sprite;
    }
}

