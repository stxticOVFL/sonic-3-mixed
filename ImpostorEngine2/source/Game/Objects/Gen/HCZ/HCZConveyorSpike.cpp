// Object ID: 0x3F
// Object Name: HCZConveyorSpike.cpp

#include "HCZConveyorSpike.h"

typedef IMath Math;

void HCZConveyorSpike::Create() {
    Object::Create();
    StartX = 0xB28;
    EndX = 0xCD8;
    Active = true;
    Priority = true;
    W = 16;
    H = 16;
    Painful = true;
}

void HCZConveyorSpike::Update() {
    StartX = 0xB28;
    EndX = 0xCD8;
    switch (SubType & 0xF) {
        case 1:
        StartX = 0xBA8;
        EndX = 0xCD8;
        break;
        case 2:
        StartX = 0xBA8;
        EndX = 0xCD8;
        break;
        case 3:
        StartX = 0xEA8;
        EndX = 0x1058;
        break;
        case 4:
        StartX = 0x11A8;
        EndX = 0x12D8;
        break;
        case 5:
        StartX = 0x1928;
        EndX = 0x19D8;
        break;
        case 6:
        StartX = 0x21A8;
        EndX = 0x2358;
        break;
        case 7:
        StartX = 0x21A8;
        EndX = 0x2358;
        break;
        case 8:
        StartX = 0x22A8;
        EndX = 0x2458;
        break;
        case 9:
        StartX = 0x23A8;
        EndX = 0x2558;
        break;
        case 10:
        StartX = 0x2528;
        EndX = 0x26D8;
        break;
        case 11:
        StartX = 0x26A8;
        EndX = 0x27D8;
        break;
        case 12:
        StartX = 0x26A8;
        EndX = 0x2958;
        break;
        case 13:
        StartX = 0x2728;
        EndX = 0x28D8;
        break;
        case 14:
        StartX = 0x3328;
        EndX = 0x3458;
        break;
        case 15:
        StartX = 0x3328;
        EndX = 0x33D8;
        break;
    }

    Object::Update();
}

void HCZConveyorSpike::Render(int CamX, int CamY) {
    }

