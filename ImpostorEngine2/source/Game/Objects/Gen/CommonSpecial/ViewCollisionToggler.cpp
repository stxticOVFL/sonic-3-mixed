// Object ID: 0xFFFFFFFF
// Object Name: ViewCollisionToggler.cpp

#include "ViewCollisionToggler.h"

typedef IMath Math;

void ViewCollisionToggler::Create() {
    Object::Create();
    Active = true;
    CleanupInactiveObject = true;
}

void ViewCollisionToggler::Update() {
    if (!isHeldDebugObject) {
        Scene->ViewTileCollision = !Scene->ViewTileCollision;
        Active = false;
    }

    Object::Update();
}

void ViewCollisionToggler::Render(int CamX, int CamY) {
    if (!Scene->maxLayer) {
        G->DrawSprite(Scene->GlobalDisplaySprite, 18, 4, X - CamX, Y - CamY, 0, 0);
    }

    }

