// Object ID: 0x80
// Object Name: HiddenMonitor.cpp

#include "HiddenMonitor.h"

typedef IMath Math;

void HiddenMonitor::Create() {
    Object::Create();
    Active = true;
    Priority = false;
    W = 32;
    H = 32;
    CleanupInactiveObject = true;
}

void HiddenMonitor::Render(int CamX, int CamY) {
    G->DrawRectangle(X - CamX - 16, Y - 16 - CamY, 32, 32, 0xFFFFFF);
    }

