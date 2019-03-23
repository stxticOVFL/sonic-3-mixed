// Object ID: 0x0D
// Object Name: BreakableWall.cpp

#include "BreakableWall.h"

typedef IMath Math;

void BreakableWall::Create() {
    Object::Create();
    Active = true;
    Priority = false;
    DoDeform = true;
    Solid = true;
    Scene->AddSelfToRegistry(this, "Solid");
    W = 32;
    H = 64;
    Behavior = SubType & 0xF;
    LevelTriggered = (SubType & 0x80) == 0x80;
    if (Scene->ZoneID == 6 || Scene->ZoneID == 7 || Scene->ZoneID == 9) Behavior |= 2;

    if (!LevelTriggered) {
        if (Behavior == 0) {
            BreakableByRoll = CollideSide::SIDES;
            BreakableBySuper = CollideSide::SIDES;
        }

        BreakableByGlide = CollideSide::SIDES;
        BreakableByKnuckles = CollideSide::SIDES;
        Scene->AddSelfToRegistry(this, "Breakable");
    }

    switch (Scene->ZoneID) {
        case 1:
        W = 32;
        H = 80;
        Priority = true;
        CurrentAnimation = 3;
        break;
        case 2:
        W = 32;
        H = 64;
        if (Behavior == 2) W = 48;

        VisualLayer = 1;
        break;
        case 3:
        W = 64;
        H = 80;
        CurrentAnimation = 5;
        break;
        case 4:
        W = 32;
        H = 64;
        CurrentAnimation = 0;
        break;
        case 5:
        W = 64;
        H = 128;
        CurrentAnimation = 0;
        break;
        case 6:
        W = 32;
        H = 64;
        CurrentAnimation = 1;
        break;
        case 7:
        case 8:
        case 9:
        W = 32;
        H = 64;
        if (Behavior == 4) H = 96;

        break;
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        break;
    }

}

void BreakableWall::DrawAIZ(int CamX, int CamY) {
    if (Scene->ZoneID != 1) return;

    G->DrawSprite(Sprite, CurrentAnimation, SubType & 0xF, X - CamX, Y - CamY, 0, IE_NOFLIP);
    if (DrawCollisions) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

}

