// Object ID: 0x6E
// Object Name: WaterDrop.cpp

#include "WaterDrop.h"

typedef IMath Math;

void WaterDrop::Create() {
    Object::Create();
    Active = true;
    Priority = false;
    Sprite = LevelScene::LoadSpriteFromBin("HCZ/WaterDrop.bin", SaveGame::CurrentMode);
    W = 8;
    H = 8;
    State = -1;
    CurrentAnimation = 0;
}

void WaterDrop::Update() {
    switch (State) {
        case -1:
        Timer++;
        Visible = false;
        if (Timer > 180) {
            State++;
            Timer = 0;
        }

        break;
        case 0:
        Visible = true;
        Frame = 0;
        Timer++;
        if (Timer > 5) {
            State++;
            Timer = 0;
        }

        break;
        case 1:
        Frame = 1;
        Timer++;
        if (Timer > 5) {
            State++;
            Timer = 0;
        }

        break;
        case 2:
        Frame = 2;
        Timer++;
        if (Timer > 8) {
            State++;
            Timer = 0;
        }

        break;
        case 3:
        Frame = 3;
        Y += 1;
        if (Scene->CollisionAt(X, Y)) {
            State++;
        }

        break;
        case 4:
			Frame = 4;
        Timer++;
        if (Timer > 5) {
            State++;
            Timer = 0;
        }

        break;
        case 5:
        Frame = 5;
        Timer++;
        if (Timer > 5) {
            State++;
            Timer = 0;
        }

        break;
        case 6:
        Frame = 6;
        Timer++;
        if (Timer > 5) {
            X = InitialX;
            Y = InitialY;
            Frame = 0;
            State = -1;
            Timer = 0;
            Visible = false;
        }

        break;
    }

    Object::Update();
}

void WaterDrop::Render(int CamX, int CamY) {
    if (!Visible) return;

    G->DrawSprite(this->Sprite, CurrentAnimation, Frame, this->X - CamX, this->Y - CamY, 0, this->FlipX ? IE_FLIPX : IE_NOFLIP);
    if (DrawCollisions) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

    }

int WaterDrop::OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data) {
    if (!Scene->Players[PlayerID]) return 0;

    if (State == 3) {
        State++;
    }

    return 1;
}

