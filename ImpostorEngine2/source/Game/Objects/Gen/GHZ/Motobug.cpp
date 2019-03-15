// Object ID: 0xFFFFFFFF
// Object Name: Motobug.cpp

#include "Motobug.h"

typedef IMath Math;

CONSTRUCTER Motobug::Motobug() {
    BinIndex = LevelScene::LoadSpriteBin("GHZ/Motobug.bin");
    Time = 30;
    SmokeDelay = 43;
    Gravity = 10;
    State = 0;
    Smoke = NULL;
}

void Motobug::Create() {
    Enemy::Create();
    Active = true;
    Priority = false;
    CleanupInactiveObject = true;
    AutoAnimate = false;
    W = 39;
    H = 28;
    VisW = 39;
    VisH = 28;
    Frame = 0;
    Acceleration = 150;
    HitCount = 1;
    CurrentAnimation = 0;
}

void Motobug::Update() {
    if (!isHeldDebugObject) {
        switch (State) {
            case 0:
            XSpeed = FlipX ? Acceleration : -Acceleration;
            if (SmokeDelay == 0) {
                SmokeDelay = 33;
                Smoke = Scene->AddNewObject(Obj_MotobugSmoke, 0, X, Y, false, false);
                Smoke->FlipX = FlipX;
                Smoke->Parent = this;
            }
            else {
                SmokeDelay--;
            }
            break;
            case 1:
            if (Time != 0) {
                CurrentAnimation = 1;
                Time--;
                break;
            }
            else {
                Time = 30;
                CurrentAnimation = 0;
                State = 0;
            }
            break;
        }

    }

    Object::Update();
}

void Motobug::Render(int CamX, int CamY) {
    if (CurrentAnimation == -1) {
        return;
    }

    if (Frame < 0) {
        return;
    }

    if (!Visible) {
        return;
    }

    G->DrawSprite(Sprite, CurrentAnimation, Frame, X - CamX, Y - CamY, Rotation, FlipX | FlipY << 1);
    if (App->viewObjectCollision) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

    }

