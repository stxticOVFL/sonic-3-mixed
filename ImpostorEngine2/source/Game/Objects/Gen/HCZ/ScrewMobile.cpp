// Object ID: 0x9A
// Object Name: ScrewMobile.cpp

#include "ScrewMobile.h"

typedef IMath Math;

CONSTRUCTER ScrewMobile::ScrewMobile() {
}

void ScrewMobile::Create() {
    Enemy::Create();
    Active = true;
    Priority = false;
    W = 32;
    H = 32;
    int test;
    test = 0;
    CurrentAnimation = 0;
    HitCount = 8;
    CurrentAnimation = Sprite->FindAnimation("Mobile");
    State = BossState::ENTERING;
    Frame = 0;
    PropellorAnim = Sprite->FindAnimation("Propellor");
    RackAnim = Sprite->FindAnimation("Rack");
    PropellorFrame = 0;
    RackFrame = -1;
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
}

void ScrewMobile::DoExplosionDebris() {
    Scene->AddMovingSprite(Sprite, X, Y, CurrentAnimation + 3, 0, FlipX, false, -0x400, -0x400, 0x38);
    Scene->AddMovingSprite(Sprite, X, Y, CurrentAnimation + 3, 1, FlipX, false, 0x400, -0x400, 0x38);
    Scene->AddMovingSprite(Sprite, X, Y, CurrentAnimation + 3, 2, FlipX, false, -0x400, -0x400, 0x48);
    Scene->AddMovingSprite(Sprite, X, Y, CurrentAnimation + 3, 3, FlipX, false, 0x400, -0x400, 0x48);
    Object* Signpost = Scene->AddNewObject(Obj_Signpost, 0x00, X, Scene->CameraY - 64, false, false);
    Signpost->VisualLayer = VisualLayer;
}

int ScrewMobile::OnHit() {
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

void ScrewMobile::HandleDamage() {
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
            DoExplosionDebris();
            Active = false;
            App->Audio->FadeMusic(3.0);
        }
        XSpeed = 0;
        YSpeed = 0;
    }

}

void ScrewMobile::Update() {
    if (!isHeldDebugObject) {
        if (!Started) {
            App->Audio->PushMusic(Sound::SoundBank[0], true, Sound::Audio->LoopPoint[0]);
            App->Audio->PushMusic(Sound::SoundBank[0xF0], true, 0);
            Started = true;
        }

        switch (State) {
            case BossState::ENTERING:
            if (Scene->Player->X > InitialX - 0x60) {
                PlayerEntered = true;
            }

            if (PlayerEntered) {
                if (Y < InitialY + 0x80) {
                    Y += 2;
                }
                else {
                    State = BossState::MOVING;
                }
            }

            break;
            case BossState::MOVING:
            Swing_UpAndDown();
            break;
            case BossState::SUCC_TIME:
            break;
        }

        HandleDamage();
    }

    Object::Update();
}

void ScrewMobile::Render(int CamX, int CamY) {
    G->DrawSprite(this->Sprite, CurrentAnimation, Frame >> 8, this->X - CamX, this->Y - CamY, 0, this->FlipX ? IE_FLIPX : IE_NOFLIP);
    G->DrawSprite(this->Sprite, CurrentAnimation, (Frame >> 8) + 1, this->X - CamX, this->Y - CamY, 0, this->FlipX ? IE_FLIPX : IE_NOFLIP);
    if (RackFrame == -1) {
        G->DrawSprite(this->Sprite, CurrentAnimation, (Frame >> 8) + 2, this->X - CamX, this->Y - CamY, 0, this->FlipX ? IE_FLIPX : IE_NOFLIP);
    }
    else {
        G->DrawSprite(this->Sprite, RackAnim, RackFrame, this->X - CamX, this->Y - CamY, 0, this->FlipX ? IE_FLIPX : IE_NOFLIP);
    }
    G->DrawSprite(this->Sprite, PropellorAnim, PropellorFrame, this->X - CamX, this->Y - CamY, 0, this->FlipX ? IE_FLIPX : IE_NOFLIP);
    if (InvulnTimer > 0) G->DrawSprite(Scene->RobotnikSprite, 2, 0, X - CamX, Y - 48 - CamY, 0, !FlipX);
    else if (HitCount < 0) G->DrawSprite(Scene->RobotnikSprite, 3, 0, X - CamX, Y - 48 - CamY, 0, !FlipX);
    else G->DrawSprite(Scene->RobotnikSprite, 0, (Scene->Frame / 6) & 1, X - CamX, Y - 48 - CamY, 0, !FlipX);
    if (App->viewObjectCollision) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

    }

