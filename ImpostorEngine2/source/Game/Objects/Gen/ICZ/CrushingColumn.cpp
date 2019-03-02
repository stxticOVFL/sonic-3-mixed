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
    Direction = false;
    SmashStyle = 0;
    if (SubType == 2) SmashStyle = 2;

    if (SubType == 4) SmashStyle = 1;

    if (SubType == 3) SmashStyle = 3;

    State = PillarState::WAIT;
    SmashTimer = 0;
}

void CrushingColumn::Update() {
    switch (State) {
        case PillarState::WAIT:
        Gravity = 0;
        YSpeed = 0;
        break;
        case PillarState::CRUSH_DOWN:
        YSpeed = 0x300;
        Direction = false;
        if (Y >= OGY + 80) {
            if (OnScreen) {
                Sound::Play(Sound::SFX_IMPACT4);
            }

            YSpeed = 0;
            Gravity = 0;
            Direction = true;
            TimerAction = PillarAction::WAITACTION;
            State = PillarState::WAIT;
        }

        break;
        case PillarState::MOVE_UP:
        if (SmashStyle = 1) {
            YSpeed = -0x110;
            if (Y <= OGY) {
                Direction = false;
                TimerAction = PillarAction::WAITACTION;
                State = PillarState::WAIT;
            }

        }
        else {
            Gravity = -0x200;
        }
        break;
        case PillarState::BLOCK:
        YSpeed = 0x400;
        Direction = false;
        break;
    }

    if (Timer > 0) Timer--;
    else if (Timer == 0) {
        Timer = -1;
        switch (TimerAction) {
            case PillarAction::WAITACTION:
            if (SmashStyle = 1) {
                Timer = 0x5F;
                if (Direction) {
                    State = PillarState::MOVE_UP;
                    TimerAction = PillarAction::MOVE_UPACTION;
                }

                TimerAction = PillarAction::CRUSH_DOWNACTION;
            }

            break;
            case PillarAction::CRUSH_DOWNACTION:
            State = PillarState::CRUSH_DOWN;
            break;
            case PillarAction::MOVE_UPACTION:
            State = PillarState::MOVE_UP;
            break;
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