void BreakableWall::DrawHCZ(int CamX, int CamY) {
    if (Scene->ZoneID != 2) return;

    if (SubType == 2) {
        G->DrawSprite(Scene->TileSprite, 0, 0x2B, 8 + X - CamX + (-24), 8 + Y - 16 - CamY + (-16), 0, IE_NOFLIP);
        G->DrawSprite(Scene->TileSprite, 0, 0xAE, 8 + X - CamX + (-8), 8 + Y - 16 - CamY + (-16), 0, IE_NOFLIP);
        G->DrawSprite(Scene->TileSprite, 0, 0x2B, 8 + X - CamX + 8 + (0), 8 + Y - 16 - CamY + (-16), 0, IE_FLIPX);
        G->DrawSprite(Scene->TileSprite, 0, 0x32, 8 + X - CamX + (-24), 8 + Y - 16 - CamY + (0), 0, IE_NOFLIP);
        G->DrawSprite(Scene->TileSprite, 0, 0x81, 8 + X - CamX + (-8), 8 + Y - 16 - CamY + (0), 0, IE_NOFLIP);
        G->DrawSprite(Scene->TileSprite, 0, 0x32, 8 + X - CamX + 8 + (0), 8 + Y - 16 - CamY + (0), 0, IE_FLIPX);
        G->DrawSprite(Scene->TileSprite, 0, 0x80, 8 + X - CamX + (-24), 8 + Y + 16 - CamY + (-16), 0, IE_NOFLIP);
        G->DrawSprite(Scene->TileSprite, 0, 0x29, 8 + X - CamX + (-8), 8 + Y + 16 - CamY + (-16), 0, IE_NOFLIP);
        G->DrawSprite(Scene->TileSprite, 0, 0x80, 8 + X - CamX + 8 + (0), 8 + Y + 16 - CamY + (-16), 0, IE_FLIPX);
        G->DrawSprite(Scene->TileSprite, 0, 0x32, 8 + X - CamX + (-24), 8 + Y + 16 - CamY + (0), 0, IE_NOFLIP);
        G->DrawSprite(Scene->TileSprite, 0, 0x81, 8 + X - CamX + (-8), 8 + Y + 16 - CamY + (0), 0, IE_NOFLIP);
        G->DrawSprite(Scene->TileSprite, 0, 0x32, 8 + X - CamX + 8 + (0), 8 + Y + 16 - CamY + (0), 0, IE_FLIPX);
    }
    else {
        G->DrawSprite(Scene->TileSprite, 0, 0x8F, 8 + X - CamX + (-16), 8 + Y - 16 - CamY + (-16), 0, IE_NOFLIP);
        G->DrawSprite(Scene->TileSprite, 0, 0x90, 8 + X - CamX + (0), 8 + Y - 16 - CamY + (-16), 0, IE_NOFLIP);
        G->DrawSprite(Scene->TileSprite, 0, 0x91, 8 + X - CamX + (-16), 8 + Y - 16 - CamY + (0), 0, IE_NOFLIP);
        G->DrawSprite(Scene->TileSprite, 0, 0x92, 8 + X - CamX + (0), 8 + Y - 16 - CamY + (0), 0, IE_NOFLIP);
        G->DrawSprite(Scene->TileSprite, 0, 0x8F, 8 + X - CamX + (-16), 8 + Y + 16 - CamY + (-16), 0, IE_NOFLIP);
        G->DrawSprite(Scene->TileSprite, 0, 0x90, 8 + X - CamX + (0), 8 + Y + 16 - CamY + (-16), 0, IE_NOFLIP);
        G->DrawSprite(Scene->TileSprite, 0, 0x91, 8 + X - CamX + (-16), 8 + Y + 16 - CamY + (0), 0, IE_NOFLIP);
        G->DrawSprite(Scene->TileSprite, 0, 0x92, 8 + X - CamX + (0), 8 + Y + 16 - CamY + (0), 0, IE_NOFLIP);
    }
    if (DrawCollisions) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

}

void BreakableWall::DrawMGZ(int CamX, int CamY) {
    if (Scene->ZoneID != 3) return;

    G->DrawSprite(Sprite, CurrentAnimation, 0, X - CamX, Y - CamY, 0, IE_NOFLIP);
    return;
    int h = H / 2;
    G->DrawSprite(Scene->TileSprite, 0, 0x44, 8 + X - CamX - 32 + (0), 8 + Y - h - CamY + (0), 0, IE_NOFLIP);
    G->DrawSprite(Scene->TileSprite, 0, 0x45, 8 + X - CamX - 16 + (0), 8 + Y - h - CamY + (0), 0, IE_NOFLIP);
    G->DrawSprite(Scene->TileSprite, 0, 0x45, 8 + X - CamX + 00 + (0), 8 + Y - h - CamY + (0), 0, IE_FLIPX);
    G->DrawSprite(Scene->TileSprite, 0, 0x44, 8 + X - CamX + 16 + (0), 8 + Y - h - CamY + (0), 0, IE_FLIPX);
    for (int i = -h + 16; i < h - 16; i += 16)
{
        G->DrawSprite(Scene->TileSprite, 0, 0x4A, 8 + X - CamX - 32 + (0), 8 + Y + i - CamY + (0), 0, IE_NOFLIP);
        G->DrawSprite(Scene->TileSprite, 0, 0x4B, 8 + X - CamX - 16 + (0), 8 + Y + i - CamY + (0), 0, IE_NOFLIP);
        G->DrawSprite(Scene->TileSprite, 0, 0x4B, 8 + X - CamX + 00 + (0), 8 + Y + i - CamY + (0), 0, IE_FLIPX);
        G->DrawSprite(Scene->TileSprite, 0, 0x4A, 8 + X - CamX + 16 + (0), 8 + Y + i - CamY + (0), 0, IE_FLIPX);
    }
    G->DrawSprite(Scene->TileSprite, 0, 0x44, 8 + X - CamX - 32 + (0), 8 + Y + h - CamY + (-16), 0, IE_NOFLIP);
    G->DrawSprite(Scene->TileSprite, 0, 0x45, 8 + X - CamX - 16 + (0), 8 + Y + h - CamY + (-16), 0, IE_NOFLIP);
    G->DrawSprite(Scene->TileSprite, 0, 0x45, 8 + X - CamX + 00 + (0), 8 + Y + h - CamY + (-16), 0, IE_FLIPX);
    G->DrawSprite(Scene->TileSprite, 0, 0x44, 8 + X - CamX + 16 + (0), 8 + Y + h - CamY + (-16), 0, IE_FLIPX);
    if (DrawCollisions) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

}

