// Object ID: 0x05
// Object Name: Rock.cpp

#include "Rock.h"

typedef IMath Math;

void Rock::Create() {
    Object::Create();
    Active = true;
    Priority = false;
    DoDeform = true;
    Solid = true;
    Scene->AddSelfToRegistry(this, "Solid");
    i = 0;
    LastX = X;
    RockSize = SubType >> 4 & 0x7;
    RockType = SubType & 0x7;
    Knux = (SubType & 0x80) != 0;
    CleanupInactiveObject = true;
    i = 0;
    Rock0Pos[i++] = 0xF8;
    Rock0Pos[i++] = 0xE8;
    Rock0Pos[i++] = 0x0B;
    Rock0Pos[i++] = 0xE4;
    Rock0Pos[i++] = 0xFC;
    Rock0Pos[i++] = 0xF4;
    Rock0Pos[i++] = 0x0C;
    Rock0Pos[i++] = 0xFC;
    Rock0Pos[i++] = 0xF4;
    Rock0Pos[i++] = 0x04;
    Rock0Pos[i++] = 0x04;
    Rock0Pos[i++] = 0x0C;
    Rock0Pos[i++] = 0xF4;
    Rock0Pos[i++] = 0x1C;
    Rock0Pos[i++] = 0x0C;
    Rock0Pos[i++] = 0x1C;
    i = 0;
    Rock0Vels[i++] = 0xFD00;
    Rock0Vels[i++] = 0xFD00;
    Rock0Vels[i++] = 0xFD40;
    Rock0Vels[i++] = 0xFD80;
    Rock0Vels[i++] = 0xFD40;
    Rock0Vels[i++] = 0xFD80;
    Rock0Vels[i++] = 0xFD80;
    Rock0Vels[i++] = 0xFE00;
    Rock0Vels[i++] = 0xFD80;
    Rock0Vels[i++] = 0xFE80;
    Rock0Vels[i++] = 0xFDC0;
    Rock0Vels[i++] = 0xFE80;
    Rock0Vels[i++] = 0xFDC0;
    Rock0Vels[i++] = 0xFF00;
    Rock0Vels[i++] = 0xFE00;
    Rock0Vels[i++] = 0xFF00;
    i = 0;
    Rock1Pos[i++] = 0xFC;
    Rock1Pos[i++] = 0xF4;
    Rock1Pos[i++] = 0x0B;
    Rock1Pos[i++] = 0xF4;
    Rock1Pos[i++] = 0xFC;
    Rock1Pos[i++] = 0xFC;
    Rock1Pos[i++] = 0xF4;
    Rock1Pos[i++] = 0x0C;
    Rock1Pos[i++] = 0x0C;
    Rock1Pos[i++] = 0x0C;
    i = 0;
    Rock1Vels[i++] = 0xFE00;
    Rock1Vels[i++] = 0xFE00;
    Rock1Vels[i++] = 0x0200;
    Rock1Vels[i++] = 0xFE00;
    Rock1Vels[i++] = 0xFF00;
    Rock1Vels[i++] = 0xFE20;
    Rock1Vels[i++] = 0xFE50;
    Rock1Vels[i++] = 0xFE40;
    Rock1Vels[i++] = 0x01C0;
    Rock1Vels[i++] = 0xFE40;
    i = 0;
    Rock2Pos[i++] = 0xFC;
    Rock2Pos[i++] = 0xFC;
    Rock2Pos[i++] = 0x0C;
    Rock2Pos[i++] = 0xFC;
    Rock2Pos[i++] = 0xF4;
    Rock2Pos[i++] = 0x04;
    Rock2Pos[i++] = 0x0C;
    Rock2Pos[i++] = 0x04;
    i = 0;
    Rock2Vels[i++] = 0xFF00;
    Rock2Vels[i++] = 0xFE00;
    Rock2Vels[i++] = 0x0100;
    Rock2Vels[i++] = 0xFE20;
    Rock2Vels[i++] = 0xFE50;
    Rock2Vels[i++] = 0xFE40;
    Rock2Vels[i++] = 0x01C0;
    Rock2Vels[i++] = 0xFE40;
    i = 0;
    i = 0;
    if (Scene->ZoneID == 1) {
        W = 46;
        if (RockSize == 0) H = 78;
        else if (RockSize == 1) H = 46;
        else if (RockSize == 2) H = 30;

        if ((SubType & 0xF) == 0xF) {
            BreakableByJump = CollideSide::TOP;
            Knux = true;
        }
        else {
            if ((RockType & 1) == 1) {
                BreakableByJump = CollideSide::TOP;
            }

            if ((RockType & 2) == 2) {
                Pushable = true;
                PushMaxLeft = 64;
                PushMaxRight = 0;
                PushableSide = CollideSide::RIGHT;
            }

            if ((RockType & 4) == 4) {
                if (Knux) {
                    BreakableByKnuckles = CollideSide::SIDES;
                }
                else {
                    BreakableByRoll = CollideSide::SIDES;
                    BreakableBySuper = CollideSide::SIDES;
                }
            }

        }
        CurrentAnimation = 27;
        if (Scene->Act == 2) CurrentAnimation = 29;

        Scene->AddSelfToRegistry(this, "Breakable");
    }

}

