// Object ID: 0xFFFFFFFF
// Object Name: MGZHeadTrigger_Eye.cpp

#include "MGZHeadTrigger_Eye.h"

typedef IMath Math;

void MGZHeadTrigger_Eye::Create() {
    Enemy::Create();
    Active = true;
    Priority = false;
    W = 16;
    H = 16;
    HitCount = 3;
    Boss = true;
    Timer = 0;
    Radius = 8;
    VisualLayer = 1;
}

void MGZHeadTrigger_Eye::Update() {
    Invincible = false;
    Harmful = true;
    if (Timer > 0) {
        Invincible = true;
        Harmful = false;
        Timer--;
    }

    Object::Update();
}

int MGZHeadTrigger_Eye::OnHit() {
    Timer = 0x20;
    HitCount -= 1;
    if (HitCount == 0) {
        HitCount = -1;
        return OnDeath();
    }

    return 0;
}

int MGZHeadTrigger_Eye::OnDeath() {
    Scene->LevelTriggerFlag = (SubType + 1);
    return Enemy::OnDeath();
}

void MGZHeadTrigger_Eye::Render(int CamX, int CamY) {
    G->DrawSprite(Sprite, 3, 1, X - CamX, Y - CamY, 0, FlipX ? IE_FLIPX : IE_NOFLIP);
    }

