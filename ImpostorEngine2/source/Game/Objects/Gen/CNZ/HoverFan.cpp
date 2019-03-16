// Object ID: 0x46
// Object Name: HoverFan.cpp

#include "HoverFan.h"

typedef IMath Math;

void HoverFan::Create() {
    Object::Create();
    Active = true;
    Priority = true;
    W = 32;
    H = 32;
    Y += 28;
    CurrentAnimation = 2;
    BlowHeight = ((SubType & 0x0F) + 8) << 4;
    HaveBlock = false;
    Solid = false;
    Underwater = 0;
    AlwaysOn = true;
    OnOff = false;
    NeedsActivation = false;
    On = false;
    PlayingSound = false;
    Amount = ((SubType & 0x70) >> 4) + 1;
}

void HoverFan::Update() {
    bool Out = true;
    int Neck = 0;
    for (int i = 0; i < Scene->PlayerCount; i++)
{
        if (Scene->Players[i]->EZY >= Y - 24 && Scene->Players[i]->OnScreen) {
            Out = false;
        }

        if (Scene->Players[i]->Action == ActionType::Conveyor || Scene->Players[i]->Action == ActionType::Dead) continue;

        if (On) {
            Neck = Math::sinHex(Scene->Frame << 2) >> 13;
            if (Scene->Players[i]->EZX + 10 >= X - (Amount * 16) && Scene->Players[i]->EZX - 10 < X + (Amount * 16) && Scene->Players[i]->EZY < Y + 12 && Scene->Players[i]->EZY >= Y - BlowHeight - 0x30 + Neck) {
                InUse = true;
                Scene->Players[i]->SubY += (Y - BlowHeight - 0x30 + Neck - (Scene->Players[i]->SubY >> 16)) << 10;
                Scene->Players[i]->Ground = false;
                Scene->Players[i]->YSpeed = -0.7;
                Scene->Players[i]->Action = ActionType::Fan;
            }
            else {
                InUse = false;
            }
        }

    }
    if (On) {
        if (Sprite->Animations[CurrentAnimation].AnimationSpeed > 2) Frame += Sprite->Animations[CurrentAnimation].AnimationSpeed;
        else if (Sprite->Animations[CurrentAnimation].Frames[Frame / 0x100].Duration != 0) Frame += 0x100 / Sprite->Animations[CurrentAnimation].Frames[Frame / 0x100].Duration;

        if (Frame / 0x100 >= Sprite->Animations[CurrentAnimation].FrameCount - 1) {
            Frame = Sprite->Animations[CurrentAnimation].FrameToLoop * 0x100;
        }

    }

    if (OnScreen && InUse) {
        Sound::Loop(Sound::SFX_CARNIVAL_FAN, 0);
    }

    if (!Underwater) {
        if (Out) {
            if (OutX >= 0) X = Math::max(InitialX, X - 8);
            else X = Math::min(InitialX, X + 8);
            On = true;
        }
        else {
            if (OutX >= 0) X = Math::min(InitialX + OutX, X + 8);
            else X = Math::max(InitialX + OutX, X - 8);
            On = false;
        }
    }

    if (AlwaysOn) On = true;

    if (NeedsActivation) {
        On = false;
        if (Scene->LevelTriggerFlag & 1) On = true;

    }

    Out = false;
    Object::Update();
}

void HoverFan::Render(int CamX, int CamY) {
    if (HaveBlock) {
        G->DrawSprite(Scene->TileSprite, 0, 0x8B, 8 + X - CamX + (-16), 8 + Y - CamY + (-16), 0, IE_NOFLIP);
        G->DrawSprite(Scene->TileSprite, 0, 0x8C, 8 + X - CamX + (0), 8 + Y - CamY + (-16), 0, IE_NOFLIP);
        G->DrawSprite(Scene->TileSprite, 0, 0x8D, 8 + X - CamX + (-16), 8 + Y - CamY + (0), 0, IE_NOFLIP);
        G->DrawSprite(Scene->TileSprite, 0, 0x8E, 8 + X - CamX + (0), 8 + Y - CamY + (0), 0, IE_NOFLIP);
    }

    if (App->viewObjectCollision) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

    }

