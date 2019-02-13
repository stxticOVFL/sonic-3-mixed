// Object ID: 0x09
// Object Name: AIZTreeBark.cpp

#include "AIZTreeBark.h"

typedef IMath Math;

void AIZTreeBark::Create() {
    Object::Create();
    Active = true;
    Priority = false;
    W = 16;
    H = 16;
    CurrentAnimation = 0;
    Frame = 0;
}

void AIZTreeBark::Render(int CamX, int CamY) {
    G->DrawSprite(Sprite, CurrentAnimation, Frame, X - CamX, Y - CamY, 0, IE_NOFLIP);
    }

