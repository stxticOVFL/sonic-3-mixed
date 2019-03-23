// Object ID: 0xFFFFFFFF
// Object Name: Signpost.cpp

#include "Signpost.h"

typedef IMath Math;

CONSTRUCTER Signpost::Signpost() {
    if (SaveGame::CurrentMode == 0) {
        BinIndex = LevelScene::LoadSpriteBin("Global/SignPost.bin");
    }
    else {
        BinIndex = LevelScene::LoadSpriteBin("Global/SignPost.bin");
    }
}

void Signpost::Create() {
    Object::Create();
    W = 48;
    H = 24;
    Active = true;
    Priority = true;
    CurrentAnimation = int(Scene->Players[0]->Character);
    CleanupInactiveObject = true;
    XSpeed = 0;
    YSpeed = 0;
    Frame = 0x00;
    Rot = 0;
    Speed = 0;
    Accel = 0;
    StopSpinning = false;
    Falling = true;
    StartResults = false;
    Timer = -1;
}

void Signpost::Update() {
    if (!isHeldDebugObject) {
        if (Falling) Gravity = 0xC;
        else Scene->Player->UnderwaterTimer = 1800;
        if (X + 24 >= Scene->CameraX + App->WIDTH || X - 24 <= Scene->CameraX) {
            if (Falling) {
                XSpeed = -XSpeed;
            }

        }

        for (int i = -16; i <= 8; i++)
{
            if (Scene->CollisionAt(X, Y + 24 + i) || Y + 24 + i >= Scene->CameraY + App->HEIGHT) {
                if (Falling) {
                    XSpeed = 0;
                    YSpeed = 0;
                    Falling = false;
                    Gravity = 0;
                    Speed = 0;
                    Timer = 60 * 3;
                    Accel = ((2 * 0x1000000) + (Rot & 0xFF0000)) / (Timer * Timer);
                    StopSpinning = true;
                    Y += i;
                    break;
                }

            }

        }
        if (StopSpinning) {
            if (Timer > 0) {
                Speed = Accel * Timer;
                Rot = Speed * Timer;
                Timer--;
                if (Timer == 0) StartResults = true;

            }

        }
        else {
            Speed = (2 * 0x1000000) / -60;
            Rot += Speed;
            Rot &= 0xFFFFFF;
        }
        if (StartResults) {
            XSpeed = 0;
            YSpeed = 0;
            App->Audio->RemoveMusic(Sound::SoundBank[0xFD]);
            Scene->DoResults();
            Timer = -1;
            StartResults = false;
        }

    }

    Object::Update();
}

void Signpost::Render(int CamX, int CamY) {
    int c = 0;
    int s = 0;
    int x = 0;
    int w = 0;
    Sprite = Scene->Objects2Sprite;
    G->DrawSprite(Sprite, 6, 2, X - CamX, Y - CamY, 0, IE_NOFLIP);
    c = Math::cosHex((Rot >> 16) + 0x80);
    s = Math::sinHex((Rot >> 16) + 0x80);
    x = (24 * c >> 16) + (-4 * s >> 16);
    w = (24 * c >> 16) + (4 * s >> 16);
    if (w - x > 0) G->DrawSpriteSized(Sprite, 6, 1, X - CamX + x + 4, Y - CamY + 22 + Sprite->Animations[6].Frames[1].OffY, 0, IE_NOFLIP, w - x, 30);

    x = (-24 * c >> 16) + (4 * s >> 16);
    w = (-24 * c >> 16) + (-4 * s >> 16);
    if (w - x > 0) G->DrawSpriteSized(Sprite, 6, 1, X - CamX + x + 4, Y - CamY + 22 + Sprite->Animations[6].Frames[1].OffY, 0, IE_NOFLIP, w - x, 30);

    x = (24 * c >> 16) + (4 * s >> 16);
    w = (-24 * c >> 16) + (4 * s >> 16);
    if (w - x > 0) G->DrawSpriteSized(Sprite, CurrentAnimation, Frame >> 8, X - CamX + x + 24, Y - CamY + 22 + Sprite->Animations[CurrentAnimation].Frames[Frame >> 8].OffY, 0, IE_NOFLIP, w - x, 30);

    x = (-24 * c >> 16) + (-4 * s >> 16);
    w = (24 * c >> 16) + (-4 * s >> 16);
    if (w - x > 0) G->DrawSpriteSized(Sprite, 5, Frame >> 8, X - CamX + x + 24, Y - CamY + 22 + Sprite->Animations[5].Frames[Frame >> 8].OffY, 0, IE_NOFLIP, w - x, 30);

    if (App->viewObjectCollision) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

    }

int Signpost::OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data) {
    if (Scene->Players[PlayerID]->Action != ActionType::Jumping) return 0;

    if (Scene->Players[PlayerID]->YSpeed > 0) return 0;

    if (YSpeed < 0) return 0;

    if (Falling) {
        YSpeed = -0x200;
        XSpeed = Scene->Players[PlayerID]->XSpeed;
        Scene->Score += 100;
    }

    return 1;
}