void BreakableWall::BreakHCZ(int HitSide) {
    if (Scene->ZoneID != 2) return;

    if (Behavior == 2) {
        Scene->AddFallingTile(0x2B, X, Y - 16, -24, -16, IE_NOFLIP, false, HitSide * 0x400, -0x500);
        Scene->AddFallingTile(0xAE, X, Y - 16, -8, -16, IE_NOFLIP, false, HitSide * 0x600, -0x600);
        Scene->AddFallingTile(0x2B, X + 8, Y - 16, -0, -16, true, false, HitSide * 0x500, -0x400);
        Scene->AddFallingTile(0x32, X, Y - 16, -24, -0, IE_NOFLIP, false, HitSide * 0x600, -0x200);
        Scene->AddFallingTile(0x81, X, Y - 16, -8, -0, IE_NOFLIP, false, HitSide * 0x800, -0x300);
        Scene->AddFallingTile(0x32, X + 8, Y - 16, -0, -0, true, false, HitSide * 0x700, -0x100);
        Scene->AddFallingTile(0x80, X, Y + 16, -24, -16, IE_NOFLIP, false, HitSide * 0x600, 0x200);
        Scene->AddFallingTile(0x29, X, Y + 16, -8, -16, IE_NOFLIP, false, HitSide * 0x800, 0x300);
        Scene->AddFallingTile(0x80, X + 8, Y + 16, -0, -16, true, false, HitSide * 0x700, 0x100);
        Scene->AddFallingTile(0x32, X, Y + 16, -24, -0, IE_NOFLIP, false, HitSide * 0x400, 0x500);
        Scene->AddFallingTile(0x81, X, Y + 16, -8, -0, IE_NOFLIP, false, HitSide * 0x600, 0x600);
        Scene->AddFallingTile(0x32, X + 8, Y + 16, -0, -0, true, false, HitSide * 0x500, 0x400);
    }
    else {
        Scene->AddFallingTile(0x8F, X, Y - 16, -16, -16, false, false, HitSide * 0x400, -0x500);
        Scene->AddFallingTile(0x90, X, Y - 16, 0, -16, false, false, HitSide * 0x600, -0x600);
        Scene->AddFallingTile(0x91, X, Y - 16, -16, 0, false, false, HitSide * 0x600, -0x100);
        Scene->AddFallingTile(0x92, X, Y - 16, 0, 0, false, false, HitSide * 0x800, -0x200);
        Scene->AddFallingTile(0x8F, X, Y + 16, -16, -16, false, false, HitSide * 0x600, 0x100);
        Scene->AddFallingTile(0x90, X, Y + 16, 0, -16, false, false, HitSide * 0x800, 0x200);
        Scene->AddFallingTile(0x91, X, Y + 16, -16, 0, false, false, HitSide * 0x400, 0x500);
        Scene->AddFallingTile(0x92, X, Y + 16, 0, 0, false, false, HitSide * 0x600, 0x600);
    }
}

