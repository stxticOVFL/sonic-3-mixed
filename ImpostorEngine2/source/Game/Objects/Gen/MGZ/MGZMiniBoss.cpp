// Object ID: 0x9F
// Object Name: MGZMiniBoss.cpp

#include "MGZMiniBoss.h"

typedef IMath Math;

void MGZMiniBoss::Create() {
    Enemy::Create();
    this->Active = true;
    this->Priority = false;
    this->W = 64;
    this->H = 32;
    this->CurrentAnimation = 13;
    HitCount = 6;
    int i = 0;
    MainPalette[i++] = 0x000000;
    MainPalette[i++] = 0xEE8822;
    MainPalette[i++] = 0xCC6622;
    MainPalette[i++] = 0xAA4422;
    MainPalette[i++] = 0x662222;
    MainPalette[i++] = 0x442200;
    MainPalette[i++] = 0x222222;
    MainPalette[i++] = 0x66EE00;
    MainPalette[i++] = 0x66CC00;
    MainPalette[i++] = 0x448800;
    MainPalette[i++] = 0x224400;
    MainPalette[i++] = 0xEEEECC;
    MainPalette[i++] = 0xCCCCAA;
    MainPalette[i++] = 0xAAAA66;
    MainPalette[i++] = 0x666644;
    MainPalette[i++] = 0x444422;
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

int MGZMiniBoss::OnHit() {
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

void MGZMiniBoss::DoExplosionDebris() {
    Scene->AddMovingSprite(Sprite, X, Y, CurrentAnimation + 1, 0, FlipX, false, -0x400, -0x400, 0x38);
    Scene->AddMovingSprite(Sprite, X, Y, CurrentAnimation + 1, 1, FlipX, false, 0x400, -0x400, 0x38);
    Scene->AddMovingSprite(Sprite, X, Y, CurrentAnimation + 1, 2, FlipX, false, -0x400, -0x400, 0x48);
    Scene->AddMovingSprite(Sprite, X, Y, CurrentAnimation + 1, 3, FlipX, false, 0x400, -0x400, 0x48);
    Object* Signpost = Scene->AddNewObject(Obj_Signpost, 0x00, X, Scene->CameraY - 64, false, false);
    Signpost->VisualLayer = VisualLayer;
}

void MGZMiniBoss::HandleDamage() {
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

void MGZMiniBoss::Update() {
    HandleDamage();
    Object::Update();
}

void MGZMiniBoss::Render(int CamX, int CamY) {
    G->DrawSprite(this->Sprite, CurrentAnimation, Frame >> 8, this->X - CamX, this->Y - CamY, 0, this->FlipX ? IE_FLIPX : IE_NOFLIP);
    if (App->viewObjectCollision) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

    }

int MGZMiniBoss::OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data) {
    IPlayer* Player = Scene->Players[PlayerID];
    if (Player == 0) {
        return false;
    }

    Player->YSpeed = -Player->YSpeed;
    Player->XSpeed = -Player->XSpeed;
    return true;
}

