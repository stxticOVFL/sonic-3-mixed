// Object ID: 0xFFFFFFFF
// Object Name: SwingingPlatformTrigger.cpp

#include "SwingingPlatformTrigger.h"

typedef IMath Math;

CONSTRUCTER SwingingPlatformTrigger::SwingingPlatformTrigger() {
}

void SwingingPlatformTrigger::Create() {
    Object::Create();
    W = 8;
    H = 48;
    X = X + (FlipX ? -28 : 28);
    Solid = true;
    Scene->AddSelfToRegistry(this, "Solid");
    SwingPlatform = NULL;
}

void SwingingPlatformTrigger::Update() {
    if (!SwingPlatform && Parent) {
        SwingPlatform = GetObjectParent();
    }

    Object::Update();
}

