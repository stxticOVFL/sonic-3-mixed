// Object ID: 0x2A
// Object Name: CorkFloor.cpp

#include "CorkFloor.h"

typedef IMath Math;

void CorkFloor::Create() {
    Object::Create();
    Active = true;
    Priority = false;
    Solid = true;
    Scene->AddSelfToRegistry(this, "Solid");
    BreakableFromTop = false;
    if (SubType == 1) BreakableFromTop = true;

    int i = 0;
    if (Scene->ZoneID == 1) {
        W = 32;
        H = 80;
        if (Scene->Act == 2) H = 88;

        VisualLayer = 1;
        i = 0;
        PieceVels[i++] = 0xFF00;
        PieceVels[i++] = 0xFE00;
        PieceVels[i++] = 0x0100;
        PieceVels[i++] = 0xFE00;
        PieceVels[i++] = 0xFF20;
        PieceVels[i++] = 0xFE40;
        PieceVels[i++] = 0x00E0;
        PieceVels[i++] = 0xFE40;
        PieceVels[i++] = 0xFF40;
        PieceVels[i++] = 0xFE80;
        PieceVels[i++] = 0x00C0;
        PieceVels[i++] = 0xFE80;
        PieceVels[i++] = 0xFF60;
        PieceVels[i++] = 0xFEC0;
        PieceVels[i++] = 0x00A0;
        PieceVels[i++] = 0xFEC0;
        PieceVels[i++] = 0xFF80;
        PieceVels[i++] = 0xFF00;
        PieceVels[i++] = 0x0080;
        PieceVels[i++] = 0xFF00;
        PieceVels[i++] = 0xFFA0;
        PieceVels[i++] = 0xFF40;
        PieceVels[i++] = 0x0060;
        PieceVels[i++] = 0xFF40;
        CurrentAnimation = 8;
        if (Scene->Act == 2) CurrentAnimation = 9;

        BreakableByJump = CollideSide::BOTTOM;
        if (BreakableFromTop) BreakableByJump = CollideSide::TOP;

        BreakableByRoll = BreakableByJump;
        if (!BreakableFromTop) BreakableBySpring = CollideSide::BOTTOM;

        Scene->AddSelfToRegistry(this, "Breakable");
    }
    else {
        BreakableByJump = CollideSide::BOTTOM;
        if (BreakableFromTop) BreakableByJump = CollideSide::TOP;

        BreakableByRoll = BreakableByJump;
    }
}

void CorkFloor::DrawAIZ(int CamX, int CamY) {
    if (Scene->ZoneID != 1) return;

    G->DrawSprite(Sprite, CurrentAnimation, 0, X - CamX, Y - CamY, 0, IE_NOFLIP);
}

void CorkFloor::BreakAIZ(int HitSide) {
    if (Scene->ZoneID != 1) return;

    int w = 2;
    int h = 6;
    int x = X - w * 8;
    int y = Y + H / 2 - h * 16;
    int left = Sprite->Animations[CurrentAnimation].Frames[Frame].X;
    int top = Sprite->Animations[CurrentAnimation].Frames[Frame].Y;
    int top2 = Sprite->Animations[CurrentAnimation].Frames[Frame].Y;
    int toph = 16;
    for (int i = 0; i < w; i++)
{
        for (int j = 0; j < h; j++)
{
            toph = 16;
            top2 = top + 88 - h * 16 + j * 16;
            if (top2 < top) {
                toph = top - top2;
                top2 = top;
            }

            if (FlipX) {
                Scene->AddMovingSprite(Sprite, x + i * 16, y + j * 16 + 16 - toph, left + (w - 1 - i) * 16, top2, 16, toph, 0, 0, FlipX, false, PieceVels[(i + j * w) * 2], PieceVels[(i + j * w) * 2 + 1], 0x18, 0);
            }
            else {
                Scene->AddMovingSprite(Sprite, x + i * 16, y + j * 16 + 16 - toph, left + i * 16, top2, 16, toph, 0, 0, FlipX, false, PieceVels[(i + j * w) * 2], PieceVels[(i + j * w) * 2 + 1], 0x18, 0);
            }
        }
    }
}

void CorkFloor::Render(int CamX, int CamY) {
    if (!Solid) return;

    DrawAIZ(CamX, CamY);
    }

int CorkFloor::OnBreakVertical(int PlayerID, int HitFrom) {
    if (PlayerID != 0) return 0;

    if (Scene->Players[PlayerID]->EZX > X + W / 2 - 2) return 0;

    if (Scene->Players[PlayerID]->EZX < X - W / 2 + 2) return 0;

    if (BreakableFromTop && HitFrom == CollideSide::BOTTOM) return 0;

    if (!BreakableFromTop && HitFrom == CollideSide::TOP) return 0;

    Sound::Play(Sound::SFX_COLLAPSE);
    BreakableByRoll = CollideSide::NONE;
    BreakableByJump = CollideSide::NONE;
    BreakableByGlide = CollideSide::NONE;
    BreakableBySpring = CollideSide::NONE;
    BreakableByKnuckles = CollideSide::NONE;
    Solid = false;
    BreakAIZ(HitFrom);
    return 1;
}

