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
    Invincible = true;
    Harmful = false;
    HitCount--;
    if (HitCount == 0) {
        Scene->LevelTriggerFlag |= 1 << SubType;
        App->Print(0, "SubType %d", SubType);
        return OnDeath();
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

}

void ReliefEye::Render(int CamX, int CamY) {
    if (InvulnTimer > 0 && (InvulnTimer & 1)) return;

    G->DrawSprite(Sprite, 3, 1, X - CamX, Y - CamY, 0, FlipX ? IE_FLIPX : IE_NOFLIP);
    if (App->viewObjectCollision) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

    }

