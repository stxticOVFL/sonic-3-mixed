// Object ID: 0xFFFFFFFF
// Object Name: PlayerSpawn.cpp

#include "PlayerSpawn.h"

typedef IMath Math;

void PlayerSpawn::Create() {
    Object::Create();
    bool SpawnSonic;
    bool SpawnMiles;
    bool SpawnKnux;
    bool SpawnMighty;
    bool SpawnRay;
    SpawnAsSidekick = false;
    SpawnPlayerIndex = 0;
    AttributeBuffer = GetAttribute("characterID");
    SpawnPlayerID = AttributeBuffer.ValUint8;
    SpawnSonic = bool(SpawnPlayerID >> 0 & 1);
    SpawnMiles = bool(SpawnPlayerID >> 1 & 1);
    SpawnKnux = bool(SpawnPlayerID >> 2 & 1);
    SpawnMighty = bool(SpawnPlayerID >> 3 & 1);
    SpawnRay = bool(SpawnPlayerID >> 4 & 1);
    if (Scene->SpecialSpawnPositionX >= 0) X = Scene->SpecialSpawnPositionX;

    if (Scene->SpecialSpawnPositionY >= 0) Y = Scene->SpecialSpawnPositionY;

    if (SpawnSonic && SaveGame::CurrentCharacterFlag == 0) {
        Scene->SpawnPlayer(SpawnPlayerIndex, SpawnAsSidekick, true, X, Y);
    }
    else if (SpawnMiles && SaveGame::CurrentCharacterFlag == 1) {
        Scene->SpawnPlayer(SpawnPlayerIndex, SpawnAsSidekick, true, X, Y);
    }
    else if (SpawnKnux && SaveGame::CurrentCharacterFlag == 2) {
        Scene->SpawnPlayer(SpawnPlayerIndex, SpawnAsSidekick, true, X, Y);
    }
    else if (SpawnMighty && SaveGame::CurrentCharacterFlag == 3) {
        Scene->SpawnPlayer(SpawnPlayerIndex, SpawnAsSidekick, true, X, Y);
    }
    else if (SpawnRay && SaveGame::CurrentCharacterFlag == 4) {
        Scene->SpawnPlayer(SpawnPlayerIndex, SpawnAsSidekick, true, X, Y);
    }

    Active = false;
}

