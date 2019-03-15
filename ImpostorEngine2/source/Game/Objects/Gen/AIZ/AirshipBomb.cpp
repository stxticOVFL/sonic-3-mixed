// Object ID: 0xFFFFFFFF
// Object Name: AirshipBomb.cpp

#include "AirshipBomb.h"

typedef IMath Math;

void AirshipBomb::Create() {
    Enemy::Create();
    Active = true;
    Priority = true;
    W = 24;
    H = 32;
    Sprite = Scene->SpriteMapIDs[0x90];
    CurrentAnimation = 1;
    Gravity = 0x70;
    X = InitialX + Scene->CameraX;
    Y = InitialY + Scene->CameraY;
    VisualLayer = 1;
    Harmful = false;
    Invincible = true;
    WeY = InitialY << 16;
    Timer = 6;
}

void AirshipBomb::Update() {
    X = Scene->Signal[6] + InitialX + Scene->CameraX;
    Y = Scene->Signal[7] + (WeY >> 16) + Scene->CameraY;
    if (WeY < 0) {
        WeY += 2 << 16;
    }
    else if (Timer > 0) {
        Timer--;
        if (Timer == 0) Sound::Play(Sound::SFX_DROP);

    }
    else {
        YSpeed += 0x20;
        WeY += YSpeed << 8;
    }
    if (Scene->CollisionAt(X, Y + H / 2)) {
        Sound::Play(Sound::SFX_BOMB_EXPLOSION);
        Scene->ShakeTimer = 16;
        Active = false;
        Scene->AddExplosion(Sprite, CurrentAnimation + 1, false, X, Y - 0x3C);
        Scene->AddExplosion(Sprite, CurrentAnimation + 2, false, X, Y - 0x0C);
        Scene->AddExplosion(Sprite, CurrentAnimation + 1, false, X - 0x4, Y - 0x34);
        Scene->AddExplosion(Sprite, CurrentAnimation + 2, false, X + 0xC, Y - 0x04);
        Scene->AddExplosion(Sprite, CurrentAnimation + 2, false, X - 0xC, Y - 0x04);
        Scene->AddExplosion(Sprite, CurrentAnimation + 1, false, X + 0x8, Y - 0x24);
        Scene->AddExplosion(Sprite, CurrentAnimation + 1, false, X - 0x8, Y - 0x1C);
        Scene->AddExplosion(Sprite, CurrentAnimation + 1, false, X, Y - 0x0C);
    }

    return;
    Object::Update();
}

void AirshipBomb::Render(int CamX, int CamY) {
    X = Scene->Signal[6] + InitialX + CamX;
    Y = Scene->Signal[7] + (WeY >> 16) + CamY;
    if (DrawCollisions) {
        G->DrawRectangle(X - CamX, Y - CamY, W, H, DrawCollisionsColor);
    }
    else {
        G->DrawSprite(Sprite, CurrentAnimation, Frame, X - CamX, Y - CamY, 0, IE_NOFLIP);
    }
    if (App->viewObjectCollision) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

    }

