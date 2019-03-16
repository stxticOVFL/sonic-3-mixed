// Object ID: 0x9A
// Object Name: HCZBoss.cpp

#include "HCZBoss.h"

typedef IMath Math;

void HCZBoss::Create() {
    Enemy::Create();
    this->Active = true;
    this->Priority = false;
    this->W = 32;
    this->H = 32;
    this->CurrentAnimation = 0;
    HitCount = 8;
    int i = 0;
    MainPalette[i++] = 0x000000;
    MainPalette[i++] = 0xEEEEEE;
    MainPalette[i++] = 0xEEAA00;
    MainPalette[i++] = 0xEE6600;
    MainPalette[i++] = 0x660000;
    MainPalette[i++] = 0xEEEE00;
    MainPalette[i++] = 0x888800;
    MainPalette[i++] = 0xAA00CC;
    MainPalette[i++] = 0xEE8822;
    MainPalette[i++] = 0xCC4400;
    MainPalette[i++] = 0x660000;
    MainPalette[i++] = 0x002200;
    MainPalette[i++] = 0x8866CC;
    MainPalette[i++] = 0x4422AA;
    MainPalette[i++] = 0x222266;
    MainPalette[i++] = 0x444400;
    i = 0;
    HurtPalette[i++] = 0x000000;
    HurtPalette[i++] = 0xEEEEEE;
    HurtPalette[i++] = 0xF0F0F0;
    HurtPalette[i++] = 0xF0F0F0;
    HurtPalette[i++] = 0xF0F0F0;
    HurtPalette[i++] = 0xF0F0F0;
    HurtPalette[i++] = 0xF0F0F0;
    HurtPalette[i++] = 0xF0F0F0;
    HurtPalette[i++] = 0xF0F0F0;
    HurtPalette[i++] = 0xF0F0F0;
    HurtPalette[i++] = 0xF0F0F0;
    HurtPalette[i++] = 0xF0F0F0;
    HurtPalette[i++] = 0xF0F0F0;
    HurtPalette[i++] = 0xF0F0F0;
    HurtPalette[i++] = 0xF0F0F0;
    HurtPalette[i++] = 0xF0F0F0;
    this->Y += 1;
}

int HCZBoss::OnHit() {
    HitCount--;
    if (HitCount == 0) {
        Scene->StopTimer = true;
        Scene->Score += 1000;
        HitCount = -1;
        return 0;
    }

    InvulnTimer = 0x20;
    return 0;
}

void HCZBoss::HandleDamage() {
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

    if (InvulnTimer > 0) {
        if (InvulnTimer & 1) {
            Sprite->SetPalette(0x10, 16, MainPalette);
            Sprite->UpdatePalette();
        }
        else {
            Sprite->SetPalette(0x10, 16, HurtPalette);
            Sprite->UpdatePalette();
        }
    }

    if (HitCount < 0) {
        VisualLayer = 1;
        if (ExplosionTimer > 0) {
            if (ExplosionTimer % 3 == 0) {
                Scene->AddExplosion(5, false, X + Math::randRange(-W / 2, W / 2), Y + Math::randRange(-H / 2, H / 2), VisualLayer);
                Sound::Play(Sound::SFX_BOSSEXPLOSION);
            }

            ExplosionTimer--;
        }
        else {
            Active = false;
            App->Audio->FadeMusic(3.0);
        }
        XSpeed = 0;
        YSpeed = 0;
    }

}

void HCZBoss::Update() {
    if (!Started) {
        App->Audio->PushMusic(Sound::SoundBank[0], true, Sound::Audio->LoopPoint[0]);
        App->Audio->PushMusic(Sound::SoundBank[0xF0], true, 0);
        Started = true;
    }

    HandleDamage();
    Object::Update();
}

void HCZBoss::Render(int CamX, int CamY) {
    G->DrawSprite(this->Sprite, CurrentAnimation, Frame >> 8, this->X - CamX, this->Y - CamY, 0, this->FlipX ? IE_FLIPX : IE_NOFLIP);
    if (App->viewObjectCollision) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

    }

