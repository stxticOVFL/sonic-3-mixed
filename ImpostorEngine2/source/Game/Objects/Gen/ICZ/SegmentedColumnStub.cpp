// Object ID: 0xFFFFFFFF
// Object Name: SegmentedColumnStub.cpp

#include "SegmentedColumnStub.h"

typedef IMath Math;

CONSTRUCTER SegmentedColumnStub::SegmentedColumnStub() {
    BinIndex = LevelScene::LoadSpriteBin("ICZ/Wall and Column.bin");
}

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
}

int SegmentedColumnStub::OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data) {
    if (!Solid) return 0;

    return 1;
}

void SegmentedColumnStub::Break() {
    BinIndex = LevelScene::LoadSpriteBin("ICZ/Ice Cube.bin");
    CurrentAnimation = Sprite->FindAnimation("Ice Cube");
    Scene->AddMovingSprite(Sprite, X + 12, Y + 4, CurrentAnimation + 1, 0 + (4 & 3), false, false, 0x1C0, -0x1C0, 0xA0);
    Scene->AddMovingSprite(Sprite, X - 12, Y + 4, CurrentAnimation + 1, 0 + (3 & 3), false, false, -0x1B0, -0x1C0, 0xA0);
    Scene->AddMovingSprite(Sprite, X + 12, Y - 4, CurrentAnimation + 1, 0 + (2 & 3), false, false, 0x100, -0x1E0, 0xA0);
    Scene->AddMovingSprite(Sprite, X - 4, Y - 4, CurrentAnimation + 1, 0 + (1 & 3), false, false, -0x100, -0x200, 0xA0);
}

void SegmentedColumnStub::Render(int CamX, int CamY) {
    if (!Visible) {
        return;
    }

    if (DrawCollisions) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - CamX, Y - CamY, W, H, DrawCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

    G->DrawSprite(Sprite, CurrentAnimation, Frame, X - CamX, Y - CamY, 0, IE_NOFLIP);
    }

int SegmentedColumnStub::OnBreakVertical(int PlayerID, int HitFrom) {
    return OnBreakHorizontal(PlayerID, HitFrom);
}

int SegmentedColumnStub::OnBreakHorizontal(int PlayerID, int HitFrom) {
    if ((HitFrom & (int)(CollideSide::SIDES)) == 0) {
        return 0;
    }

    if (Scene->Players[PlayerID]->XSpeed > 0x12) {
        BreakableByRoll = CollideSide::NONE;
        Sound::Play(Sound::SFX_COLLAPSE);
        Solid = false;
        Visible = false;
        Break();
        return 1;
    }

    return 0;
}

