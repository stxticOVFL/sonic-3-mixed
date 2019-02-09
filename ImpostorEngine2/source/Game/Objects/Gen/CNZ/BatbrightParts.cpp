// Object ID: 0xFFFFFFFF
// Object Name: BatbrightParts.cpp

#include "BatbrightParts.h"

typedef IMath Math;

void BatbrightParts::Create() {
    Object::Create();
    Active = true;
    Priority = true;
    W = 16;
    H = 16;
    VisW = 16;
    VisH = 16;
    Gravity = 0;
    Frame = 0;
    VisualLayer = 1;
}

void BatbrightParts::Update() {
    MoveWithParent();
    Object::Update();
}

void BatbrightParts::Render(int CamX, int CamY) {
    G->DrawSprite(Sprite, CurrentAnimation, Frame, X - CamX, Y - CamY, 0, IE_NOFLIP);
    }