void Rock::Update() {
    LastX = X;
    X = SubX >> 16;
    Object::Update();
}

void Rock::DrawAIZ(int CamX, int CamY) {
    if (Scene->ZoneID != 1) return;

    G->DrawSprite(Sprite, CurrentAnimation, RockSize, LastX - CamX, Y - CamY, 0, IE_NOFLIP);
}

void Rock::BreakAIZ(int HitSide) {
    if (Scene->ZoneID != 1) return;

    int off = 1;
    if (HitSide == 0) {
        Scene->AddMovingSprite(Sprite, X + 12, Y + 4, CurrentAnimation + 1, 0 + ((off + 3) & 3), false, false, 0x1C0, -0x1C0, 0x18);
        Scene->AddMovingSprite(Sprite, X - 12, Y + 4, CurrentAnimation + 1, 0 + ((off + 2) & 3), false, false, -0x1B0, -0x1C0, 0x18);
        Scene->AddMovingSprite(Sprite, X + 12, Y - 4, CurrentAnimation + 1, 0 + ((off + 1) & 3), false, false, 0x100, -0x1E0, 0x18);
        Scene->AddMovingSprite(Sprite, X - 4, Y - 4, CurrentAnimation + 1, 0 + ((off + 0) & 3), false, false, -0x100, -0x200, 0x18);
    }
    else {
        if (RockSize == 0) {
            for (int i = 0; i < 8; i++)
{
                Scene->AddMovingSprite(Sprite, X + Rock0Pos[i << 1], Y + Rock0Pos[(i << 1) + 1], CurrentAnimation + 1, 0 + ((8 - i) & 3), false, false, HitSide * Rock0Vels[i << 1], Rock0Vels[(i << 1) + 1], 0x18);
            }
        }
        else if (RockSize == 1) {
            for (int i = 0; i < 5; i++)
{
                Scene->AddMovingSprite(Sprite, X + Rock1Pos[i << 1], Y + Rock1Pos[(i << 1) + 1], CurrentAnimation + 1, 0 + ((5 - i) & 3), false, false, HitSide * Rock0Vels[i << 1], Rock0Vels[(i << 1) + 1], 0x18);
            }
        }
        else if (RockSize == 2) {
            Scene->AddMovingSprite(Sprite, X + 12, Y + 4, CurrentAnimation + 1, 0 + ((off + 3) & 3), false, false, HitSide * -0x2C0, -0x280, 0x18);
            Scene->AddMovingSprite(Sprite, X - 12, Y + 4, CurrentAnimation + 1, 0 + ((off + 2) & 3), false, false, HitSide * -0x280, -0x200, 0x18);
            Scene->AddMovingSprite(Sprite, X + 12, Y - 4, CurrentAnimation + 1, 0 + ((off + 1) & 3), false, false, HitSide * -0x300, -0x300, 0x18);
            Scene->AddMovingSprite(Sprite, X - 4, Y - 4, CurrentAnimation + 1, 0 + ((off + 0) & 3), false, false, HitSide * -0x2C0, -0x280, 0x18);
        }

    }
}

void Rock::Render(int CamX, int CamY) {
    if (!Solid) return;

    DrawAIZ(CamX, CamY);
    if (App->viewObjectCollision) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

    }

int Rock::OnBreakVertical(int PlayerID, int HitFrom) {
    if (HitFrom != CollideSide::TOP) return 0;

    if (Knux && Scene->Players[PlayerID]->Character != CharacterType::Knuckles) return 0;

    OnBreakHorizontal(PlayerID, HitFrom);
    return 1;
}

int Rock::OnBreakHorizontal(int PlayerID, int HitFrom) {
    if (Math::abs(Scene->Players[PlayerID]->GroundSpeed) < 0x480 && HitFrom != CollideSide::TOP && Scene->Players[PlayerID]->Action == ActionType::Rolling) return 1;

    Sound::Play(Sound::SFX_COLLAPSE);
    BreakableByRoll = CollideSide::NONE;
    BreakableByJump = CollideSide::NONE;
    BreakableBySuper = CollideSide::NONE;
    BreakableByGlide = CollideSide::NONE;
    BreakableByKnuckles = CollideSide::NONE;
    BreakableByMighty = CollideSide::NONE;
    Solid = false;
    int HitSide = -1;
    if (HitFrom == CollideSide::RIGHT) HitSide = 1;

    if (HitFrom == CollideSide::TOP) HitSide = 0;

    BreakAIZ(HitSide);
    return 0;
}

