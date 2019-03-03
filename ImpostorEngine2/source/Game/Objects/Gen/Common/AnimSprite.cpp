// Object ID: 0x30
// Object Name: AnimSprite.cpp

#include "AnimSprite.h"

typedef IMath Math;

void AnimSprite::Create() {
    Object::Create();
    Active = true;
    switch (Scene->ZoneID) {
        case 1:
        CurrentAnimation = 2;
        break;
    }

    switch (SubType) {
        case 0:
        {
            FrameStart = 0;
            FrameCount = 5;
            FrameLength = 4;
            break;
        }
        case 1:
        {
            FrameStart = 5;
            FrameCount = 4;
            FrameLength = 4;
            break;
        }
    }

}

void AnimSprite::Update() {
    Frame = FrameStart + (Scene->Frame / FrameLength) % FrameCount;
    Object::Update();
}

void AnimSprite::Render(int CamX, int CamY) {
    if (CurrentAnimation == -1) return;

    if (Scene->ZoneID == 1) {
        if (Y + 16 >= Scene->VisualWaterLevel) return;

    }

    G->DrawSprite(Sprite, CurrentAnimation, Frame, X - CamX, Y - CamY, 0, FlipX | FlipY << 1);
    }

