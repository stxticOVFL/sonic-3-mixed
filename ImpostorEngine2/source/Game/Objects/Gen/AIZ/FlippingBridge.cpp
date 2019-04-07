// Object ID: 0x2B
// Object Name: FlippingBridge.cpp

#include "FlippingBridge.h"

typedef IMath Math;

CONSTRUCTER FlippingBridge::FlippingBridge() {
    BinIndex = LevelScene::LoadSpriteBin("AIZ/Flipping Bridge.bin");
}

void FlippingBridge::Create() {
    Object::Create();
    Active = true;
    Priority = true;
    DoDeform = true;
    SolidTop = true;
    SolidCustomized = true;
    Scene->AddSelfToRegistry(this, "Solid");
    Rotation = 0;
    W = 256;
    H = 8;
    VisW = 256;
    VisH = 64;
    Delay = (SubType & 0xF) * 6;
    Period = (SubType >> 4 & 0x7) + 1;
    Rise = 8 - ((SubType & 0x80) >> 5);
    RevolutionDuration = 8 * Delay + Delay;
    Flip = FlipX ? 1 : -1;
    Timer = 0;
    Frame = 5;
    CurrentAnimation = Sprite->FindAnimation("Flipping Bridge");
}

void FlippingBridge::Update() {
    Timer = Scene->Frame % RevolutionDuration;
    if (FlipX) Timer = (RevolutionDuration - 1) - Timer;

    Object::Update();
}

void FlippingBridge::Render(int CamX, int CamY) {
    for (int i = -4; i < 4; i++)
G->DrawSprite(Sprite, CurrentAnimation, (((Timer + Delay * (i + 4) * Flip + RevolutionDuration) % RevolutionDuration) / Period), X - CamX + i * 32 + 16, Y - CamY - i * Rise, 0, IE_NOFLIP);

    }

int FlippingBridge::CustomSolidityCheck(int probeX, int probeY, int PlayerID, int checkJumpThrough) {
    if (!checkJumpThrough) return 0;

    if (!SolidTop) return 0;

    if (probeX < X - 128) return 0;

    if (probeX >= X + 128) return 0;

    int i = (probeX - (X - 8 * 32 / 2)) / 32;
    int frm = (((Timer + Delay * i * Flip + RevolutionDuration) % RevolutionDuration) / Period);
    if (frm < 5) return 0;

    int x = X - 128 + i * 32;
    int y = Y - (i - 4) * Rise;
    if (probeX >= x && probeY >= y - 4 && probeX < x + 32 && probeY < y + 4) {
        return 1;
    }

    return 0;
}

