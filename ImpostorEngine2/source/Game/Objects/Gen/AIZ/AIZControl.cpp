// Object ID: 0xFFFFFFFF
// Object Name: AIZControl.cpp

#include "AIZControl.h"

typedef IMath Math;

void AIZControl::Create() {
    Object::Create();
    AttributeBuffer = GetAttribute("actID");
    ActID = AttributeBuffer.ValUint8;
    AttributeBuffer = GetAttribute("zoneLetters");
    sprintf(ZoneLetters, AttributeBuffer.ValString);
    AttributeBuffer = GetAttribute("loadTileconfig");
    LoadTileconfig = AttributeBuffer.ValBool;
    AttributeBuffer = GetAttribute("loadStageconfig");
    LoadStageconfig = AttributeBuffer.ValBool;
    AttributeBuffer = GetAttribute("loadTiles");
    LoadTiles = AttributeBuffer.ValBool;
    AttributeBuffer = GetAttribute("loadAniTiles");
    LoadAniTiles = AttributeBuffer.ValBool;
    Scene->ZoneID = 1;
    Scene->VisualAct = ActID;
    Scene->Act = ActID;
    sprintf(Scene->ZoneLetters, ZoneLetters);
    Scene->AddNewDebugObjectID(Obj_CollapsingPlatform);
    Scene->AddNewDebugObjectID(Obj_BreakableWall);
    Scene->AddNewDebugObjectID(Obj_SpikedLog);
    Scene->AddNewDebugObjectID(Obj_Bloominator);
    Scene->AddNewDebugObjectID(Obj_RhinoBot);
    Scene->AddNewDebugObjectID(Obj_MonkeyDude);
    Scene->AddNewDebugObjectID(Obj_CaterkillerJr);
    Scene->AddNewDebugObjectID(Obj_FireBreath);
    Scene->AddNewDebugObjectID(Obj_FlameMobile);
    if (ActID == 1) {
        Scene->VisualWaterLevel = 0x508;
        Scene->WaterLevel = 0x508;
        FireRiseValue = 0;
        FireRiseValue2 = 0;
        Timerrrr = 2;
        TreeRevealRow = 32;
        FireLayerBackup = NULL;
        CutsceneActTimer = 60;
        Scene->Data->Layers[4].OffsetY = 0;
    }

    if (ActID == 2) {
        Scene->VisualWaterLevel = 0x528;
        Scene->WaterLevel = 0x528;
        ShipTimer = 0x40200000;
        BombDelay = 0x1A4;
        BombIndex = 0;
        if (Scene->RoutineNumber == -2) {
            Scene->LevelCardTimer = 6.0;
            Scene->LevelCardHide = true;
        }
        else {
            Scene->LevelCardTimer = 0.0;
            Scene->LevelCardHide = false;
        }
    }

    if (Scene->Player) {
        if (Scene->Player->Character != CharacterType::Knuckles) {
        }
        else {
        }
    }

}

void AIZControl::Update() {
    Object::Update();
}

