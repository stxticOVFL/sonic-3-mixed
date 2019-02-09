// Object ID: 0xA5
// Object Name: Batbright.cpp

#include "Batbright.h"

typedef IMath Math;

void Batbright::Create() {
    Enemy::Create();
    Active = true;
    Priority = true;
    W = 16;
    H = 16;
    VisW = 16;
    VisH = 16;
    Gravity = 0;
    Frame = 0;
    CurrentAnimation = 35;
    for (int i = 0; i < 2; i++)
{
        Children[i] = Scene->AddNewObject(Obj_BatbrightParts, 0, X, Y, false, false);
        Children[i]->Sprite = Sprite;
        Children[i]->CurrentAnimation = CurrentAnimation + i;
        Children[i]->Parent = this;
    }
    VisualLayer = 1;
}

void Batbright::Update() {
    CheckDistanceToPlayers();
    if (PlayerXDistance >= 0x40) {
        App->Print(-1, "Not attacking player.");
        return;
    }

    XSpeed = 0x200;
    if (PlayerRelativeXDirection == 0) {
        XSpeed = -XSpeed;
    }

    MoveTowardsTargetPosition(ClosetPlayer, 0x200, 8);
    MoveSprite();
    Object::Update();
}

void Batbright::OnAnimationFinish() {
}

int Batbright::OnHit() {
    Children[0]->Active = false;
    Children[1]->Active = false;
    return OnDeath();
}

int Batbright::OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data) {
    IPlayer* Player = Scene->Players[PlayerID];
    if (Player == 0) {
        return false;
    }

    return 1;
}

void Batbright::Render(int CamX, int CamY) {
    G->DrawSprite(Sprite, CurrentAnimation, Frame, X - CamX, Y - CamY, 0, IE_NOFLIP);
    }

