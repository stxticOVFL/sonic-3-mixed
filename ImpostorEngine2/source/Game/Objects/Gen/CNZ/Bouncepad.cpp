// Object ID: 0x4B
// Object Name: Bouncepad.cpp

#include "Bouncepad.h"

typedef IMath Math;

void Bouncepad::Create() {
    Object::Create();
    Active = true;
    Priority = true;
    W = (SubType & 0xF0) << 1;
    H = 16;
    VisW = (SubType & 0xF0) << 1;
    VisH = 16;
}

int Bouncepad::OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data) {
    IPlayer* Player = Scene->Players[PlayerID];
    if (Player->Action == ActionType::Dead) {
        return 0;
    }

    Player->Ground = false;
    Player->XSpeed = FlipX ? -0x800 : 0x800;
    Player->YSpeed = FlipY ? 0x800 : -0x800;
    Player->InputAlarm = 0x0f;
    Player->Action = ActionType::Spring;
    Player->SpringFlip = 3;
    Sound::Play(Sound::SFX_PAD_BOUNCE);
    return 1;
}

void Bouncepad::Render(int CamX, int CamY) {
    if (App->viewObjectCollision) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

    }

