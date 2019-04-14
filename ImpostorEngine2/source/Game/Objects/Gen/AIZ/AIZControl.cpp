// Object ID: 0xFFFFFFFF
// Object Name: AIZControl.cpp

#include "AIZControl.h"

typedef IMath Math;

void AIZControl::Create() {
    Object::Create();
    AttributeBuffer = GetAttribute("actID");
    ActID = AttributeBuffer.ValUint8;
    AttributeBuffer = GetAttribute("zoneLetters");
    ZoneLetters = AttributeBuffer.ValString;
    AttributeBuffer = GetAttribute("loadTileconfig");
    LoadTileconfig = AttributeBuffer.ValBool;
    AttributeBuffer = GetAttribute("loadStageconfig");
    LoadStageconfig = AttributeBuffer.ValBool;
    AttributeBuffer = GetAttribute("loadTiles");
    LoadTiles = AttributeBuffer.ValBool;
    AttributeBuffer = GetAttribute("loadAniTiles");
    LoadAniTiles = AttributeBuffer.ValBool;
}

void AIZControl::Update() {
    Object::Update();
}

