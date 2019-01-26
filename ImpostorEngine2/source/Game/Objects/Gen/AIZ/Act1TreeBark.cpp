// Object ID: 0x09
// Object Name: Act1TreeBark.cpp

#include "Act1TreeBark.h"

typedef IMath Math;

void Act1TreeBark::Create() {
    Object::Create();
    Active = true;
    Priority = false;
    W = 16;
    H = 16;
    CurrentAnimation = 0;
    Frame = 0;
}

void Act1TreeBark::Render(int CamX, int CamY) {
    G->DrawSprite(Sprite, CurrentAnimation, Frame, X - CamX, Y - CamY, 0, IE_NOFLIP);
    }

