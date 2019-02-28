// Object ID: 0x55
// Object Name: Relief.cpp

#include "Relief.h"

typedef IMath Math;

void Relief::Create() {
    Object::Create();
    Active = true;
    Priority = false;
    W = 12;
    H = 56 * 2;
    Solid = true;
    Scene->AddSelfToRegistry(this, "Solid");
    VisualLayer = 1;
    Object* Child;
    Child = Scene->AddNewObject(Obj_ReliefEye, SubType, X, Y, FlipX, false);
    Child->Sprite = Sprite;
}

void Relief::Render(int CamX, int CamY) {
    G->DrawSprite(Sprite, 3, 6, X - CamX, Y - CamY, 0, FlipX ? IE_FLIPX : IE_NOFLIP);
    }

