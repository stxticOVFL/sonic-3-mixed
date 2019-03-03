// Object ID: 0x09
// Object Name: TreeBark.cpp

#include "TreeBark.h"

typedef IMath Math;

void TreeBark::Create() {
    Object::Create();
    Active = true;
    Priority = false;
    W = 16;
    H = 16;
    CurrentAnimation = 0;
    Frame = 0;
}

void TreeBark::Render(int CamX, int CamY) {
    G->DrawSprite(Sprite, CurrentAnimation, Frame, X - CamX, Y - CamY, 0, IE_NOFLIP);
    }

