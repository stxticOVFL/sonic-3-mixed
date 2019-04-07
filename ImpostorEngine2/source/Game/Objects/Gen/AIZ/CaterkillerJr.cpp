// Object ID: 0x8F
// Object Name: CaterkillerJr.cpp

#include "CaterkillerJr.h"

typedef IMath Math;

CONSTRUCTER CaterkillerJr::CaterkillerJr() {
    BinIndex = LevelScene::LoadSpriteBin("AIZ/Caterkiller Jr.bin");
}

void CaterkillerJr::Create() {
    Enemy::Create();
    Active = true;
    Priority = false;
    W = 32;
    H = 16;
    VisW = 96;
    VisH = 64;
    Frame = 0;
    HitCount = 1;
    CurrentAnimation = Sprite->FindAnimation("Caterkiller Jr");
    CleanupInactiveObject = true;
    XSpeed = -0x100;
    Routine = 4;
    SwingCounter = 3;
    YSpeed = 0x80;
    MaxAccel = 0x80;
    Acceleration = 0x8;
    SwingDirection = 0;
    Harmful = true;
    for (int i = 0; i < 0x7F; i++)
PosTable[i] = 0;

}

void CaterkillerJr::OnSwingFinish() {
    Routine = 6;
    YSpeed = 0x100;
    MaxAccel = 0x100;
    Acceleration = 0x8;
    SwingDirection = 0;
}

void CaterkillerJr::Update() {
    Frame++;
    Frame &= 0x7F;
    int d3;
    bool nomove = false;
    switch (Routine) {
        case 4:
        Rotation = Swing_UpAndDown();
        if (Routine == 6) nomove = true;

        break;
        case 6:
        d3 = Swing_UpAndDown();
        Rotation = d3;
        if (d3) {
            Routine = 8;
            XSpeed = -XSpeed;
            FlipX = !FlipX;
        }

        break;
        case 8:
        d3 = Swing_UpAndDown();
        Rotation = d3;
        if (d3) {
            Routine = 4;
            SwingCounter = 3;
            YSpeed = 0x80;
            MaxAccel = 0x80;
            Acceleration = 0x8;
            SwingDirection = 0;
            nomove = true;
        }

        break;
    }

    PosTable[(Frame + 0x7F) & 0x7F] = (FlipX & 0x1) << 31 | (X & 0x7FFF) << 16 | (Y & 0xFFFF);
    if (nomove) return;

    Object::Update();
}

int CaterkillerJr::OnHit() {
    return OnDeath();
}

void CaterkillerJr::Render(int CamX, int CamY) {
    int x;
    int y;
    int fX;
    uint32_t pos;
    pos = PosTable[(Frame + 0x80 - 64) & 0x7F];
    fX = pos >> 31;
    x = pos >> 16 & 0x7FFF;
    y = pos & 0xFFFF;
    G->DrawSprite(Sprite, 22, 3, x - CamX, y - CamY, 0, fX | FlipY << 1);
    pos = PosTable[(Frame + 0x80 - 56) & 0x7F];
    fX = pos >> 31;
    x = pos >> 16 & 0x7FFF;
    y = pos & 0xFFFF;
    G->DrawSprite(Sprite, 22, 3, x - CamX, y - CamY, 0, fX | FlipY << 1);
    pos = PosTable[(Frame + 0x80 - 48) & 0x7F];
    fX = pos >> 31;
    x = pos >> 16 & 0x7FFF;
    y = pos & 0xFFFF;
    G->DrawSprite(Sprite, CurrentAnimation, 2, x - CamX, y - CamY, 0, fX | FlipY << 1);
    pos = PosTable[(Frame + 0x80 - 36) & 0x7F];
    fX = pos >> 31;
    x = pos >> 16 & 0x7FFF;
    y = pos & 0xFFFF;
    G->DrawSprite(Sprite, CurrentAnimation, 1, x - CamX, y - CamY, 0, fX | FlipY << 1);
    pos = PosTable[(Frame + 0x80 - 24) & 0x7F];
    fX = pos >> 31;
    x = pos >> 16 & 0x7FFF;
    y = pos & 0xFFFF;
    G->DrawSprite(Sprite, CurrentAnimation, 1, x - CamX, y - CamY, 0, fX | FlipY << 1);
    pos = PosTable[(Frame + 0x80 - 12) & 0x7F];
    fX = pos >> 31;
    x = pos >> 16 & 0x7FFF;
    y = pos & 0xFFFF;
    G->DrawSprite(Sprite, CurrentAnimation, 1, x - CamX, y - CamY, 0, fX | FlipY << 1);
    G->DrawSprite(Sprite, CurrentAnimation, 3 + ((Scene->Frame >> 2) % 3), x - CamX, y - CamY, 0, fX);
    G->DrawSprite(Sprite, CurrentAnimation, 0, X - CamX, Y - CamY, 0, FlipX | FlipY << 1);
    if (App->viewObjectCollision) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

    }

