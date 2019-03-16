// Object ID: 0x36
// Object Name: BreakBar.cpp

#include "BreakBar.h"

typedef IMath Math;

void BreakBar::Create() {
    Object::Create();
    Active = true;
    Priority = false;
    W = 8;
    H = ((SubType & 0x30) << 1) + 64;
    CurrentAnimation = 9;
    Broken = false;
    Horizontal = !!(SubType & 0x80);
    Delay = (SubType & 0xF) * 60;
    PlayerTouched = false;
}

void BreakBar::Update() {
    if (!Broken) {
        for (int i = 0; i < Scene->PlayerCount; i++)
{
            if (Broken) {
                Scene->Players[i]->Action = ActionType::InStream;
            }

            if (Scene->Players[i]->EZY < Y - H / 2) {
                continue;
            }

            if (Scene->Players[i]->EZY > Y + H / 2) {
                continue;
            }

            if (Scene->Players[i]->EZX > X + 64) {
                continue;
            }

            if (Scene->Players[i]->Action == ActionType::Hurt || Scene->Players[i]->Action == ActionType::Dead) continue;

            if (Scene->Players[i]->EZX > X + 20 && Scene->Players[i]->Action == ActionType::InStream) {
                Scene->Players[i]->Action = ActionType::InStreamGrab;
                Scene->Players[i]->EZX = X;
                Scene->Players[i]->XSpeed = 0;
                if (i == 0) Scene->CameraX += 20;

                PlayerTouched = true;
            }

            if (Scene->Players[i]->Action == ActionType::InStreamGrab && Scene->Players[i]->InputJump && i == 0) {
                Scene->Players[i]->Action = ActionType::InStream;
                Scene->Players[i]->EZX = X + 20;
                Break();
            }

        }
    }

    if (PlayerTouched) {
        Delay--;
        if (Delay == 0) {
            for (int i = 0; i < Scene->PlayerCount; i++)
{
                if (Scene->Players[i]->Action == ActionType::InStreamGrab && Scene->Players[i]->EZX == X) {
                    Scene->Players[i]->Action = ActionType::InStream;
                    Scene->Players[i]->EZX = X + 20;
                }

            }
            Break();
        }

    }

    Object::Update();
}

void BreakBar::Break() {
    if (Broken) return;

    Broken = true;
    Sound::Play(Sound::SFX_COLLAPSE);
    int hold = 0;
    for (int i = -H / 2 + 12; i < H / 2 - 4; i += 8)
{
        hold = Math::abs(i) / 4;
        Scene->AddMovingSprite(Sprite, X, Y + i, CurrentAnimation, 1, false, false, 0x400, 0x0, 0x8, 180, hold);
    }
    hold += 2;
    Scene->AddMovingSprite(Sprite, X, Y - H / 2 + 4, CurrentAnimation, 0, false, false, 0x400, -0x8, 0x8, 180, hold);
    Scene->AddMovingSprite(Sprite, X, Y + H / 2 - 4, CurrentAnimation, 2, false, false, 0x400, 0x8, 0x8, 180, hold);
    Active = false;
}

void BreakBar::Render(int CamX, int CamY) {
    if (Broken) return;

    G->DrawSprite(Sprite, CurrentAnimation, 0, X - CamX, Y - CamY - H / 2 + 4, 0, IE_NOFLIP);
    for (int i = -H / 2 + 12; i < H / 2 - 4; i += 8)
{
        G->DrawSprite(Sprite, CurrentAnimation, 1, X - CamX, Y - CamY + i, 0, IE_NOFLIP);
    }
    G->DrawSprite(Sprite, CurrentAnimation, 2, X - CamX, Y - CamY + H / 2 - 4, 0, IE_NOFLIP);
    if (App->viewObjectCollision) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

    }

