// Object ID: 0x33
// Object Name: Button.cpp

#include "Button.h"

typedef IMath Math;

void Button::Create() {
    Object::Create();
    Active = true;
    Priority = false;
    Permanent = (SubType >> 4 & 0x1);
    TriggerID = (SubType & 0xF);
    TriggerType = (SubType >> 6 & 0x1);
    CollisionType = (SubType >> 5 & 0x1);
    if (!CollisionType) Solid = true;
    else SolidTop = true;
    Scene->AddSelfToRegistry(this, "Solid");
    W = 32;
    H = 16;
    Rotation = 0;
    StartY = this->Y;
    CurrentAnimation = 15;
    Down = false;
    Pressed = false;
}

void Button::Update() {
    this->Down = Scene->Players[0]->Ground && Scene->Players[0]->LastObject == this;
    if (Down) {
        if (!Pressed) {
            Pressed = true;
            Sound::Play(Sound::SFX_SCORE_ADD);
            Scene->LevelTriggerFlag |= 1 << TriggerID;
            CollidingWithPlayer = true;
        }

    }

    Y = StartY + 4 + 4 * Down;
    Object::Update();
}

void Button::Render(int CamX, int CamY) {
    G->DrawSprite(Sprite, CurrentAnimation, Down, X - CamX, Y - 4 * Down - CamY, 0, IE_NOFLIP);
    }

int Button::OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data) {
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

