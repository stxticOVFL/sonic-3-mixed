// Object ID: 0xFFFFFFFF
// Object Name: TitleCard.cpp

#include "TitleCard.h"

typedef IMath Math;

void TitleCard::Create() {
    Object::Create();
    AttributeBuffer = GetAttribute("zoneName");
    zoneName = AttributeBuffer.ValString;
    AttributeBuffer = GetAttribute("actID");
    actID = AttributeBuffer.ValUint8;
}

void TitleCard::Update() {
    Object::Update();
}

void TitleCard::Render(int CamX, int CamY) {
    }

