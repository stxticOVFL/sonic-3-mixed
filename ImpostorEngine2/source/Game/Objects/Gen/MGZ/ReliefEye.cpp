// Object ID: 0xFFFFFFFF
// Object Name: ReliefEye.cpp

#include "ReliefEye.h"

typedef IMath Math;

void ReliefEye::Create() {
    Enemy::Create();
    Active = true;
    Priority = false;
    W = 16;
    H = 16;
    HitCount = 3;
    Timer = 0;
    Radius = 8;
    VisualLayer = 1;
    Boss = true;
}

void ReliefEye::Update() {
    HandleDamage();
    Object::Update();
}

int ReliefEye::OnHit() {
    InvulnTimer = 0x20;
    HitCount--;
    if (HitCount == 0) {
        HitCount = -1;
        return 0;
    }

    return 0;
}

void ReliefEye::HandleDamage() {
    if (HitCount > 0) {
        if (InvulnTimer > 0) {
            InvulnTimer -= 1;
            Invincible = true;
            Harmful = false;
        }
        else {
            Invincible = false;
            Harmful = true;
        }
    }

    if (HitCount < 0) {
        OnDeath();
    }

    XSpeed = 0;
    YSpeed = 0;
}

void ReliefEye::Render(int CamX, int CamY) {
    G->DrawSprite(Sprite, 3, 1, X - CamX, Y - CamY, 0, FlipX ? IE_FLIPX : IE_NOFLIP);
    }

