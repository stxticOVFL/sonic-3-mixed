// Object ID: 0x51
// Object Name: FloatingPlatform.cpp

#include "FloatingPlatform.h"

typedef IMath Math;

void FloatingPlatform::Create() {
    Object::Create();
    Active = true;
    Priority = true;
    SolidTop = true;
    Scene->AddSelfToRegistry(this, "Solid");
    Timer = 0;
    LastX = X;
    LastY = Y;
    YS = 1 - (FlipX << 1);
    Vertical = false;
    RisingType = false;
    Rising = false;
    Moving = false;
    SizeIndex = (SubType >> 4) & 0x7;
    MoveType = (SubType & 0xF) - 0x8;
    BackupX = X;
    Amplitude = 0;
    if (SizeIndex == 0) {
        W = 64;
        H = 64;
    }
    else if (SizeIndex == 1) {
        W = 48;
        H = 24;
    }
    else if (SizeIndex == 2) {
        W = 64;
        H = 40;
    }

    if (MoveType > 0) {
        if (MoveType >= 4) {
            BackupX += 0x100;
        }

    }

    MoveType = (SubType & 0xF);
    if (MoveType == 1 || MoveType == 2) {
        Amplitude = 0x20 << MoveType;
    }
    else if (MoveType == 3 || MoveType == 4) {
        Amplitude = 0x08 << MoveType;
    }

    switch (Scene->ZoneID) {
        case 1:
        CurrentAnimation = 19;
        if (Scene->Act == 2) CurrentAnimation = 20;

        Frame = 0;
        break;
        case 2:
        CurrentAnimation = 14;
        break;
        case 6:
        CurrentAnimation = 14;
        break;
    }

}

void FloatingPlatform::Update() {
    if (MoveType == 0) {
        if (BeingStoodOn) {
            if (Timer < 0x40) Timer += 0x4;

        }
        else {
            if (Timer > 0x00) Timer -= 0x4;

        }
        LastY = Y;
        Y = InitialY - (Math::sinHex(Timer) >> 14);
    }
    else if (MoveType == 1 || MoveType == 2) {
        LastX = X;
        if (FlipX) X = InitialX + Amplitude / 2 - (Math::sinHex(Scene->Frame) >> (12 - MoveType));
        else X = InitialX + Amplitude / 2 + (Math::sinHex(Scene->Frame) >> (12 - MoveType));
        XSpeed = (X - LastX) << 8;
    }
    else if (MoveType == 3 || MoveType == 4) {
        LastY = Y;
        if (!FlipX) Y = InitialY - Amplitude / 2 - (Math::sinHex(Scene->Frame) >> (14 - MoveType));
        else Y = InitialY - Amplitude / 2 + (Math::sinHex(Scene->Frame) >> (14 - MoveType));
        if (CollidingWithPlayer) {
            if (Scene->Player->Action != ActionType::Dead && Scene->Player->EZY < Y - H / 2) {
                if (Scene->CollisionAt(Scene->Player->EZX - 9, Scene->Player->EZY - Scene->Player->H / 2 - 2, NULL, 2, Scene->Player)) {
                    Scene->Player->Die(false);
                }

                if (Scene->CollisionAt(Scene->Player->EZX + 9, Scene->Player->EZY - Scene->Player->H / 2 - 2, NULL, 2, Scene->Player)) {
                    Scene->Player->Die(false);
                }

            }

        }

    }
    else if (MoveType == 5 || MoveType == 6) {
        LastX = X;
        LastY = Y;
        if (FlipX ^ (MoveType == 6)) X = InitialX + 0x80 / 2 - (Math::sinHex(Scene->Frame) >> 10);
        else X = InitialX + 0x80 / 2 + (Math::sinHex(Scene->Frame) >> 10);
        if (!FlipX) Y = InitialY - 0x40 / 2 - (Math::sinHex(Scene->Frame) >> 11);
        else Y = InitialY - 0x40 / 2 + (Math::sinHex(Scene->Frame) >> 11);
        if (CollidingWithPlayer) {
            if (Scene->Player->Action != ActionType::Dead && Scene->Player->EZY < Y - H / 2) {
                if (Scene->CollisionAt(Scene->Player->EZX, Scene->Player->EZY - Scene->Player->H / 2 - 2, NULL, 2, Scene->Player)) {
                    Scene->Player->Die(false);
                }

            }

        }

        XSpeed = (X - LastX) << 8;
    }
    else if (MoveType == 7) {
        if (BeingStoodOn) Rising = true;

        LastY = Y;
        if (Rising && Y > InitialY - 0x140) {
            Y -= 1;
        }

        if (CollidingWithPlayer) {
            if (Scene->Player->Action != ActionType::Dead && Scene->Player->EZY < Y - H / 2) {
                if (Scene->CollisionAt(Scene->Player->EZX - 9, Scene->Player->EZY - Scene->Player->H / 2 - 2, NULL, 2, Scene->Player)) {
                    Scene->Player->Die(false);
                }

                if (Scene->CollisionAt(Scene->Player->EZX + 9, Scene->Player->EZY - Scene->Player->H / 2 - 2, NULL, 2, Scene->Player)) {
                    Scene->Player->Die(false);
                }

            }

        }

    }

    if (Moving) {
        if (!RisingType) {
            LastX = X;
            if (Vertical) Y = InitialY - 32 * Math::abs(YS) + (Math::cosHex(Scene->Frame + 1) * 32 * YS >> 16);
            else X = InitialX + 32 * Math::abs(YS) + (Math::cosHex(Scene->Frame + 1) * 32 * YS >> 16);
            XSpeed = (X - LastX) << 8;
        }

        if (Rising && Y > InitialY - 0x140) {
            Y -= 1;
        }

    }

    return;
    Object::Update();
}

void FloatingPlatform::Render(int CamX, int CamY) {
    int nX = X;
    int nY = Y;
    if (Moving) {
        if (!RisingType) {
            if (Vertical) nY = InitialY - 32 * Math::abs(YS) + (Math::cosHex(Scene->Frame + 0) * 32 * YS >> 16);
            else nX = InitialX + 32 * Math::abs(YS) + (Math::cosHex(Scene->Frame + 0) * 32 * YS >> 16);
        }

    }

    nX = LastX;
    nY = LastY;
    if (Scene->ZoneID == 1) {
        G->DrawSprite(Sprite, CurrentAnimation, 0, nX - CamX, nY - 2 - CamY, 0, IE_NOFLIP);
    }
    else if (Scene->ZoneID == 2) {
        G->DrawSprite(Sprite, CurrentAnimation, Frame >> 8, nX - CamX, nY - CamY, 0, IE_NOFLIP);
    }
    else if (Scene->ZoneID == 3) {
        G->DrawSprite(Sprite, 2, 0, nX - CamX, nY - 2 - CamY, 0, IE_NOFLIP);
    }
    else {
        G->DrawRectangle(nX - CamX - W / 2, nY - CamY - H / 2, W, H, 0xFF0000);
    }
    }

