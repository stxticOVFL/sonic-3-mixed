// Object ID: 0x9E
// Object Name: TunnelBotCutscene.cpp

#include "TunnelBotCutscene.h"

typedef IMath Math;

void TunnelBotCutscene::Create() {
    Enemy::Create();
    this->Active = true;
    this->Priority = false;
    this->W = 32;
    this->H = 32;
    this->CurrentAnimation = 13;
    HitCount = 0xFFFF;
    Sprite = LevelScene::LoadSpriteFromBin("MGZ/TunnelBot.bin", SaveGame::CurrentMode);
    this->Y += 1;
}

int TunnelBotCutscene::OnHit() {
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

void TunnelBotCutscene::HandleDamage() {
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
        }
        else {
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

        XSpeed = 0;
        YSpeed = 0;
    }

}

void TunnelBotCutscene::Update() {
    CheckDistanceToPlayers();
    if (PlayerXDistance <= 0x200) {
        Y--;
    }

    HandleDamage();
    Object::Update();
}

void TunnelBotCutscene::Render(int CamX, int CamY) {
    G->DrawSprite(this->Sprite, CurrentAnimation, Frame >> 8, this->X - CamX, this->Y - CamY, 0, this->FlipX ? IE_FLIPX : IE_NOFLIP);
    if (App->viewObjectCollision) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

    }

int TunnelBotCutscene::OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data) {
    IPlayer* Player = Scene->Players[PlayerID];
    if (Player == 0) {
        return false;
    }

    Player->YSpeed = -Player->YSpeed;
    Player->XSpeed = -Player->XSpeed;
    return true;
}

