// Object ID: 0x8E
// Object Name: MonkeyDude.cpp

#include "MonkeyDude.h"

typedef IMath Math;

CONSTRUCTER MonkeyDude::MonkeyDude() {
    if (LevelScene::IsZoneCurrently("AIZ")) {
        BinIndex = LevelScene::LoadSpriteBin("AIZ/Monkey Dude.bin");
    }
    else {
        BinIndex = LevelScene::LoadSpriteBin("AIZ/Monkey Dude.bin");
    }
}

void MonkeyDude::Create() {
    Enemy::Create();
    Active = true;
    Priority = false;
    W = 32;
    H = 32;
    VisW = 64;
    VisH = 64;
    CurrentAnimation = Sprite->FindAnimation("MonkeyBro");
    CleanupInactiveObject = true;
    if (LevelScene::IsZoneCurrently("AIZ")) {
        Sprite->LinkPalette(Scene->TileSprite);
    }

    Children = Scene->AddNewObject(Obj_MonkeyDudeCoconut, 0, 0, 0, false, false);
    Children->Sprite = Sprite;
    Children->CurrentAnimation = CurrentAnimation;
    HasCoconut = true;
    Flip = 1;
    if (FlipX) {
        Flip = -1;
    }

    SubX = 0;
    Frame = 0;
    HitCount = 1;
    frame_face = 0;
    frame_hand = 0;
    frame_arm = 0;
    VisualLayer = 1;
}

void MonkeyDude::Update() {
    frame_face = (frame_face + 1) & 0xF;
    frame_hand = (frame_hand + 1) % (112 * 2);
    if (frame_hand % (64 + 48) >= 64) {
        if (frame_hand % 224 < 112 && (frame_hand & 0xF) == 8) Y += 8;
        else if (frame_hand % 224 >= 112 && (frame_hand & 0xF) == 8) Y -= 8;

    }

    frame_arm = (frame_arm + 1) & 0x7F;
    if (!isHeldDebugObject) {
        if (HasCoconut) {
            if ((Scene->Player->EZX < X - 16 && Scene->Player->EZX > X - 0x80 && Flip > 0) || (Scene->Player->EZX > X + 16 && Scene->Player->EZX < X + 0x80 && Flip < 0)) {
                int final_x = 0;
                int final_y = 0;
                int angle = 0;
                int offset = 1;
                for (int i = 0; i < 5; i++)
{
                    final_x = X + Flip * -10;
                    final_y = Y - 2 - (frame_face / 8) * 2 * offset;
                    angle = ((Math::sinHex((frame_arm - i * 4) * 2) * 0x2A) >> 16) - 0x15;
                    final_x -= Flip * (Math::cosHex(angle) * i * 8) >> 16;
                    final_y -= (Math::sinHex(angle) * i * 8) >> 16;
                }
                Children->X = final_x;
                Children->Y = final_y;
                Children->XSpeed = -0x200 * Flip;
                Children->YSpeed = -0x400;
                Sound::Play(Sound::SFX_DROP);
                HasCoconut = false;
            }

        }

    }

    Object::Update();
}

int MonkeyDude::OnLeaveScreen() {
    HasCoconut = true;
    return 0;
}

int MonkeyDude::OnHit() {
    Children->Active = false;
    return OnDeath();
}

void MonkeyDude::Render(int CamX, int CamY) {
    int final_x = 0;
    int final_y = 0;
    int angle = 0;
    int offset = 1;
    int f = 0;
    if (frame_hand % (64 + 48) >= 64) {
        offset = 0;
    }

    for (int i = 0; i < 5; i++)
{
        final_x = X - CamX + Flip * -10;
        final_y = Y - CamY - 2 - (frame_face / 8) * 2 * offset;
        angle = ((Math::sinHex((frame_arm - i * 4) * 2) * 0x2A) >> 16) - 0x15;
        final_x -= Flip * (Math::cosHex(angle) * i * 8) >> 16;
        final_y -= (Math::sinHex(angle) * i * 8) >> 16;
        G->DrawSprite(Sprite, CurrentAnimation, 3 + (i == 4 ? 1 : 0), final_x - 4, final_y - 4, 0, IE_NOFLIP);
        if (App->viewObjectCollision) {
            G->SetDrawAlpha(0x80);
            G->DrawRectangle(final_x - 4, final_y - 4, W / 2, H / 2, DrawNoCollisionsColor);
            G->SetDrawAlpha(0xFF);
        }

        if (HasCoconut && i == 4) {
            G->DrawSprite(Sprite, CurrentAnimation, 6, final_x - 4, final_y - 4, 0, IE_NOFLIP);
            if (App->viewObjectCollision) {
                G->SetDrawAlpha(0x80);
                G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
                G->SetDrawAlpha(0xFF);
            }

        }

    }
    if (frame_hand % (64 + 48) >= 64) {
        f = ((frame_hand / 8) % 2) * 2;
        if (frame_hand % 224 < 112) {
            f = 2 - f;
        }

        G->DrawSprite(Sprite, CurrentAnimation, f, X - CamX, Y - CamY, 0, FlipX);
        if (App->viewObjectCollision) {
            G->SetDrawAlpha(0x80);
            G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
            G->SetDrawAlpha(0xFF);
        }

    }
    else {
        G->DrawSprite(Sprite, CurrentAnimation, frame_face / 8, X - CamX, Y - CamY, 0, FlipX);
        if (App->viewObjectCollision) {
            G->SetDrawAlpha(0x80);
            G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
            G->SetDrawAlpha(0xFF);
        }

    }
    }

