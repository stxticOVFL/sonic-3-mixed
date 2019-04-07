// Object ID: 0x32
// Object Name: Drawbridge.cpp

#include "Drawbridge.h"

typedef IMath Math;

CONSTRUCTER Drawbridge::Drawbridge() {
    BinIndex = LevelScene::LoadSpriteBin("AIZ/Drawbridge.bin");
}

void Drawbridge::Create() {
    Object::Create();
    Active = true;
    Priority = false;
    DoDeform = true;
    W = 16;
    H = 192;
    CurrentAnimation = Sprite->FindAnimation("Drawbridge");
    Solid = true;
    SolidCustomized = true;
    Scene->AddSelfToRegistry(this, "Solid");
    VisualLayer = 1;
    Activated = false;
}

void Drawbridge::Update() {
    if (Activated) {
        if (Rotation < 0x40) Rotation += 4;

    }

    Activated = (Scene->LevelTriggerFlag & 0x80) == 0x80;
    Object::Update();
}

void Drawbridge::Break() {
}

void Drawbridge::Render(int CamX, int CamY) {
    for (int i = 1; i <= 12; i++)
G->DrawSprite(Sprite, CurrentAnimation, 0, X - CamX + ((Math::sinHex(Rotation) * i * 16) >> 16), Y - CamY - ((Math::cosHex(Rotation) * i * 16) >> 16), 0, IE_NOFLIP);

    }

int Drawbridge::CustomSolidityCheck(int probeX, int probeY, int PlayerID, int checkJumpThrough) {
    int x;
    int y;
    for (int i = 1; i <= 12; i++)
{
        x = X + ((Math::sinHex(Rotation) * i * 16) >> 16);
        y = Y - ((Math::cosHex(Rotation) * i * 16) >> 16);
        if (probeX >= x - 8 && probeY >= y - 8 && probeX < x + 8 && probeY < y + 8) {
            return 1;
        }

    }
    return 0;
}

