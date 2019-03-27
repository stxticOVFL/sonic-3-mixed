// Object ID: 0x51
// Object Name: FloatingPlatform.cpp

#include "FloatingPlatform.h"

typedef IMath Math;

CONSTRUCTER FloatingPlatform::FloatingPlatform() {
    if (LevelScene::IsZoneCurrently("AIZ")) {
        Act1BinIndex = LevelScene::LoadSpriteBin("AIZ/Floating Platform.bin");
        Act2BinIndex = LevelScene::LoadSpriteBin("AIZ/Floating Platform 2.bin");
        BinIndex = Act1BinIndex;
    }
    else if (LevelScene::IsZoneCurrently("HCZ")) {
        BinIndex = LevelScene::LoadSpriteBin("HCZ/Platform.bin");
    }
    else if (LevelScene::IsZoneCurrently("MGZ")) {
        BinIndex = LevelScene::LoadSpriteBin("MGZ/Floating Platform.bin");
    }
    else if (LevelScene::IsZoneCurrently("CNZ")) {
        BinIndex = LevelScene::LoadSpriteBin("CNZ/Rising Platform.bin");
    }
    else if (LevelScene::IsZoneCurrently("ICZ")) {
        BinIndex = LevelScene::LoadSpriteBin("ICZ/Platforms.bin");
    }
    else if (LevelScene::IsZoneCurrently("LBZ")) {
        BinIndex = LevelScene::LoadSpriteBin("LBZ/Floating Platform.bin");
    }
    else {
        BinIndex = LevelScene::LoadSpriteBin("AIZ/Floating Platform.bin");
        Act1BinIndex = BinIndex;
        Act2BinIndex = BinIndex;
    }
}

void FloatingPlatform::Create() {
    Object::Create();
    Active = true;
    Priority = true;
    DoDeform = true;
    IsFloatingPlatform = true;
    SolidTop = true;
    Scene->AddSelfToRegistry(this, "Solid");
    Outliner = Scene->AddNewObject(Obj_PlatformOutliner, 0, X, Y, false, false);
    Outliner->Parent = this;
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
        if (Scene->Act == 1) {
            BinIndex = Act1BinIndex;
            CurrentAnimation = Sprite->FindAnimation("Floating Platform");
            Sprite->LinkPalette(Scene->TileSprite);
        }
        else if (Scene->Act == 2) {
            BinIndex = Act2BinIndex;
            Sprite = LevelScene::GetSpriteFromBinIndex(BinIndex);
            Sprite->LinkPalette(Scene->TileSprite);
            CurrentAnimation = Sprite->FindAnimation("Floating Platform 2");
        }

        Frame = 0;
        break;
        case 2:
        CurrentAnimation = Sprite->FindAnimation("Main");
        break;
        case 3:
        CurrentAnimation = Sprite->FindAnimation("Floating Platform");
        break;
        case 4:
        CurrentAnimation = Sprite->FindAnimation("Rising Platform");
        break;
        case 5:
        CurrentAnimation = Sprite->FindAnimation("Platforms");
        Sprite->LinkPalette(Scene->TileSprite);
        break;
        case 6:
        CurrentAnimation = Sprite->FindAnimation("Floating Platform");
        break;
        case 7:
        break;
        case 8:
        break;
        case 9:
        break;
        case 10:
        break;
        case 11:
        break;
        case 12:
        break;
        case 13:
        break;
        case 14:
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
        if (BeingStoodOn) {
            Rising = true;
        }

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
            if (Vertical) {
                Y = InitialY - 32 * Math::abs(YS) + (Math::cosHex(Scene->Frame + 1) * 32 * YS >> 16);
            }
            else {
                X = InitialX + 32 * Math::abs(YS) + (Math::cosHex(Scene->Frame + 1) * 32 * YS >> 16);
            }
            XSpeed = (X - LastX) << 8;
        }

        if (Rising && Y > InitialY - 0x140) {
            Y -= 1;
        }

    }

    if (!Scene->maxLayer && !isHeldDebugObject) {
        int32_t AnimCount = Sprite->AnimCount;
        if (Scene->ZoneID == 3) {
            Outliner->W = Sprite->Animations[CurrentAnimation % AnimCount].Frames[0].W;
            Outliner->H = Sprite->Animations[CurrentAnimation % AnimCount].Frames[0].H;
        }
        else if (Scene->ZoneID == 2) {
            int32_t FrameCount = Sprite->Animations[CurrentAnimation % AnimCount].FrameCount;
            int32_t CaculatedFrame = Frame >> 8;
            if (CaculatedFrame >= FrameCount) {
                CaculatedFrame = Frame;
            }

            Outliner->W = Sprite->Animations[CurrentAnimation % AnimCount].Frames[CaculatedFrame % FrameCount].W;
            Outliner->H = Sprite->Animations[CurrentAnimation % AnimCount].Frames[CaculatedFrame % FrameCount].H;
        }
        else {
            Outliner->W = Sprite->Animations[CurrentAnimation % AnimCount].Frames[Frame].W;
            Outliner->H = Sprite->Animations[CurrentAnimation % AnimCount].Frames[Frame].H;
        }
        Outliner->Visible = true;
    }
    else {
        Outliner->Visible = false;
    }
    return;
    Object::Update();
}

void FloatingPlatform::Render(int CamX, int CamY) {
    int nX = X;
    int nY = Y;
    if (Moving) {
        if (!RisingType) {
            if (Vertical) {
                nY = InitialY - 32 * Math::abs(YS) + (Math::cosHex(Scene->Frame + 0) * 32 * YS >> 16);
            }
            else {
                nX = InitialX + 32 * Math::abs(YS) + (Math::cosHex(Scene->Frame + 0) * 32 * YS >> 16);
            }
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
        G->DrawSprite(Sprite, CurrentAnimation, 0, nX - CamX, nY - 2 - CamY, 0, IE_NOFLIP);
    }
    else {
        G->DrawRectangle(nX - CamX - W / 2, nY - CamY - H / 2, W, H, 0xFF0000);
        if (App->viewObjectCollision) {
            G->SetDrawAlpha(0x80);
            G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
            G->SetDrawAlpha(0xFF);
        }

    }
    }

