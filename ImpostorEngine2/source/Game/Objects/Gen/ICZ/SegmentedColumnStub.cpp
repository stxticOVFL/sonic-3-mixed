// Object ID: 0xFFFFFFFF
// Object Name: SegmentedColumnStub.cpp

#include "SegmentedColumnStub.h"

typedef IMath Math;

void SegmentedColumnStub::Create() {
    Object::Create();
    W = 64;
    H = 32;
    Active = true;
    Priority = false;
    Solid = true;
    Scene->AddSelfToRegistry(this, "Solid");
    CurrentAnimation = Sprite->FindAnimation("Wall and Column");
    Frame = SubType == 0 ? 8 : 1;
    IApp::Print(0, "%d %d", X, Y);
    BreakableByRoll = CollideSide::SIDES;
    Scene->AddSelfToRegistry(this, "Breakable");
    Number = -1;
}

int SegmentedColumnStub::OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data) {
    if (!Solid) return 0;

    IApp::Print(0, "%d", Number);
    return 1;
}

void SegmentedColumnStub::Render(int CamX, int CamY) {
    if (!Visible) return;

    G->DrawSprite(Sprite, CurrentAnimation, Frame, X - CamX, Y - CamY, 0, IE_NOFLIP);
    }

int SegmentedColumnStub::OnBreakHorizontal(int PlayerID, int HitFrom) {
    if (HitFrom != CollideSide::SIDES) return 0;

    Solid = false;
    Visible = false;
    return 1;
}

