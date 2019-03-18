// Object ID: 0xAF
// Object Name: CrushingColumn.cpp

#include "CrushingColumn.h"

typedef IMath Math;

CONSTRUCTER CrushingColumn::CrushingColumn() {
    BinIndex = LevelScene::LoadSpriteBin("ICZ/Wall and Column.bin");
}

void CrushingColumn::Create() {
    Object::Create();
    Active = true;
    Priority = true;
    Solid = true;
    Scene->AddSelfToRegistry(this, "Solid");
    W = 64;
    H = 224;
    CurrentAnimation = Sprite->FindAnimation("Wall and Column");
    YSpeed = 0;
    Type = SubType;
    State = PillarState::INIT;
    if (X < 0x3880) {
        FloorY = 0x680;
    }
    else if (X < 0x3AE0) {
        FloorY = 0x700;
    }
    else if (X < 0x47D0) {
        FloorY = 0x6E0;
    }
    else if (X < 0x4880) {
        FloorY = 0x670;
    }
    else if (X < 0x4D70) {
        FloorY = 0xF8;
    }
    else if (X < 0x4EF0) {
        FloorY = 0x178;
    }
    else if (X < 0x4FF0) {
        FloorY = 0x180;
    }
    else if (X < 0x5100) {
        FloorY = 0x1B8;
    }
    else if (X < 0x5240) {
        FloorY = 0x400;
    }
    else if (X < 0x52A0) {
        FloorY = 0x400;
    }
    else if (X < 0x5F70) {
        FloorY = 0xF8;
    }
    else if (X < 0x6070) {
        FloorY = 0x178;
    }
    else if (X < 0x6980) {
        FloorY = 0x300;
    }

    if (Type == PillarType::STATIONARY_KNUX_ONLY && Scene->Player->Character != CharacterType::Knuckles) {
        Active = false;
    }

}

void CrushingColumn::Update() {
    switch (State) {
        case PillarState::INIT:
        if (Type == PillarType::FLOOR_CRUSH) {
            State = PillarState::WAIT;
        }
        else if (Type == PillarType::FLOOR_CRUSH_PERIODIC) {
            State = PillarState::WAIT;
            Timer = 0x5F;
            TimerAction = PillarAction::CRUSH_DOWNACTION;
        }

        break;
        case PillarState::WAIT:
        YSpeed = 0;
        if (Type == PillarType::FLOOR_CRUSH) {
            if (Scene->Player->X < X) {
                if (Y > InitialY) YSpeed = -0x100;

            }

            if (Scene->Player->X > X + W / 2 + 16 && Y + H / 2 < FloorY) {
                State = PillarState::MOVE_TOWARDS_CRUSH;
                YSpeed = 0x800;
            }

        }

        break;
        case PillarState::MOVE_TOWARDS_CRUSH:
        if (Y + H / 2 >= FloorY) {
            YSpeed = 0x00;
            State = PillarState::WAIT;
            if (OnScreen) {
                Sound::Play(Sound::SFX_IMPACT4);
                Scene->ShakeTimer = 6;
            }

            if (Type == PillarType::FLOOR_CRUSH_PERIODIC) {
                Timer = 0x1F;
                TimerAction = PillarAction::MOVE_UPACTION;
            }

        }

        break;
        case PillarState::BACK_AWAY:
        if (Type == PillarType::FLOOR_CRUSH_PERIODIC) {
            if (Y > InitialY) {
                YSpeed = -0x100;
            }
            else {
                YSpeed = 0;
                State = PillarState::INIT;
            }
        }

        break;
        case PillarState::BLOCK:
        break;
    }

    if (Timer > 0) {
        Timer--;
        if (Timer == 0) {
            Timer = -1;
            switch (TimerAction) {
                case PillarAction::MOVE_UPACTION:
                State = PillarState::BACK_AWAY;
                break;
                case PillarAction::CRUSH_DOWNACTION:
                State = PillarState::MOVE_TOWARDS_CRUSH;
                YSpeed = 0x800;
                break;
            }

        }

    }

    Object::Update();
}

void CrushingColumn::Render(int CamX, int CamY) {
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

int CrushingColumn::OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data) {
    if (State != PillarState::MOVE_TOWARDS_CRUSH) return 0;

    if (HitFrom == CollideSide::TOP && Visible) {
    }
    else {
    }
    if (Scene->Players[PlayerID]->Ground && HitFrom == CollideSide::BOTTOM) {
        Scene->Players[PlayerID]->Die(false);
    }

    return 1;
}

