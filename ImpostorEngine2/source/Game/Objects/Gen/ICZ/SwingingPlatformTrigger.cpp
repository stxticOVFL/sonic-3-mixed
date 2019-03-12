// Object ID: 0xFFFFFFFF
// Object Name: SwingingPlatformTrigger.cpp

#include "SwingingPlatformTrigger.h"

typedef IMath Math;

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

    if (!SwingPlatform) return;

    X = SwingPlatform->X + (FlipX ? -28 : 28);
    Y = SwingPlatform->Y;
    Object::Update();
}

int SwingingPlatformTrigger::OnCollisionWithPlayer(int PlayerID, int HitFrom, int Data) {
    Player = Scene->Players[PlayerID];
    if (!SwingPlatform || Player->GroundSpeed <= 0x10 || !Player->Ground || SwingPlatform->SubType != 0) return 0;

    IApp::Print(0, "%d", Player->GroundSpeed / 4);
    SwingPlatform->SubType = Player->GroundSpeed / 4;
}