void BreakableWall::BreakMGZ(int HitSide) {
    if (Scene->ZoneID != 3) return;

    int h = H / 2;
    HitSide = -HitSide;
    Scene->AddFallingTile(0x44, X - 32, Y - h, 0, 0, false, false, HitSide * 0x400, -0x500);
    Scene->AddFallingTile(0x45, X - 16, Y - h, 0, 0, false, false, HitSide * 0x500, -0x580);
    Scene->AddFallingTile(0x45, X + 00, Y - h, 0, 0, true, false, HitSide * 0x600, -0x600);
    Scene->AddFallingTile(0x44, X + 16, Y - h, 0, 0, true, false, HitSide * 0x700, -0x680);
    int wh = -1;
    for (int i = -h + 16; i < h - 16; i += 16)
{
        Scene->AddFallingTile(0x4A, X - 32, Y + i, 0, 0, false, false, HitSide * (0x680 - (Math::abs(wh) << 7)), wh * 0x100);
        Scene->AddFallingTile(0x4B, X - 16, Y + i, 0, 0, false, false, HitSide * (0x780 - (Math::abs(wh) << 7)), wh * 0x180);
        Scene->AddFallingTile(0x4B, X + 00, Y + i, 0, 0, true, false, HitSide * (0x880 - (Math::abs(wh) << 7)), wh * 0x200);
        Scene->AddFallingTile(0x4A, X + 16, Y + i, 0, 0, true, false, HitSide * (0x980 - (Math::abs(wh) << 7)), wh * 0x280);
        wh++;
    }
    Scene->AddFallingTile(0x44, X - 32, Y + h, 0, -16, false, false, HitSide * 0x400, 0x500);
    Scene->AddFallingTile(0x45, X - 16, Y + h, 0, -16, false, false, HitSide * 0x500, 0x580);
    Scene->AddFallingTile(0x45, X + 00, Y + h, 0, -16, true, false, HitSide * 0x600, 0x600);
    Scene->AddFallingTile(0x44, X + 16, Y + h, 0, -16, true, false, HitSide * 0x700, 0x680);
}

void BreakableWall::Update() {
    if (Scene->LevelTriggerFlag > 0 && LevelTriggered) {
        switch (Scene->ZoneID) {
            case 1:
            if (Y > Scene->Player->EZY) {
                Y += 8;
                if (Y - InitialY > 160) Active = false;

            }
            else {
                Y -= 8;
                if (InitialY - Y > 160) Active = false;

            }
            break;
        }

    }

    Object::Update();
}

void BreakableWall::Render(int CamX, int CamY) {
    if (!Solid) return;

    G->DrawRectangle(X - W / 2 - CamX, Y - H / 2 - CamY, W, H, 0xFF0000);
    DrawAIZ(CamX, CamY);
    DrawHCZ(CamX, CamY);
    DrawMGZ(CamX, CamY);
    if (Scene->ZoneID >= 4 && CurrentAnimation >= 0) {
        G->DrawSprite(Sprite, CurrentAnimation, 0, X - CamX, Y - CamY, 0, IE_NOFLIP);
    }

    }

int BreakableWall::OnBreakHorizontal(int PlayerID, int HitFrom) {
    Sound::Play(Sound::SFX_COLLAPSE);
    BreakableByRoll = CollideSide::NONE;
    BreakableByJump = CollideSide::NONE;
    BreakableByGlide = CollideSide::NONE;
    BreakableBySuper = CollideSide::NONE;
    BreakableByKnuckles = CollideSide::NONE;
    Solid = false;
    int HitSide = -1;
    if (HitFrom == CollideSide::RIGHT) HitSide = 1;

    BreakHCZ(HitSide);
    BreakMGZ(HitSide);
    return 0;
}

