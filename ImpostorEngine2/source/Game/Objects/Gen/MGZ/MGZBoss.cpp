// Object ID: 0xA1
// Object Name: MGZBoss.cpp

#include "MGZBoss.h"

typedef IMath Math;

void MGZBoss::Create() {
    Enemy::Create();
    this->Active = true;
    this->Priority = false;
    this->W = 32;
    this->H = 32;
    this->CurrentAnimation = 16;
    HitCount = 8;
    this->Y += 1;
}

int MGZBoss::OnHit() {
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

void MGZBoss::DoExplosionDebris() {
    Scene->AddMovingSprite(Sprite, X, Y, CurrentAnimation + 1, 0, FlipX, false, -0x400, -0x400, 0x38);
    Scene->AddMovingSprite(Sprite, X, Y, CurrentAnimation + 1, 1, FlipX, false, 0x400, -0x400, 0x38);
    Scene->AddMovingSprite(Sprite, X, Y, CurrentAnimation + 1, 2, FlipX, false, -0x400, -0x400, 0x48);
    Scene->AddMovingSprite(Sprite, X, Y, CurrentAnimation + 1, 3, FlipX, false, 0x400, -0x400, 0x48);
    Object* Signpost = Scene->AddNewObject(Obj_Signpost, 0x00, X, Scene->CameraY - 64, false, false);
    Signpost->VisualLayer = VisualLayer;
}

void MGZBoss::HandleDamage() {
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

void MGZBoss::Update() {
    HandleDamage();
    Object::Update();
}

void MGZBoss::Render(int CamX, int CamY) {
    G->DrawSprite(this->Sprite, CurrentAnimation, Frame >> 8, this->X - CamX, this->Y - CamY, 0, this->FlipX ? IE_FLIPX : IE_NOFLIP);
    if (App->viewObjectCollision) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

    }

int MGZBoss::OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data) {
    IPlayer* Player = Scene->Players[PlayerID];
    if (Player == 0) {
        return false;
    }

    Player->YSpeed = -Player->YSpeed;
    Player->XSpeed = -Player->XSpeed;
    return true;
}

