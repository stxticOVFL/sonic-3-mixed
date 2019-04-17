// Object ID: 0xFFFFFFFF
// Object Name: EggCapsuleButton.cpp

#include "EggCapsuleButton.h"

typedef IMath Math;

void EggCapsuleButton::Create() {
    Object::Create();
    Active = true;
    Priority = false;
    Solid = true;
    Scene->AddSelfToRegistry(this, "Solid");
    Sprite = LevelScene::LoadSpriteFromBin("Global/EggPrison.bin", SaveGame::CurrentMode);
    W = 32;
    H = 16;
    Rotation = 0;
    Down = false;
    Pressed = false;
    SwingCounter = 0;
}

void EggCapsuleButton::Update() {
    if (!Pressed) {
        for (int i = 0; i < Scene->PlayerCount; i++)
{
            this->Down = Scene->Players[i]->LastObject == this;
        }
    }

    if (Down) {
        if (!Pressed) {
            Pressed = true;
            Sound::Play(Sound::SFX_SCORE_ADD);
            CollidingWithPlayer = true;
            BounceOffShield = true;
        }

    }

    if (!FlipY) Y = InitialY + 7 * Down;

    if (FlipY) Y = InitialY - 7 * Down;

    Object::Update();
}

void EggCapsuleButton::Render(int CamX, int CamY) {
    if (!FlipY) G->DrawSprite(Sprite, CurrentAnimation, 0, X - CamX, Y - 7 * Down - CamY, 0, IE_NOFLIP);
    else if (FlipY) G->DrawSprite(Sprite, CurrentAnimation, 0, X - CamX, Y - 7 * Down - CamY, 0, IE_FLIPY);

    if (DrawCollisions) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawNoCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

    }

int EggCapsuleButton::OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data) {
    if (!FlipY) {
        if (HitFrom != CollideSide::TOP) {
            this->CollidingWithPlayer = false;
            return 0;
        }

        if (Scene->Players[PlayerID]->YSpeed <= 0) {
            this->CollidingWithPlayer = false;
            return 0;
        }

    }

    if (FlipY) {
        if (HitFrom != CollideSide::BOTTOM) {
            this->CollidingWithPlayer = false;
            return 0;
        }

        if (Scene->Players[PlayerID]->YSpeed >= 0) {
            this->CollidingWithPlayer = false;
            return 0;
        }

    }

    return 1;
}

