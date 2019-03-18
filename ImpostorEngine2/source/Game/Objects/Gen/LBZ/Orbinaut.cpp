// Object ID: 0xC0
// Object Name: Orbinaut.cpp

#include "Orbinaut.h"

typedef IMath Math;

void Orbinaut::Create() {
    Enemy::Create();
    Active = true;
    Priority = false;
    W = 32;
    H = 32;
    for (int i = 0; i < 4; i++)
{
        Orbs[i] = Scene->AddNewObject(Obj_StarPointerOrbs, i, X, Y, FlipX, false);
        Orbs[i]->CurrentAnimation = CurrentAnimation;
        OrbOffsets[i] = i * 90;
    }
    RotAngle = 0;
    TurnSpeed = 0.01;
}

int Orbinaut::OnHit() {
    Orbs[0]->Active = false;
    Orbs[1]->Active = false;
    Orbs[2]->Active = false;
    Orbs[3]->Active = false;
    return OnDeath();
}

void Orbinaut::Update() {
    for (int i = 0; i < 4; i++)
{
        RotAngle = 0;
        RotAngle += OrbOffsets[i];
        RotAngle += TurnSpeed;
        IApp::Print(0, "%d %d", RotAngle, sin(RotAngle));
        Orbs[i]->X = sin(RotAngle) * 20 + X;
        Orbs[i]->Y = cos(RotAngle) * 20 + Y;
        OrbOffsets[i] = RotAngle;
    }
    X -= 0.01;
    Object::Update();
}

void Orbinaut::Render(int CamX, int CamY) {
    if (DrawCollisions) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - CamX, Y - CamY, W, H, DrawCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

    G->DrawSprite(Sprite, CurrentAnimation, Frame >> 8, X - CamX, Y - CamY, 0, FlipX ? IE_FLIPX : IE_NOFLIP);
    }

