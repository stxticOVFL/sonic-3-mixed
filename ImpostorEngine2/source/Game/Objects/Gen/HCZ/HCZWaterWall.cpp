// Object ID: 0x3B
// Object Name: HCZWaterWall.cpp

#include "HCZWaterWall.h"

typedef IMath Math;

void HCZWaterWall::Create() {
    Object::Create();
    this->Active = true;
    this->Priority = true;
    this->W = 64;
    this->H = 0x270 + 64;
    this->Y -= 0x138 - 32;
    this->VisualLayer = 1;
}

void HCZWaterWall::Render(int CamX, int CamY) {
    if (App->viewObjectCollision) {
        G->SetDrawAlpha(0x80);
        G->DrawRectangle(X - (W / 2) - CamX, Y - (H / 2) - CamY, W, H, DrawCollisionsColor);
        G->SetDrawAlpha(0xFF);
    }

    }

int HCZWaterWall::OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data) {
    if (this->X < 0xA80) return false;

    IPlayer* player = Scene->Players[PlayerID];
    if (player->Action != ActionType::InStream) return false;

    if (player->EZY > this->Y - this->H / 2 + 20 && player->EZY < this->Y - this->H / 2 + 40) {
        player->ObjectControlled = 0;
        player->DoCollision = true;
        player->EZY = this->Y - this->H / 2 - 20;
        player->YSpeed = -0x1000;
    }
    else if (player->EZY > this->Y) {
        player->ObjectControlled = 0x80;
        player->DoCollision = false;
        player->VisualLayer = 0;
    }

    return true;
}

