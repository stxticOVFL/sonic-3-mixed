// Object ID: 0x8C
// Object Name: Bloominator.cpp

#include "Bloominator.h"

typedef IMath Math;

CONSTRUCTER Bloominator::Bloominator() {
    if (LevelScene::IsZoneCurrently("AIZ")) {
        BinIndex = LevelScene::LoadSpriteBin("AIZ/Tulipon.bin");
    }
    else {
        BinIndex = LevelScene::LoadSpriteBin("AIZ/Tulipon.bin");
    }
}

void Bloominator::Create() {
    Enemy::Create();
    Active = true;
    Priority = false;
    W = 32;
    H = 48;
    Frame = 0;
    HitCount = 1;
    switch (Scene->ZoneID) {
        case 1:
        Sprite->LinkPalette(Scene->TileSprite);
    }

    CurrentAnimation = Sprite->FindAnimation("Tulipon");
    CleanupInactiveObject = true;
    for (int i = 0; i < 2; i++)
{
        Children[i] = Scene->AddNewObject(Obj_BloominatorSpore, 0, 0, 0, false, false);
        Children[i]->Sprite = Sprite;
        Children[i]->CurrentAnimation = CurrentAnimation;
    }
    VisualLayer = 1;
}

void Bloominator::Update() {
    if (!isHeldDebugObject) {
        if (Frame == 31) {
            Children[0]->Timer = X << 8;
            Children[0]->Rotation = (Y - 16) << 8;
            Children[0]->X = X;
            Children[0]->Y = Y - 16;
            Children[0]->XSpeed = -0x100;
            Children[0]->YSpeed = -0x500;
            Sound::Play(Sound::SFX_SHOT);
        }
        else if (Frame == 62) {
            Children[1]->Timer = X << 8;
            Children[1]->Rotation = (Y - 16) << 8;
            Children[1]->X = X;
            Children[1]->Y = Y - 16;
            Children[1]->XSpeed = 0x100;
            Children[1]->YSpeed = -0x500;
            Sound::Play(Sound::SFX_SHOT);
        }
        else if (Frame == 182) {
            Frame = 0;
        }

        Frame++;
    }

    Object::Update();
}

int Bloominator::OnHit() {
    Children[0]->Active = false;
    Children[1]->Active = false;
    return OnDeath();
}

void Bloominator::Render(int CamX, int CamY) {
    int Subframe = 0;
    int Keyframe = Frame - 1;
    if (Keyframe >= 14 && Keyframe < 62 + 6) {
        if (Keyframe >= 14 && Keyframe < 14 + 11) {
            Subframe = 1;
        }
        else if (Keyframe >= 25 && Keyframe < 25 + 6) {
            Subframe = 2;
        }
        else if (Keyframe >= 31 && Keyframe < 31 + 6) {
            Subframe = 3;
        }
        else if (Keyframe >= 45 && Keyframe < 45 + 11) {
            Subframe = 1;
        }
        else if (Keyframe >= 56 && Keyframe < 56 + 6) {
            Subframe = 2;
        }
        else if (Keyframe >= 62 && Keyframe < 62 + 6) {
            Subframe = 3;
        }

    }

    G->DrawSprite(Sprite, CurrentAnimation, Subframe, X - CamX, Y - CamY, 0, IE_NOFLIP);
    if (DrawCollisions) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

    }

