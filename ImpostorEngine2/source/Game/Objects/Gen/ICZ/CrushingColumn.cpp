// Object ID: 0xAF
// Object Name: CrushingColumn.cpp

#include "CrushingColumn.h"

typedef IMath Math;

void CrushingColumn::Create() {
    Object::Create();
    Active = true;
    Priority = false;
    Solid = true;
    DoDeform = true;
    Scene->AddSelfToRegistry(this, "Solid");
    W = 64;
    H = 224;
    CurrentAnimation = Sprite->FindAnimation("Wall and Column");
    OGY = Y - 5 + 5;
    Y += 10;
    YSpeed = -0xA0;
    Direction = true;
    SmashStyle = 0;
    if (SubType == 2) SmashStyle = 2;

    if (SubType == 4) SmashStyle = 1;

    if (SubType == 3) SmashStyle = 3;

    State = 0;
    SmashTimer = 0;
}

void CrushingColumn::Update() {
    if (Direction) {
        if (Y <= OGY && SmashStyle == 1) {
            YSpeed = 0;
            YSpeed = 0x300;
            Direction = false;
        }
        else if (Y >= OGY && SmashStyle == 2) {
            YSpeed = 0;
            YSpeed = -0x300;
            Direction = false;
        }

        State = 0;
    }
    else {
        if (SmashStyle == 1) {
            if (SmashTimer > 0) {
                YSpeed += 0x30;
                if (Y >= OGY + 80) {
                    if (OnScreen) {
                        Sound::Play(Sound::SFX_IMPACT4);
                    }

                    YSpeed = 0;
                    SmashTimer = 0;
                    YSpeed = -0x110;
                    Direction = true;
                    Y = OGY + 80;
                    State++;
                }

            }

        }
        else if (SmashStyle == 2) {
            if (SmashTimer > 0) {
                if (SubType == 1 && !State == 1) {
                    SmashTimer = 1;
                }

                YSpeed -= 0x30;
                if (Y <= OGY - 80) {
                    if (OnScreen) {
                        Sound::Play(Sound::SFX_IMPACT4);
                    }

                    YSpeed = 0;
                    SmashTimer = 0;
                    YSpeed = 0x110;
                    Direction = true;
                    Y = OGY - 80;
                    State++;
                }

            }

        }
        else if (SmashStyle == 3) {
            if (X < Scene->Players[0]->X + 20) {
                YSpeed -= 0x30;
                if (Y <= OGY - 80) {
                    if (OnScreen) {
                        Sound::Play(Sound::SFX_IMPACT4);
                    }

                    YSpeed = 0;
                    SmashTimer = 0;
                    YSpeed = 0x110;
                    Y = OGY - 80;
                }

            }

        }

    }
    SmashTimer++;
    Object::Update();
}

void CrushingColumn::Render(int CamX, int CamY) {
    if (!Visible) return;

    G->DrawSprite(Sprite, CurrentAnimation, Frame >> 8, X - CamX, Y - CamY, 0, IE_NOFLIP);
    }

int CrushingColumn::OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data) {
    if (!Solid) return 0;

    if (HitFrom == CollideSide::TOP && Visible) {
    }
    else {
    }
    if (Scene->Players[PlayerID]->Ground && !Direction) {
        Scene->Players[PlayerID]->Die(false);
    }

    return 1;
}

