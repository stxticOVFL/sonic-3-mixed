// Object ID: 0x53
// Object Name: MGZSwingingPlatform.cpp

#include "MGZSwingingPlatform.h"

typedef IMath Math;

void MGZSwingingPlatform::Create() {
    Object::Create();
    Active = true;
    Priority = true;
    LastX = X;
    LastY = Y;
    SolidTop = true;
    Scene->AddSelfToRegistry(this, "Solid");
    W = 48;
    H = 24;
    VisW = 48;
    VisH = 64;
}

void MGZSwingingPlatform::Update() {
    LastX = X;
    LastY = Y;
    X = InitialX + (Math::cosHex(Scene->Frame + SubType) >> 10);
    Y = InitialY - (Math::sinHex(Scene->Frame + SubType) >> 10);
    XSpeed = (X - LastX) << 8;
    if (CollidingWithPlayer) {
        if (Scene->Player->Action != ActionType::Dead && Scene->Player->EZY < Y) {
            if (Scene->CollisionAt(Scene->Player->EZX, Scene->Player->EZY - Scene->Player->H / 2 - 2, NULL, 2, Scene->Player)) {
                Scene->Player->Die(false);
            }

        }

    }

    return;
    Object::Update();
}

void MGZSwingingPlatform::Render(int CamX, int CamY) {
    G->DrawSprite(Sprite, 7, 0, InitialX - CamX + (Math::cosHex(Scene->Frame + SubType) >> 12), InitialY - CamY - (Math::sinHex(Scene->Frame + SubType) >> 12), 0, IE_NOFLIP);
    G->DrawSprite(Sprite, 7, 0, InitialX - CamX + ((Math::cosHex(Scene->Frame + SubType) * 32) >> 16), InitialY - CamY - ((Math::sinHex(Scene->Frame + SubType) * 32) >> 16), 0, IE_NOFLIP);
    G->DrawSprite(Sprite, 7, 0, InitialX - CamX + ((Math::cosHex(Scene->Frame + SubType) * 48) >> 16), InitialY - CamY - ((Math::sinHex(Scene->Frame + SubType) * 48) >> 16), 0, IE_NOFLIP);
    G->DrawSprite(Sprite, 7, 0, InitialX - CamX + ((Math::cosHex(Scene->Frame + SubType) * 64) >> 16), InitialY - CamY - ((Math::sinHex(Scene->Frame + SubType) * 64) >> 16), 0, IE_NOFLIP);
    G->DrawSprite(Sprite, 7, 1, InitialX - CamX, InitialY - CamY, 0, IE_NOFLIP);
    G->DrawSprite(Sprite, 7, 2, LastX - CamX, LastY - CamY, 0, IE_NOFLIP);
    if (App->viewObjectCollision) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

    }

