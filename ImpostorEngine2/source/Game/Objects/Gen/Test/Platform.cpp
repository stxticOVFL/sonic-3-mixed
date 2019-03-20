// Object ID: 0xFFFFFFFF
// Object Name: Platform.cpp

#include "Platform.h"

typedef IMath Math;

void Platform::Create() {
    Object::Create();
    Active = true;
    Priority = false;
    Scene->AddSelfToRegistry(this, "Solid");
    W = 64;
    H = 64;
    int i = 0;
    /*Type = Attributes[0];
    AmplitudeX = Attributes[1];
    Speed = Attributes[2];
    HasTension = Attributes[3];
    FrameID = Attributes[4];
    Collision = Attributes[5];
    TileOriginX = Attributes[6];
    ChildCount = Attributes[7];
    Angle = Attributes[8];*/
    if (Collision == 0) SolidTop = true;
    else Solid = true;
    if (Type == PlatformType::PUSHABLE) {
        Pushable = true;
        PushMaxLeft = Speed * 16;
        PushMaxRight = Speed * 16;
    }

    switch (FrameID) {
        case 0:
        W = 32;
        H = 32;
        break;
        case 1:
        W = 64;
        H = 64;
        break;
        case 3:
        W = 64;
        H = 64;
        break;
        case 4:
        W = 64;
        H = 64;
        break;
        case 2:
        W = 64;
        H = 16;
        break;
        case 5:
        W = 160;
        H = 48;
        break;
        case 6:
        W = 248;
        H = 96;
        break;
    }

}

void Platform::Update() {
    Object::Update();
}

void Platform::Render(int CamX, int CamY) {
    G->DrawRectangle(X - CamX - W / 2, Y - CamY - H / 2, W, H, 0xFFFFFF);
    if (App->viewObjectCollision) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

    }

