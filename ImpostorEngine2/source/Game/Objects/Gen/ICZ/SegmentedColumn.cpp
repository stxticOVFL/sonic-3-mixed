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
        SolidList[i] = Stubs[i]->Solid;
    }
    BreakTimer = 0;
}

void SegmentedColumn::Update() {
    BreakTimer = BreakTimer == 0 ? 0 : BreakTimer - 1;
    SolidCount = 0;
    for (int i = 0; i < 4; i++)
{
        SolidCount = SolidList[i] ? SolidCount + 1 : SolidCount;
        if (SolidList[i] != Stubs[i]->Solid) {
            SolidCount--;
            BreakTimer = 30 + (SolidCount * 8);
        }

        SolidList[i] = Stubs[i]->Solid;
    }
    for (int i = 0; i < 4; i++)
{
        if (Stubs[i]->Solid && Stubs[i]->SubType != 2 && BreakTimer == 0) {
            Stubs[i]->BreakableByRoll = CollideSide::SIDES;
            Scene->AddSelfToRegistry(Stubs[i], "Breakable");
            break;
        }

    }
    if (BreakTimer <= (SolidCount * 8) && BreakTimer != 0) {
        Stub = Stubs[(32 - BreakTimer) / 8];
        Stub->Y += 4;
        YStack += 4;
        if (YStack == 32) {
            Sound::Play(Sound::SFX_IMPACT5);
            YStack = 0;
        }

    }

    Object::Update();
}

