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
    CurrentAnimation = 0;
    VisualLayer = 1;
}

void Batbright::Update() {
    CheckDistanceToPlayers();
    if (PlayerXDistance >= 0x40) {
        App->Print(-1, "Not attacking player.");
        return;
    }

    XSpeed = 0x0200;
    MoveTowardsTargetPosition(ClosetPlayer, 0x200, 8);
    Object::Update();
}

void Batbright::OnAnimationFinish() {
}

int Batbright::OnHit() {
    return OnDeath();
}

int Batbright::OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data) {
    IPlayer* Player = Scene->Players[PlayerID];
    if (Player == 0) {
        return false;
    }

    return 1;
}

