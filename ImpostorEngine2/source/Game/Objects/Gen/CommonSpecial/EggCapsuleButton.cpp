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
    W = 32;
    H = 16;
    Rotation = 0;
    Down = false;
    Pressed = false;
    SwingCounter = 0;
}

void EggCapsuleButton::Update() {
    if (!Pressed) this->Down = Scene->Players[0]->Ground && Scene->Players[0]->LastObject == this;

    if (Down) {
        if (!Pressed) {
            Pressed = true;
            Sound::Play(Sound::SFX_SCORE_ADD);
            CollidingWithPlayer = true;
            BounceOffShield = true;
        }

    }

    Y = InitialY + 7 * Down;
    Object::Update();
}

void EggCapsuleButton::Render(int CamX, int CamY) {
    G->DrawSprite(Sprite, CurrentAnimation, 0, X - CamX, Y - 7 * Down - CamY, 0, IE_NOFLIP);
    }

int EggCapsuleButton::OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data) {
    if (HitFrom != CollideSide::TOP) {
        this->CollidingWithPlayer = false;
        return 0;
    }

    if (Scene->Players[PlayerID]->YSpeed <= 0) {
        this->CollidingWithPlayer = false;
        return 0;
    }

    return 1;
}

