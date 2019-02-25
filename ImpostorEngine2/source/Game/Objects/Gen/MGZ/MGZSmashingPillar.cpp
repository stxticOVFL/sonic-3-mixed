// Object ID: 0x52
// Object Name: MGZSmashingPillar.cpp

#include "MGZSmashingPillar.h"

typedef IMath Math;

void MGZSmashingPillar::Create() {
    Object::Create();
    Active = true;
    Priority = false;
    W = 64;
    H = 80;
    CurrentAnimation = 35;
}

