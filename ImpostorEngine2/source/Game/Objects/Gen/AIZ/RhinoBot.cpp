// Object ID: 0x8D
// Object Name: RhinoBot.cpp

#include "RhinoBot.h"

typedef IMath Math;

CONSTRUCTER RhinoBot::RhinoBot() {
    if (LevelScene::IsZoneCurrently("AIZ")) {
        BinIndex = LevelScene::LoadSpriteBin("AIZ/RhinoBot.bin");
        DustBinIndex = LevelScene::LoadSpriteBin("AIZ/RhinoBot Dust.bin");
    }
    else {
        BinIndex = LevelScene::LoadSpriteBin("AIZ/RhinoBot.bin");
        DustBinIndex = LevelScene::LoadSpriteBin("AIZ/RhinoBot Dust.bin");
    }
}

void RhinoBot::Create() {
    Enemy::Create();
    Active = true;
    Priority = false;
    W = 32;
    H = 32;
    VisW = 128;
    VisH = 32;
    Frame = 0;
    SubX = X << 16;
    Speed = 0;
    Acceleration = -0x10;
    HitCount = 1;
    DustSprite = LevelScene::GetSpriteFromBinIndex(DustBinIndex);
    CurrentAnimation = Sprite->FindAnimation("RhinoBot");
    CurrentDustAnimation = DustSprite->FindAnimation("RhinoBot Dust");
    switch (Scene->ZoneID) {
        case 1:
        Sprite->LinkPalette(Scene->TileSprite);
        DustSprite->LinkPalette(Scene->TileSprite);
        break;
        case 2:
        break;
        case 3:
        break;
        case 4:
        break;
        case 5:
        break;
        case 6:
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

    CleanupInactiveObject = true;
}

void RhinoBot::Update() {
    int DisX = 0;
    int DisY = 0;
    if (!isHeldDebugObject) {
        if (Speed == Math::sign(Acceleration) * 0x300) {
            Acceleration = -Acceleration;
        }

        if (Speed == 0 && Timer == -1 && Math::abs(Speed) < 0x400) {
            FlipX = !FlipX;
            if (FlipX) Acceleration = -0x10;
            else Acceleration = 0x10;
        }

        Speed += Acceleration;
        SubX += Speed << 8;
        X = SubX >> 16;
        if (Timer == -1 && Math::abs(Speed) < 0x400) {
            if (Math::sign(Speed) == Math::sign(Acceleration)) {
                Frame = 0;
                if (Math::abs(Speed) < 0x80) {
                    Frame = 3;
                }

                if (Math::abs(Speed) < 0x40) {
                    Frame = 1;
                }

            }
            else {
                Frame = 1;
                if (Math::abs(Speed) < 0x280) {
                    Frame = 2;
                }

            }
            for (int p = 0; p < Scene->PlayerCount; p++)
{
                DisX = (Scene->Players[p]->EZX - X) * Math::sign(Speed);
                DisY = Math::abs(Scene->Players[p]->EZY - Y);
                if (DisX < 96 && DisX > 0 && DisY <= 32) {
                    Timer = 24;
                    Speed = 0;
                    Acceleration = 0;
                    Frame = 0;
                }

            }
        }

        if (Timer == 0) {
            if (FlipX) Speed = -0x400;
            else Speed = 0x400;
            Frame = 0;
            Priority = true;
        }

        int Y1 = Y;
        int Y2 = Y;
        for (int y = Y + 8; y < Y + 32; y++)
{
            if (Scene->CollisionAt(X - 8, y)) {
                Y1 = y;
                break;
            }

        }
        for (int y = Y + 8; y < Y + 32; y++)
{
            if (Scene->CollisionAt(X + 8, y)) {
                Y2 = y;
                break;
            }

        }
        if (Y1 < Y2 && Y1 > Y + 8) {
            Y = Y1 - 16;
        }
        else if (Y2 > Y + 8) {
            Y = Y2 - 16;
        }

        if (Y1 >= Y + 30 || Y1 == Y || Scene->CollisionAt(X - 8 - 1, Y)) {
            Acceleration = 0x10;
            Speed = 0x10;
            Timer = -1;
            SubX += 0x10000;
            FlipX = false;
            Priority = false;
            while (!Scene->CollisionAt((SubX >> 16) - 8 - 1, Y + 20)) SubX += 0x10000;

            X = (SubX >> 16);
        }

        if (Y2 >= Y + 30 || Y2 == Y || Scene->CollisionAt(X + 8 + 1, Y)) {
            Acceleration = -0x10;
            Speed = -0x10;
            Timer = -1;
            SubX -= 0x10000;
            FlipX = true;
            Priority = false;
            while (!Scene->CollisionAt((SubX >> 16) + 8 + 1, Y + 20)) SubX -= 0x10000;

            X = (SubX >> 16);
        }

        if (Timer >= 0) {
            Timer--;
        }

    }

    Object::Update();
}

void RhinoBot::Render(int CamX, int CamY) {
    int Flip = 1;
    if (FlipX) Flip = -1;

    if (Frame == 3) {
        Flip = -Flip;
    }

    G->DrawSprite(Sprite, CurrentAnimation, Frame, X - CamX, Y - CamY, 0, Flip > 0);
    if (Frame == 2) {
        G->DrawSprite(DustSprite, CurrentDustAnimation, ((Scene->Frame / 3) & 3), X - CamX + Flip * 14, Y - CamY + 1, 0, Flip > 0);
    }

    if (Timer != -1) {
        G->DrawSprite(DustSprite, CurrentDustAnimation, ((Scene->Frame / 3) & 3), X - CamX, Y - CamY + 1, 0, Flip > 0);
    }

    if (DrawCollisions) {
        G->SetDrawAlpha(0x80);
        if (Frame == 2) {
            G->DrawRectangle(X - (W / 2) - CamX + Flip * 14, Y - (H / 2) - CamY + 1, W, H, DrawCollisionsColor);
        }
        else {
            G->DrawRectangle(X - CamX, Y - CamY, W, H, DrawCollisionsColor);
        }
        G->SetDrawAlpha(0xFF);
    }

    }

