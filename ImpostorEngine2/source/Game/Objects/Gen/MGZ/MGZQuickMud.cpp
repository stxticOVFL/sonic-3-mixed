// Object ID: 0x4F
// Object Name: MGZQuickMud.cpp

#include "MGZQuickMud.h"

typedef IMath Math;

void MGZQuickMud::Create() {
    Object::Create();
    Active = true;
    Priority = false;
    Solid = true;
    Scene->AddSelfToRegistry(this, "Solid");
    W = SubType << 4;
    H = 0x60;
}

int MGZQuickMud::OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data) {
    return true;
}

