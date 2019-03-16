// Object ID: 0xFFFFFFFF
// Object Name: BatbrightParts.cpp

#include "BatbrightParts.h"

typedef IMath Math;

void BatbrightParts::Create() {
    Enemy::Create();
    Active = true;
    Priority = true;
    CleanupInactiveObject = true;
    IsBodyExtension = true;
    W = 16;
    H = 16;
    VisW = 16;
    VisH = 16;
    Gravity = 0;
    Frame = 0;
    IsLight = false;
    AnimationData[0] = 0;
    AnimationData[1] = 29;
    AnimationData[2] = 1;
    AnimationData[3] = 2;
    AnimationData[4] = 0;
    AnimationData[5] = 1;
    AnimationData[6] = 1;
    AnimationData[7] = 2;
    AnimationData[8] = 0;
    AnimationData[9] = 14;
    AnimationData[10] = 1;
    AnimationData[11] = 2;
    AnimationData[12] = -4;
    AnimationData[13] = 0;
    VisualLayer = 1;
}

void BatbrightParts::Update() {
    MoveWithParent();
    IsLight = (CurrentAnimation == 37);
    if (!IsLight) {
        Y += 3;
        Frame = 1;
    }
    else if (IsLight) {
        DelayedAnimationProgress(AnimationData);
    }

    Object::Update();
}

void BatbrightParts::Render(int CamX, int CamY) {
    G->DrawSprite(Sprite, CurrentAnimation, Frame, X - CamX, Y - CamY, 0, IE_NOFLIP);
    if (App->viewObjectCollision) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

    }

